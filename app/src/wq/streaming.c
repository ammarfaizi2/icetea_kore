
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <kore/kore.h>
#include <kore/http.h>

#include "error_page.h"
#include "wq/streaming.h"


static void file_unmap(struct stream *);
static int file_stream_finish(struct netbuf *);
static int file_open(struct http_request *, struct stream **, struct icetea_file_stream*);
static int file_mmap(struct http_request *, struct stream *);

int
file_stream(struct http_request *req, struct icetea_file_stream *sti)
{
	struct	stream	*s;

	if (!file_open(req, &s, sti))
		return (KORE_RESULT_OK);
	
	kore_log(LOG_NOTICE, "%p: opened %s for streaming (%ld)",
	    (void *)req->owner, s->path, s->size);

	http_response_header(req, "content-type", sti->content_type);
	http_response_stream(req, 200, s->data,
	    s->size, file_stream_finish, s);
	return (KORE_RESULT_OK);
}

int
file_open(struct http_request *req, struct stream **out, struct icetea_file_stream *sti) {
	struct stat	st;
	struct stream *s;

	char *fpath = sti->file;
	kore_log(LOG_NOTICE, "%s", sti->file);

	s = kore_malloc(sizeof(*s));
	s->data = NULL;
	s->path = fpath;

	if ((s->fd = open(fpath, O_RDONLY)) == -1) {
		kore_free(s);

		if (errno == ENOENT)
			// http_response(req, 404, NULL, 0);
			error_page_404(req);
		else
			http_response(req, 500, NULL, 0);

		return (KORE_RESULT_ERROR);
	}

	if (fstat(s->fd, &st) == -1) {
		close(s->fd);
		kore_free(s);

		http_response(req, 500, NULL, 0);
		return (KORE_RESULT_ERROR);
	}

	s->size = st.st_size;
	if (!file_mmap(req, s)) {
		close(s->fd);
		kore_free(s);

		http_response(req, 500, NULL, 0);
		return (KORE_RESULT_ERROR);
	}

	*out = s;

	return (KORE_RESULT_OK);
}


int
file_mmap(struct http_request *req, struct stream *s)
{
	s->data = mmap(NULL, s->size, PROT_READ, MAP_SHARED, s->fd, 0);
	if (s->data == MAP_FAILED)
		return (KORE_RESULT_ERROR);

	return (KORE_RESULT_OK);
}

int
file_stream_finish(struct netbuf *nb)
{
	struct stream *s = nb->extra;

	kore_log(LOG_NOTICE, "%p: file stream %s done (%zu/%zu)",
	    (void *)nb->owner, s->path, nb->s_off, nb->b_len);

	file_unmap(s);

	return (KORE_RESULT_OK);
}

void
file_unmap(struct stream *s)
{
	if (munmap(s->data, s->size) == -1) {
		kore_log(LOG_ERR, "munmap(%s): %s", s->path, errno_s);
	} else {
		s->data = NULL;
		kore_log(LOG_NOTICE,
		    "unmapped %s for streaming", s->path);
	}
}