
#include <string.h>
#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"

int	index_page(struct http_request *);

int
index_page(struct http_request *req)
{

	char *login;

	http_populate_cookies(req);

	if (http_request_cookie(req, "login", &login))
	{
		if (!strcmp(login, "ok"))
		{
			http_response_header(req, "Location", "/home");
			http_response(req, 302, "", 0);
			return KORE_RESULT_OK;
		}
	}

	return view(req, "login");
}
