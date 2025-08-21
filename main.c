/* Name: main.c
 * Purpose: get the user input and manage the actions to perform
 * 	the desired operation(s).
 * Author: Naci Furkan Karaduman
*/

#include <stdio.h>
#include <string.h>
#include "fileop.h"
#include "account.h"
#include <stdlib.h>
#include "operations.h"
#include "user_input.h"
#include "return_codes.h"

#define MASTER_PASSWORD	"furkankaraduman"

static void show_menu();

extern Account *account_storage[];
extern int accounts;

int main(void)
{
	// Firstly we need to ask the master password and confirm it.
	// Ask the user to enter the master string to access the SSPasword 
	// Management System.
	char master_password[50];
	int res; 
	printf("Enter the master password: ");
	res = scanf("%49s", master_password);
	
	// Compare the result with the MASTER_PASSWORD. If there is a match,
	// print a welcome message, otherwise print an error and terminate the program.
	if(res == 1 && strcmp(master_password, MASTER_PASSWORD) == 0)
		printf("Welcome to SSPassword Management System\n");
	else{
		perror("You entered wrong password\n");
		return 1;
	}
	
	// account_storage is a global variable and all of its pointers are
	// initially NULL. This function initializes all of the pointers of
	// the array.
	operation_account_storage_initialize();

	// Load the accounts
	// read the account data into account_storage.
	accounts = read_accounts_from_file(account_storage);

	// Check if the return value of the function is the FILE_COULD_NOT_OPEN_ERROR
	// error code(see return_codes.h)
	if(accounts == FILE_COULD_NOT_OPEN_ERROR){
		perror("Occured an error while reading files from source file\n");
		return accounts;
	}
	// Declare a variable for operation choice.
	int operation = -1;
	int id = -1; // Initiallty an invalid id number.
	int field;
	/*@null@*/char password[MAXFIELD + 1];
	/*@null@*/char account_name[MAXFIELD + 1];
	/*@null@*/char user_name[MAXFIELD + 1];
	/*@null@*/Account *acc = NULL;
	do{
		res = -1;
		operation = -1;
		show_menu();
		
		get_integer("Enter operation number: ", &operation);
		switch(operation)
		{
			case EXIT: 
				printf("Terminatig SSPassword Management System...\n");
				break;
			case ADD: // Add a new password
				res = get_integer("Enter account ID: ", &id);
				if(res != 1) {res = MISSING_FIELD_ERROR;break;};
				res = get_string("Enter account name: ", account_name);
				if(res != 1) {res = MISSING_FIELD_ERROR;break;};
				res = get_string("Enter username: ", user_name);
				if(res != 1) {res = MISSING_FIELD_ERROR;break;};
				res = get_string("Enter password: ", password);
				if(res != 1) {res = MISSING_FIELD_ERROR;break;};
				
				res = account_create_account(&acc, id, account_name, user_name, password);
				if(res != SUCCESS)
					break;
				res = operation_add_account(acc);
				break;
			case LIST: 
				printf("PASSWORDS:\n");
				operation_list_accounts();
				res = SUCCESS;
				break;
			case UPDATE:
				get_integer("Enter account ID: ", &id);
				get_integer("Enter field code: ", &field);
				if(field == ACC_ID)
				{
					int nid;
					get_integer("Enter new field value: ", &nid);
					res = operation_update_account(id, (void *)&nid, field);
				}else
				{
					char new[MAXFIELD + 1];
					get_string("Enter new field value: ", new);
					res = operation_update_account(id, (void *)new, field);
				}
				break;
			case REMOVE:
				get_integer("Enter account ID: ", &id);
				res = operation_remove_account(id);
				break;
			default: 
				fprintf(stderr, "Unknown operation %d\n", operation);
				res = UNKNOWN_OPERATION_ERROR;	
		}
		// Print the return codes.
		if(res == SUCCESS)
			fprintf(stdout, "SUCCESS\n");
		else if(res == MISSING_FIELD_ERROR)
			fprintf(stderr, "MISSING FIELD ERROR\n");
		else if(res == TOO_LONG_INPUT_ERROR)
			fprintf(stderr, "TOO LONG INPUT ERROR\n");
		else if(res == ACCOUNT_BUFFER_FULL_ERROR)
			fprintf(stderr, "ACCOUNT BUFFER FULL ERROR\n");
		else if(res == ACCOUNT_DOES_NOT_EXISTS_ERROR)
			fprintf(stderr, "ACCOUNT DOES NOT EXISTS ERROR\n");
		else if(res == INVALID_FIELD_ERROR)
			fprintf(stderr, "INVALIK FIELD ERROR\n");
		else if(res == ID_ALREADY_EXISTS_ERROR)
			fprintf(stderr, "ID ALREADY EXISTS ERROR\n");
		else if(res == ALLOCATION_FAILED_ERROR)
			fprintf(stderr, "ALLOCATION FAILED ERROR\n");
		else if(res == FILE_COULD_NOT_OPEN_ERROR)
			fprintf(stderr, "FILE COULD NOT OPEN\n");
	}while(operation != EXIT && res == SUCCESS);
	
	/*
	 *	Save all the accounts into the source file back.
	 * */
	int saved = save_accounts_to_file(account_storage, accounts);
	/*
	 *	Check if the number of saved account matches with the total number of accounts.
	 * */
	if(saved == accounts)
		printf("All accounts saved successfully.\n");
	else
		printf("All accounts could not saved!\n");
	return 0;
}

void show_menu()
{
	printf("1-> Add new account\n");
	printf("2-> List accounts\n");
	printf("3-> Update account\n");
	printf("4-> Remove account\n");
	printf("0-> Exit\n");
}


