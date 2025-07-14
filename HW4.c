/*
 HW 4
 Written with VIM, from Kauai island :)
*/
 
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


char *getDateAndTime();
int read_data_file(char filename[], int length);
void bubble_sort(int length);
void generate_alias_list(char name[], char datetime[], int length);

// structure that will be used to store parts of IP address + alias

struct address_t 
{
	int p1;
	int p2;
	int p3; 
	int p4; 
	char as[32]; 
};

// an array of 100 address_t structures, to store up to 100 IPs+aliases

struct address_t list_add[100]; 

int main() 
{

	char datetime[32], name[32], filename[32] = " CS222_Inet.txt";  
	int length = 100;

//prompts user to enter name and saves it as variable 'name'

	printf("Enter name:");
	fgets(name, sizeof(name), stdin);

// calling the functions that are defined & explained below. 
	
	strcpy(datetime, getDateAndTime());
	length = read_data_file(filename, length);
	bubble_sort(length);
	generate_alias_list(name, datetime, length); 

	
}

char *getDateAndTime() // gets date and time and returns it as 'datetime'
{
	time_t datetime;
	time(&datetime);
	return ctime(&datetime);
}

// function to read the unsorted IP addresses 

int read_data_file(char filename[], int length) // DONE, but remove print statements later 
{
	FILE *fptr;
	int i=0;

// 'tmp' is used to store a single line at a time from the file to be read

	char tmp[132];

//opens the IP adress file to be read from 
	
	fptr = fopen("CS222_Inet.txt", "r");

// if file is unable to be opened, process is ended

	if (fptr == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

// iterates through the whole file until it reaches the end. variable 'length'
// is set to 100 by default, so this loop can run up to 100 times if needed.

// each loop stores each number and alias from the current line of the IP list
// to the structure array declared earlier. 
	
	while (i < length)
	{
		if (fgets(tmp,sizeof(tmp),fptr) != NULL)
		{
			sscanf(tmp, "%d.%d.%d.%d %s", &list_add[i].p1,
							&list_add[i].p2, &list_add[i].p3,
							&list_add[i].p4, list_add[i].as);
			
// however, if all the numbers read in the line are zero, it knows that the
// sentinel address has been reached and sets length equal to the number of
// loops that have been executed, which is stored in 'i'	

			if (list_add[i].p1+list_add[i].p2+list_add[i].p3+list_add[i].p4 == 0)
			{
				
			length = i;

			}	
		}
		
		++i;	
		
	} 

// once iteration is complete, file is closed and 'length' is returned with
// the number of lines that will need to be written to the output file

	fclose(fptr);
	return length;
	
}

// function to sort IPs by alias

void bubble_sort(int length)
{
	int c = 0, i= 0, cmp = 0;
	char temp_name[32]; // temporary string to store name
	char user_input[32]; // stores user input 
	int t1, t2, t3, t4; // temp storage for numbers

// asks user how they want the output to be ordered 

	printf("\nSort in ascending or descending order? (enter 'a' or 'd'):");
	fgets(user_input, sizeof(user_input), stdin);

// if the user enters anything else than a or d it prompts them again

	while ((user_input[0] != 'a' && user_input[0] != 'd'))
	{
		printf("\nError: illegal value");
		printf("\nSort in ascending or descending order? (enter 'a' or 'd'):");
		fgets(user_input, sizeof(user_input), stdin);

	}

// these two loops iterate through the entire list each time they are run.
	

	while (c < length -1)
	{
		while (i < length -1)
		{

// the alias in the current loop is compared to the one after it. If it is
// first alphabetically, 'cmp' will be 1, if second, cmp is -1

			cmp = strcmp(list_add[i].as, list_add[i+1].as);

// sorts in ascending order 

			if (user_input[0] == 'a')
			{	

				if (cmp > 0) 
				{

// the alias and IP address of the current loop is stored in these variables
// while the original values get overwritten

					strcpy(temp_name, list_add[i].as);
					t1 = list_add[i].p1;
					t2 = list_add[i].p2;
					t3 = list_add[i].p3;
					t4 = list_add[i].p4;

// moves aliases & numbers down the list by 1

					strcpy(list_add[i].as, list_add[i+1].as);
					list_add[i].p1 = list_add[i+1].p1;
	      	 		list_add[i].p2 = list_add[i+1].p2;
					list_add[i].p3 = list_add[i+1].p3;
	      	 		list_add[i].p4 = list_add[i+1].p4;

// sets the next aliases + IP to 1 place higher than before
		
					strcpy(list_add[i+1].as, temp_name);
					list_add[i+1].p1 = t1;
	      		 	list_add[i+1].p2 = t2;
					list_add[i+1].p3 = t3;
	     	  		list_add[i+1].p4 = t4;
				
				}
 			}

// sorts in descending order 
			
			if (user_input[0] == 'd')
			{	

				if (cmp < 0) // if second is greater than first
				{
					strcpy(temp_name, list_add[i].as);
					t1 = list_add[i].p1;
					t2 = list_add[i].p2;
					t3 = list_add[i].p3;
					t4 = list_add[i].p4;

					strcpy(list_add[i].as, list_add[i+1].as);
					list_add[i].p1 = list_add[i+1].p1;
	      	 		list_add[i].p2 = list_add[i+1].p2;
					list_add[i].p3 = list_add[i+1].p3;
	      	 		list_add[i].p4 = list_add[i+1].p4;
		
					strcpy(list_add[i+1].as, temp_name);
					list_add[i+1].p1 = t1;
	      		 	list_add[i+1].p2 = t2;
					list_add[i+1].p3 = t3;
	     	  		list_add[i+1].p4 = t4;
				
				}
 			}

			i++;
		}

        i=0; // i is reset to 0 so loop can start again 
		c++; // c is incremented by 1
	}
}

void generate_alias_list(char name[], char datetime[], int length) 
{
	char user_input[32];
	int i=0, s=0;
	FILE *fptr;
	
	fptr = fopen("222_Alias_List.txt", "w");

// if the file is unable to be created, prints error message and exits

	if (fptr == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

// Name, date, and title printed at top of the file 

	fprintf(fptr, "%s%sCS222 Network Alias Listing\n\n", name, datetime);

	while (i < length)
	{

// converts every character of each alias to upper case one at a time 

		s=0;
		while (list_add[i].as[s])
			{
				list_add[i].as[s] = toupper(list_add[i].as[s]);
				s++;
			}

// prints IP addresses and uppercased aliases to file 

		fprintf(fptr, "%s", list_add[i].as);
		fprintf(fptr, "     %d.%d.%d.%d\n", list_add[i].p1,list_add[i].p2,
						list_add[i].p3, list_add[i].p4);
		i++;
	}

	fclose(fptr);

}

