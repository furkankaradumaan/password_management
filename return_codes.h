/* Name: return_codes.h
 * Purpose: To mantain meaningfull names for
 * 	function return values and to make easier
 * 	to manage them.
 * Author: Naci Furkan Karaduman
 * */

#ifndef _RETURN_CODES_H
#define _RETURN_CODES_H

enum RETURN_CODE
{
	SUCCESS = -100,
	MISSING_FIELD_ERROR,
	TOO_LONG_INPUT_ERROR,
	ACCOUNT_BUFFER_FULL_ERROR,
	ACCOUNT_DOES_NOT_EXISTS_ERROR,
	INVALID_FIELD_ERROR,
	ID_ALREADY_EXISTS_ERROR,
	ALLOCATION_FAILED_ERROR,
	FILE_COULD_NOT_OPEN_ERROR,
	UNKNOWN_OPERATION_ERROR
};
#endif
