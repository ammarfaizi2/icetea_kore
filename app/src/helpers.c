/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <kore/kore.h>

#include "helpers.h"
#include "wq/streaming.h"

int
view(struct http_request *req, const char *name) {

	struct icetea_file_stream ic;
	ic.file = malloc(ICETEA_ALLOC_FILENAME);

	strcpy(ic.file, "views/");
	strcat(ic.file, name);
	strcat(ic.file, ".ice");
	ic.content_type = "text/html";
	file_stream(req, &ic);

	return (KORE_RESULT_OK);
}

int endWith(const char str1[], const char str2[])
{
	for (int j = strlen(str1)-1, i = strlen(str2)-1; i >= 0; --i)
	{
		if (str1[j--] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}
