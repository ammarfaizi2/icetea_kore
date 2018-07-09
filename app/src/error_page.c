#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"

int	error_page_404(struct http_request *);

int
error_page_404(struct http_request *req)
{
	
	return view(req, "errors/404");
	return (KORE_RESULT_OK);
}
