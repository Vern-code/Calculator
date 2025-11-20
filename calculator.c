#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // starting wiht a simple logic programme

    int num1;
    int num2;
    char operator;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    do
    {
        printf("Enter one of the following simple operator (+, =, *, /): ");
        scanf(" %c", &operator);

    } while (operator != '+' && operator != '-' && operator != '*' && operator != '/');
    
 
    if (operator == '+')
    {
        printf("The sum of %d and %d = %d\n", num1, num2, num1 + num2);
    }

    else if (operator == '-')
    {
        printf("The difference between %d and %d = %d\n", num1, num2, num1 - num2);
    }
    
    else if (operator == '*')
    {
        printf("The product of %d and %d = %d\n", num1, num2, num1 * num2);
    }
    
    else if (operator == '/')
    {
        printf("The division of %d by %d = %d\n", num1, num2, num1 / num2);
    }



    

    

    return 0;
}