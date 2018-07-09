#include <kore/kore.h>
#include <kore/http.h>
#include "helpers.h"

int	login_page(struct http_request *);
int login_action(struct http_request *);

int
login_page(struct http_request *req)
{
	
	return view(req, "login");
}

int
login_post(struct http_request *req)
{

}