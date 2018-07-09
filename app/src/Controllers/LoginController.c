
#include <string.h>
#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"


int	login_page(struct http_request *);
int login_action_page(struct http_request *);

int
login_page(struct http_request *req)
{
	
	return view(req, "login");
}

int
login_action_page(struct http_request *req)
{
	char *username, *password, *login;

	http_populate_cookies(req);

	if (http_request_cookie(req, "login", &login))
	{
		if (!strcmp(login, "ok"))
		{
			http_response_header(req, "Location", "/home");
			goto fq;
			return KORE_RESULT_OK;
		}
	}

	http_populate_post(req);
	http_argument_get_string(req, "username", &username);
	http_argument_get_string(req, "password", &password);

	if (!strcmp(username, "admin") && !strcmp(password, "admin"))
	{
		http_response_cookie(req, "login", "ok", "/", time(NULL) + (1 * 60 * 60), 0, NULL);
		http_response_header(req, "Location", "/home");
	} else {
		http_response_header(req, "Location", "/login");
	}

fq:	
	http_response(req, 302, "", 0);

	return KORE_RESULT_OK;
}
