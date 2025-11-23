#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char input[100];

    printf("Enter expression to solve: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char *token;
    const char delim[] = " ";

    token = strtok(input, delim);  // get first token

    double result;
    char current_operator = '+';  // default operator
    double num;
    char *ptr;

    // First token should always be a number → initialize result
    result = strtod(token, &ptr);

    // Advance to the next token before the loop
    token = strtok(NULL, delim);

    while(token != NULL)
    {
        // If the token is an operator, store it
        if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
        {
            current_operator = token[0];
        }
        else
        {
            // Token is a number → convert and apply the stored operator
            num = strtod(token, &ptr);

            if (current_operator == '+') result += num;
            else if (current_operator == '-') result -= num;
            else if (current_operator == '*') result *= num;
            else if (current_operator == '/')
            {
                if(num != 0)
                    result /= num;
                else
                {
                    printf("Error: Division by zero!\n");
                    return 1;
                }
            }
        }

        // Move to the next token
        token = strtok(NULL, delim);
    }

    printf("RESULT: %.2f\n", result);  // 6 decimal places

    return 0;
}
