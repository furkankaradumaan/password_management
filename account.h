#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#define MAXFIELD	100

enum FIELDS
{
	ACC_ID,
	ACC_NAME,
	ACC_USERNAME,
	ACC_PASSWORD
};

typedef struct
{
	int account_id; // Account ID (Unique for each account.)
	char account_name[MAXFIELD + 1];
	char user_name[MAXFIELD + 1];
	char password[MAXFIELD + 1];	
}Account;

int account_create_account(Account **acc,
		int account_id,
		/*@unique@*/char *account_name,
		/*@unique@*/char *user_name,
		/*@unique@*/char *password);
void account_destroy_account(Account *account);

void account_print_account(Account *account);
int check_id_exists(int id);

#endif
