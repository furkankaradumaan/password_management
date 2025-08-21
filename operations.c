/* Name: operations.c
 * Purpose: Contains operations about adding, removing,
 * 	updating or searching accounts.
 * Author: Naci Furkan Karaduman*/
#include <stdio.h>
#include "operations.h"
#include <string.h>
#include "return_codes.h"
#include <stdlib.h>

/*@notnull@*/Account *account_storage[MAXACCOUNTS];
int accounts = 0;

int operation_add_account(/*@null@*/Account *account)
{
        if(account == NULL)
                return MISSING_FIELD_ERROR;
        if(accounts >= MAXACCOUNTS)
                return ACCOUNT_BUFFER_FULL_ERROR;
        account_storage[accounts++] = account;	
	return SUCCESS;
}

int operation_remove_account(int account_id)
{
	int index = operation_search_by_id(account_id);

	if(index == ACCOUNT_DOES_NOT_EXISTS_ERROR)
		return ACCOUNT_DOES_NOT_EXISTS_ERROR;
	
	account_destroy_account(account_storage[index]);
	for(int i = index + 1; i < accounts; i++)
	{
		account_storage[i-1] = account_storage[i];
	}
	account_storage[accounts] = NULL;
	accounts--;

	return SUCCESS;
}
void operation_list_accounts()
{
	for(int i = 0; i < accounts; i++)
	{
		account_print_account(account_storage[i]);
		printf("*************************************\n");
	}
}

int operation_update_account(int account_id, void *new_value, enum FIELDS field)
{
	int index = operation_search_by_id(account_id);
	if(index == ACCOUNT_DOES_NOT_EXISTS_ERROR)
		return ACCOUNT_DOES_NOT_EXISTS_ERROR;

	if(field == ACC_ID)
		account_storage[index]->account_id = *((int *)new_value);
	else if(field == ACC_NAME)
		strcpy(account_storage[index]->account_name,
				(char *)new_value);
	else if(field == ACC_PASSWORD)
		strcpy(account_storage[index]->password,
                                (char *)new_value);
	else if(field == ACC_USERNAME)
		strcpy(account_storage[index]->user_name,
                                (char *)new_value);
	else
		return INVALID_FIELD_ERROR;
	return SUCCESS;
}

int operation_search_by_id(int account_id)
{
	for(int i = 0; i < accounts; i++)
		if(account_storage[i]->account_id == account_id)
			return i;

	return ACCOUNT_DOES_NOT_EXISTS_ERROR;
}
void operation_account_storage_initialize()
{	
	for(int i = 0; i < MAXACCOUNTS; i++)
	{
		account_storage[i] = (Account *)malloc(sizeof(Account));	
	}
}

