/*
HW 2
Written with VIM
*/

#include <stdio.h>


// Declares two functions, and variable answer as integers

int get_input(), display(int val), answer;


int main()
{	

		// Variable "newnum" is declared as the output of UDF get_input
		// Variable "answer" is defined as the output of UDF display

		int newnum = get_input();
		answer = display(newnum);

		// if display(newnum) returns 1, it prints below statement 
		// if not, the second statement is printed

		if (answer == 1)
		{
				printf("%d is divisible by 9\n", newnum);
		}

		else
		{
				printf("%d is not divisible by 9\n", newnum);
		}

		return 0;
}

// UDF get_input()

int get_input()
{  	
		int val;

		// Prompts user to enter an integer and saves it as val

		printf("Enter an integer from 1-999999:");
		scanf("%d", &val);

		// If the value is greater than 999999 or less than 1, it asks for another

		while ((1 > val) || (999999 < val))
		{
				printf("Number out of range. ");
				printf("Enter an integer from 1-999999:");
				scanf("%d", &val);
		}
		
		return val;
}

// UDF display()

int display(int num) 
{
		int cool_num, sum_num=0;

		// While the number input to the function is greater than 0, it extracts the
		// rightmost digit, adds it to counter "sum_num", prints the extracted number,
		// and only then does it divide the original number by 10.

		while (num > 0)
		{
				cool_num = (num%10);
				sum_num = sum_num + cool_num;
				printf("%d\n",cool_num);
				num = (num/10);	
		}

		// after the loop is finished, if the sum of the extracted numbers has no
		// remainder when divided by 9, the function returns 1. Else, 0 is returned. 

		if (sum_num % 9 == 0)
		{
				return 1;
		}

		else
		{ 
				return 0;
		}

}

