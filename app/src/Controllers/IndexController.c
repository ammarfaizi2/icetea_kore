#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"

int	index_page(struct http_request *);

int
index_page(struct http_request *req)
{
	
	return view(req, "login");
}
