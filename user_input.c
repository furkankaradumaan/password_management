/* Name: user_input.c
 * Purpose: Implementing functions in user_input.h.
 * 	Getting integer or string data from the user by
 * 	displaying the desired prompt.
 * Author: Naci Furkan Karaduman
*/
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
