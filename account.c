/* Name: account.c
 * Purpose: Implements the functions in the
 * 	header account.h. Functions about displaying, creating
 * 	or destoying account structs.
 * Author: Naci Furkan Karaduman
*/
#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "return_codes.h"

extern Account *account_storage[];
extern int accounts;

int account_create_account(Account **acc, int account_id,
		char *account_name, char *user_name, char *password)
{
	if(account_name == NULL
	   || user_name == NULL
	   || password == NULL)
		return MISSING_FIELD_ERROR;
	if(strlen(account_name) > MAXFIELD
	   || strlen(user_name) > MAXFIELD
	   || strlen(password) > MAXFIELD)
		return TOO_LONG_INPUT_ERROR;
	if(check_id_exists(account_id) == 1)
	{
		return ID_ALREADY_EXISTS_ERROR;
	}
	*acc = (Account *)malloc(sizeof(Account));
	if(acc == NULL)
		return ALLOCATION_FAILED_ERROR;
	(*acc)->account_id = account_id;
	strcpy((*acc)->account_name, account_name);
	strcpy((*acc)->user_name, user_name);
	strcpy((*acc)->password, password);

	return SUCCESS;
}

void account_destroy_account(Account *account)
{
	if(account != NULL)
		free(account);
}

void account_print_account(Account *account)
{
	printf("Account ID: %d\nAccount Name: %s\nUsername: %s\nPassword: %s\n",
			account->account_id, account->account_name,
			account->user_name, account->password);
}

int check_id_exists(int id)
{
	for(int i = 0; i < accounts; i++)
	{
		if(account_storage[i]->account_id == id)
			return 1;
	}

	return 0;
}
