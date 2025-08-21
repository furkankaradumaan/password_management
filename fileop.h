/* Name: fileop.h
 * Purpose: This file contains the constants and function prototypes for
 * 	storing passwords in to a file, or reading the passwords back from the file.
 * Author: Naci Furkan Karaduman
*/

#ifndef __FILE_OP_H
#define __FILE_OP_H

#include "account.h"

#define MAXPASS	50

#define _SOURCE_FILE	"accounts.dat"

int read_accounts_from_file(Account **accounts);
int save_accounts_to_file(Account **accounts, int npass);
#endif
