
#ifndef __H_ICETEA_STREAMING_H
#define __H_ICETEA_STREAMING_H

#define ICETEA_ALLOC_FILENAME 255

struct icetea_file_stream
{
	char	*file;
	char	*content_type;
};

struct stream {
	int			fd;
	off_t		size;
	char		*path;
	u_int8_t	*data;
};

int	file_stream(struct http_request *, struct icetea_file_stream*);

#endif
