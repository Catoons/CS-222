/*
 HW 3
 Written with VIM
*/

#include<stdio.h>
#include<time.h>
#include<string.h>

char *getDateAndTime();
int get_integer();
void decimal_to_binary(int decimal_val, char binary_string[]);
void decimal_to_hex(int decimal_val, char hex_string[]);
void decimal_to_oct(int decimal_val, char oct_string[]);
int save_file(char name[], char datetime[], int decimal_val, char oct_string[], char hex_string[], char binary_string[]);

int main()
{

// variables are defined that will be used throughout the functions

	char name[32],datetime[32],binary_string[32],oct_string[32],hex_string[32];
	int decimal_val = 0, sav_success = 0; 

// recieves user input from keyboard as string 'name'
	
	printf("Enter your name:");
	fgets(name, sizeof(name), stdin);

// if get_integer() returns -1, the program ends. Otherwise, it will loop

	while (decimal_val != -1)
	{
		decimal_val = get_integer();

		if (decimal_val == -1)
		{
			printf("\nGoodbye!");
			return 0;
		}

// calls the datetime function and saves date and time as 'datetime'

		strcpy(datetime, getDateAndTime());

// runs and prints conversions 

		printf("\nDecimal: %d", decimal_val);	

		decimal_to_binary(decimal_val, binary_string);
		decimal_to_hex(decimal_val, hex_string);
		decimal_to_oct(decimal_val, oct_string);
	
		printf("\nBinary: %s", binary_string);
		printf("\nOctal: %s", oct_string);
		printf("\nHexadecimal: %s", hex_string);

// calls function to save a file 

		sav_success = save_file(name, datetime, decimal_val, oct_string, hex_string, binary_string);

	}
	printf("\nGoodbye!");
}

// gets and returns date and time as 'datetime'

char *getDateAndTime()
{
	time_t datetime;
	time(&datetime);
	return ctime(&datetime);
}


// gets either an integer or the character 'x' from user and saves as string

int get_integer()
{

// prototypes atoi function	to convert from str to int 

	int atoi(const char *str);
	char user_in[32];
	int user_number = 0; 

	printf("Enter an Integer [1 - 1,000,000] or type x to exit:");
	fgets(user_in, sizeof(user_in), stdin);
	

// if the user inputs 'x', the function returns -1, ending the function

	if (user_in[0] == 'x')
	{	
		return -1;
	}

// otherwise, it converts the string of numbers to an integer, and checks
// if it is in the specified range. As long as it is not, it will continue
// to run, prompting the user each time. It also continues to check for 'x'

	else
	{
		user_number = atoi(user_in);
		while (1000000 < user_number || user_number < 1)
		{	
			printf("Error: %d is out of range\n", user_number);
			printf("Enter an Integer [1 - 1,000,000] or type x to exit:");
			fgets(user_in, sizeof(user_in), stdin);
			user_number = atoi(user_in);

			if (user_in[0] == 'x')
			{
				return -1;
			}		

// once the user enters a valid number, it returns it to main as an integer 

		}
		return atoi(user_in);
	}
}


// converts the decimal obtained in the function above to its binary form

void decimal_to_binary(int decimal_val, char binary_string[])
{
	int i=0, j=0;
	int quotient; 
	quotient = decimal_val;
	char temp_string[32];
	int length;

// the value of 'decimal_val' is copied to 'quotient' so the original value
// can be saved and used in later functions 
	

// the remainder of the decimal when divided by 2 (which will always be 0 or 1)
// is converted to a string with sprintf and placed at the location of
// temp_string corresponding to the value of i (since i starts at 0 and is
// incremented by 1 each loop, so the next remainder is placed in next spot) 
	
// once its saved that remainder, it divides the decimal by 2 and repeat
// to get the next binary digit. 

	while (quotient != 0)
	{
		sprintf(&temp_string[i], "%d", quotient % 2);
		i++;
		quotient = quotient / 2;
	} 

	length = strlen(temp_string);

// 1 is subtracted from i so null byte is excluded from the next loop

	i--;

// since binary is read left to right but the loop wrote it right to left,
// the string must be reversed. Counter j, which is starting at 0, is used
// for the final string that will be used in main() while the original counter
// i, used in the above function, will be used to iterate backwards. 

// So, starting from where it left off, the remainders are iterated over
// backwards and copied to 'binary_string', now in correct order.

	while (j < length)
	{
		sprintf(&binary_string[j], "%c", temp_string[i]);
		j++;
		i--;
	} 
		
}

// the next two functions are very similar to the last.
// this function converts the same decimal value into hexadecimal form.

void decimal_to_hex(int decimal_val, char hex_string[])
{
	int i=0, j=0;
	int quotient, temp;
	quotient = decimal_val;
	int length = 0;
	char cool_string[32];

// a similar loop to the last function, except this time it's dividing by
// 16 instead of 2, becuase hex has 16 possible states unlike binary. 

	while (quotient != 0)
	{
		temp = quotient %16; 

// converts digits into the numbers that correspond to their chars in ACII 

			if (temp < 10)
				temp = temp + 48;
			else
				temp = temp + 55;
		
// whatever # 'temp' is will be converted to its character equivalent in ASCII

		sprintf(&cool_string[i], "%c", temp);
		i++;
		quotient = quotient / 16;
	} 

// same thing as decimal_to_binary function to reverse string

	length = strlen(cool_string);
	i--;

	while (j < length)
	{
		sprintf(&hex_string[j], "%c", cool_string[i]);
		j++;
		i--;
	} 
}

// this function is the same as decimal_to_binary except it divides by 8 
// instead of 2, since octal has 8 different values (0-7)

void decimal_to_oct(int decimal_val, char oct_string[])
{
	int i=0, j=0;
	int quotient; 
	quotient = decimal_val;
	char temp_string[32];
	int length;

	while (quotient != 0)
	{
		sprintf(&temp_string[i], "%d", quotient % 8);
		i++;
		quotient = quotient / 8;
	} 

	length = strlen(temp_string);
	i--;

	while (j < length)
	{
		sprintf(&oct_string[j], "%c", temp_string[i]);
		j++;
		i--;
	} 
}

// function to save data as a file 

int save_file(char name[], char datetime[], int decimal_val, char oct_string[], char hex_string[], char binary_string[])
{
	char user_input[32];
	char file_name[32], *pointer;
	int length;
	FILE *fptr;

// prompts the user to enter 'y' 'n' for if they want to save to a file
	
	printf("\nSave to a file? (y/n):");
	fgets(user_input, sizeof(user_input), stdin);
	length = strlen(user_input);

// if the user enters anything else, this loop will prompt the user again
	
	while ((length > 2) || (user_input[0] != 'n' && user_input[0] != 'y'))
	{	
		printf("\nError: illegal value");
	    printf("\nSave to a file? (y/n):");
		fgets(user_input, sizeof(user_input), stdin);
		length = strlen(user_input);
	}

// if the user enters 'n', the function will end and return 1 to main
	
	if (user_input[0] == 'n')
	{
		return 1;
	}

// otherwise, it asks the user for the file name, opens that file for writing,
// and writes all data to it before closing the file and returning 1 to main

	else
	{
		printf("\nEnter file name:");
		fgets(file_name, sizeof(file_name), stdin);

// removes the '\n' from the file name created when user hits enter 

		if ((pointer=strchr(file_name, '\n')) != NULL)
		{
			*pointer = '\0';
		}

		fptr = fopen(file_name, "w");

// if the file is unable to be created, prints error message & returns 0

		if (fptr == NULL)
		{
			printf("Error opening file %s\n", file_name);
			return 0;
		}

		fprintf(fptr, "%s", name);
		fprintf(fptr, "Today's date: %s\n", datetime);
		fprintf(fptr, "Decimal: %d", decimal_val);
		fprintf(fptr, "\nHexadecimal: %s", hex_string);
		fprintf(fptr, "\nOctal: %s", oct_string);
		fprintf(fptr, "\nBinary: %s", binary_string);


		fclose(fptr);

		return 1;
	
	}
}
