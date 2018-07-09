
#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"

int	home_page(struct http_request *);
int	logout_page(struct http_request *);

int
home_page(struct http_request *req)
{
	char *login;

	http_populate_cookies(req);

	if (http_request_cookie(req, "login", &login))
	{
		if (strcmp(login, "ok"))
		{
			http_response_header(req, "Location", "/login");
			http_response(req, 302, "", 0);
			return KORE_RESULT_OK;
		}
	}

	return view(req, "home");
}

int
logout_page(struct http_request *req)
{
	http_response_cookie(req, "login", "", "/", 0, 0, NULL);
	http_response_header(req, "Location", "/login");
	http_response(req, 302, "", 0);
	return KORE_RESULT_OK;
}
