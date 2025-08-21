#include "fileop.h"
#include <stdio.h>
#include "return_codes.h"

int read_accounts_from_file(/*@notnull@*/Account **accounts)
{
	int count = 0;
	FILE *file = fopen(_SOURCE_FILE, "r");
	if(file == NULL)
		return FILE_COULD_NOT_OPEN_ERROR;
	
	while(fread(accounts[count], sizeof(Account), 1, file) > 0)
		count++;
	
	fclose(file);
	return count;
}
int save_accounts_to_file(/*@notnull@*/Account **accounts, int n)
{
	int count = 0;

	FILE *file = fopen(_SOURCE_FILE, "w");
	if(file == NULL )
		return FILE_COULD_NOT_OPEN_ERROR;
	while(n-- > 0)
	{
		fwrite(accounts[count], sizeof(Account), 1, file);
		count++;
	}
	fclose(file);
	return count;
}

