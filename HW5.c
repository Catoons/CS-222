/*
 HW 5
 Written with VIM
*/

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct address_t
{
	int octet[4];
	char alias[11];
	struct address_t *next;
};
struct address_t *head = NULL;

void add_address(char user_input[]); 
void lookup_address(); 
void display_list();
void display_aliases(); 
void save_to_file(char name[]);
void insert(int octect[], char alias[]);


int main()
{
	FILE *fptr;
	char name[32], user_input[32], temp[100], temp_alias[32];
	int menu_option, i=0, length=100, t1, t2, t3, t4;

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
// to the linked list.

	while (i < length)
	{
		if (fgets(temp,sizeof(temp),fptr) != NULL)
		{
			sscanf(temp, "%d.%d.%d.%d %s", &t1, &t2, &t3, &t4, temp_alias);

// converts each char of current alias to uppercase

			int s=0;

			while (temp_alias[s])
			{
				temp_alias[s] = toupper(temp_alias[s]);
				s++;
			}

// however, if all the numbers read in the line are zero, it knows that the
// sentinel address has been reached and sets length equal to the number of
// loops that have been executed, which is stored in 'i'

			if (t1 + t2 + t3 + t4  == 0)
			{
				length = i;
			}

// if the sentinel hasn't been reached, data is written to linked list

			else
			{
				int temp_octet[4] = {t1, t2, t3, t4};
				insert(temp_octet, temp_alias);
			}
		}
		++i;
	}

// prompts user for name and displays options 

	printf("Please enter name: ");
	fgets(name, sizeof(name), stdin);

	printf("\n1) Add address\n2) Look up address\n3) Display list\n");
	printf("4) Display aliases for location\n5) Save to file\n6) Quit\n");
	printf("\nEnter menu option (1-6): ");
	scanf("%d", &menu_option);

// runs until the user enters 6 to exit 

	while (menu_option != 6)
	{

// if the user enters a number not between 1-6, prints error and prompts again
// otherwise, the function corresponding to the user's input is run

		while (menu_option < 1 || menu_option > 6)
		{
			printf("Error: Number out of range\n");
			printf("Enter menu option (1-6): ");
			scanf("%d", &menu_option);
		}
	
		if (menu_option == 1)
		{
			add_address(user_input);
			printf("\nEnter menu option (1-6): ");	
			scanf("%d", &menu_option);
		}

		if (menu_option == 2)
		{	
			lookup_address();
			printf("\nEnter menu option (1-6): ");	
			scanf("%d", &menu_option);
		}

		if (menu_option == 3)
		{  
			display_list();
			printf("\nEnter menu option (1-6): ");	
			scanf("%d", &menu_option);
		}

		if (menu_option == 4)
		{
			display_aliases();
			printf("\nEnter menu option (1-6): ");	
			scanf("%d", &menu_option);
		}

		if (menu_option == 5)
		{
			save_to_file(name);
			printf("\nEnter menu option (1-6): ");	
			scanf("%d", &menu_option);
		}
		
	}

// runs if user enters '6'

	printf("\nGoodbye!\n");
		return 0;
}

// ------------------------------------------------------------------------- //
// function to search for a specific user address in the list 

void lookup_address()
{	
	struct address_t *ptr = head;
	char user_input[11];
	int i=0, c;

	printf("\nEnter alias: "); 
	scanf("%s", user_input);

// if the user enters an alias longer than 10 chars, it prints an error

	while  (strlen(user_input) > 10) 
	{
		printf("\nERROR: Illegal alias. Please reenter: ");
		scanf("%s", user_input);
	}

// reads to end of linked list, comparing all aliases to user input

	while (ptr != NULL)
	{
		c = strcmp(user_input, ptr->alias);

// c will be 0 if strcmp finds that both strings are the same
// if it is, this if statement prints out the IP address of that user
		
		if (c==0)
		{
			printf("%d.%d.%d.%d\n", ptr->octet[0], ptr->octet[1], 
							ptr->octet[2], ptr->octet[3]);
			i++;
		}

		ptr = ptr->next;
	}

// if the above statement never runs, "i" will still be zero, and therefore
// it knows that the alias was never found in the list. 
	
	if (i == 0)
	{
		printf("\nERROR: alias not found.\n");
	}

}

// ------------------------------------------------------------------------- //
// function to retrieve and add user address + alias to list 

void add_address(char user_input[])
{	
	char temp_alias[32];
	int t1, t2, t3, t4, c, f=0, i=0;
	struct address_t *ptr = head; 
	
	printf("\nEnter address: ");
	scanf("%s", user_input);

// parses the user input to retrive the individual numbers in IP address and
// assigns them to variables to be used temporarily

	sscanf(user_input, "%d.%d.%d.%d", &t1, &t2, &t3, &t4);

// if any of the numbers of the IP address are not bewtween 0-255,
// an error is printed and the user is prompted to enter an IP again

	while (t1>255 || t1<0 || t2>255 || t2<0 || t3>255 || t3<0 ||t4>255||t4<0)
	{
		printf("\nERROR: Illegal address. Please reenter: ");
		scanf("%s", user_input);
		sscanf(user_input, "%d.%d.%d.%d", &t1, &t2, &t3, &t4);
	}

	printf("Enter alias (10 characters or less): ");
	scanf("%s", temp_alias);

	while (strlen(temp_alias) > 10) 
	{
		printf("\nERROR: Illegal alias. Please reenter: ");
		scanf("%s", temp_alias);
	}

// converts user alias to uppercase

	while (temp_alias[f])
		{
			temp_alias[f] = toupper(temp_alias[f]);
			f++;
		}

// iterates through the whole linked list, comparing aliases to see if the
// user input is already in the list. 

	while (ptr != NULL)
	{
		c = strcmp(temp_alias, ptr->alias);

// if each of the numbers the user gave are the same as one of the IPs in the
// list, it will print and error and increment i to indicate such

		if (t1 == ptr->octet[0] && t2 == ptr->octet[1] && t3 == ptr->octet[2]
						&& t4 == ptr->octet[3])
		{
			printf("\nERROR: Address is already in list.\n");
			i++;
		}

// c will be 0 if strcmp finds that user alias and alias in list are the same
	
		if (c==0)
		{
			printf("\nERROR: Alias is already in list.\n");	
			i++;
		}

		ptr = ptr->next;
	}		

// if no matching aliases or IP addresses are found, input is added to list

	if (i == 0)
	{
		int temp_octet[4] = {t1, t2, t3, t4};
		insert(temp_octet, temp_alias);
	}
}

// ------------------------------------------------------------------------- //
// function to read and display contents of linked list

void display_list() 
{
	int i=0;

// ptr is set to head so it points to the beginning of the linked list
   	
	struct address_t *ptr = head;
	printf("\n");
	
// if nothing has been put in the structure, returns message below

	if (ptr == NULL)
	{
		printf("\nEmpty list\n");
	}

// if there is content in the structure, the data is printed out until
// the end of the file is reached

// i is incremented each loop to keep track of the # of nodes printed

	while(ptr != NULL)
	{
		printf("%d.%d.%d.%d \t%s\n", ptr->octet[0], ptr->octet[1], 
						ptr->octet[2],ptr->octet[3], ptr->alias);

		ptr = ptr->next;

		i++;
	}

// if any nodes have been printed, this loop displaying the # of nodes is run

	if (i > 0)
	{
		printf("\nNumber of nodes: %d\n", i);
	}
}

// ------------------------------------------------------------------------- //
// function to display aliases that match a certain address location 

void display_aliases()
{
	char user_input[10];
	int p1, p2, i=0;
	struct address_t *ptr = head; 

	printf("\nEnter locality: ");
	scanf("%s", user_input);

// parses the user input into two numbers for IP

	sscanf(user_input, "%d.%d", &p1, &p2);

// if any of the numbers are not between 0-255,
// an error is printed and the user is prompted to enter them again

	while (p1>255 || p1<0 || p2>255 || p2<0)
	{
		printf("\nERROR: Illegal address. Please reenter: ");
		scanf("%s", user_input);
		sscanf(user_input, "%d.%d", &p1, &p2);
	}

// until the end of the linked list is reached, this checks if the numbers that
// the user entered match the first two of any of the IP addresses. If so,
// the alias corresponding to that address is printed and "i" is incremented.

		while (ptr != NULL)
	{
		if (p1 == ptr->octet[0] && p2 == ptr->octet[1])
		{
			printf("\n%s", ptr->alias);
			i++;
		}

		ptr = ptr->next;
	}

// this only runs if no addresses with matching locality were found	as i=0
		
	if (i == 0)
	{
		printf("ERROR: No address with that locality exists.");
	}

	printf("\n");
	
}

// ------------------------------------------------------------------------- //
// function to output linked list to file 

void save_to_file(char name[])
{
	char input[32], *pointer;
	int i=0;
	FILE *fptr;
	struct address_t *ptr = head;
	
	getchar();
	printf("\nEnter file name: ");
	fgets(input, sizeof(input), stdin);

//removes the newline char from fgets, replaces it will null 

	if ((pointer=strchr(input, '\n')) != NULL)
	{
		*pointer = '\0';
	}
	
// opens the user file for writing and prints name to first line

	fptr = fopen(input, "w");
	fprintf(fptr, "%s", name);
	

// if the file is unable to be created, prints error message and exits

	if (fptr == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

// prints IP addresses and aliases to file

	while (ptr != NULL)
	{
		fprintf(fptr, "\n%d.%d.%d.%d\t", ptr->octet[0], ptr->octet[1],
						ptr->octet[2], ptr->octet[3]);
		fprintf(fptr, "%s", ptr->alias);
		ptr = ptr->next;
		i++;
	}

// once everything is printed to file, informs user the file has been saved
// and closes the file. 

	if (i>0)
	{
		printf("%s has been saved.\n", input);
	}

	fclose(fptr);
}

// ------------------------------------------------------------------------- //
// function to insert user data into linked list

void insert(int octet[], char alias[])
{

	int i=0;

// allocates the needed memory to add data to linked list

	struct address_t *link=(struct address_t*) malloc(sizeof(struct address_t));

// assigns numbers stored in the passed integer array to the list

	while (i <= 3)
	{
		link->octet[i] = octet[i];
		i++;
	}
	
	i=0;

// does the same for alias, doing one char at a time

	while (i < strlen(alias))
	{
		link->alias[i] = alias[i];
		i++;
	}

// moves to next node in linked list

	link->next = head;
	head = link;
}
