
#include <kore/kore.h>
#include <kore/http.h>

#include "helpers.h"
#include "wq/streaming.h"

int	public_renderer(struct http_request *);

int
public_renderer(struct http_request *req)
{
	struct icetea_file_stream ic;
	ic.file = malloc(ICETEA_ALLOC_FILENAME);
	strcpy(ic.file, "public");
	strcat(ic.file, req->path);
	
	ic.content_type = "application/octet-stream";

	if (endWith(req->path, ".css"))
	{
		ic.content_type = "text/css";		
	} else if (endWith(req->path, ".json")) 
	{
		ic.content_type = "application/json";
	}

	file_stream(req, &ic);

	return (KORE_RESULT_OK);
}
