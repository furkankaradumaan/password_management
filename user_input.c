#include <stdio.h>
#include "user_input.h"

int get_integer(char *prompt, int *out)
{
	printf("%s", prompt);
	return scanf("%d", out);
}
int get_string(char *prompt, char *out)
{
	printf("%s", prompt);
	return scanf("%s", out);
}
