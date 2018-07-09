
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
	char *username, *password, *out;
	http_populate_post(req);
	http_argument_get_string(req, "username", &username);
	http_argument_get_string(req, "password", &password);

	out = malloc(1024);

	strcpy(out, "Username: ");
	strcat(out, username);
	strcat(out, "<br/>Password: ");
	strcat(out, password);

	http_response_header(req, "Content-Type", "text/html");
	http_response(req, 200, out, strlen(out));
	free(out);
	
	return KORE_RESULT_OK;
}
