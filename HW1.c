/* 
   HW 1 
*/


#include <stdio.h>
int main()
{
    int number;
    
   
    
    printf("Enter an integer: ");
    scanf("%d", &number);
    
      
    
    if (number < 0)
    {
    printf("%d is negative.\n", number);
    }
    
    
    
    else if (number == 0)
    {
    printf("%d is zero.\n", number);
    }
    
    
    
    else
    {
    printf("%d is not negative.\n", number);
    }
    
    
    /* If there is a remainder after dividing by 2,
    returns the number followed by 'is odd'. if
    there is no remainder, 'is even' follows. */
    
    if (number % 2 == 0)
    {
    printf("%d is even.\n", number);
    }
    else
    {
    printf("%d is odd.\n", number);
    }
    return 0;
}
