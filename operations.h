#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include "account.h"
#define MAXACCOUNTS	100


enum OPERATIONS
{
	EXIT = 0,
	ADD,
	LIST,
	UPDATE,
	REMOVE	
};

int operation_add_account(Account *account);
int operation_remove_account(int account_id);
void operation_list_accounts();
int operation_update_account(int account_id, void *new_value, enum FIELDS field);
int operation_search_by_id(int account_id);
void operation_account_storage_initialize();

#endif
