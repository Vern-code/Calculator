#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_operator(char c);

int main(void) {
    char input[100];
    double numbers[100];
    char operators[100];
    int num_index = 0, op_index = 0;
    char temp_buffer[50];
    int temp_index = 0;
    char *ptr;

    printf("Enter expression to solve: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Check if input is empty or contains only spaces
    int has_expression = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ') {
            has_expression = 1;
            break;
        }
    }

    if (!has_expression) {
        printf("No expression detected. End of program!\n");
        return 0;
    }

    // ----------------------------
    // PARSE INPUT
    // ----------------------------
    for (int i = 0; i < strlen(input); i++) {

        if (input[i] == ' ') {
            continue;
        }
        
        // Unary minus or unary plus
        if ((input[i] == '-' || input[i] == '+') &&
            (i == 0 || is_operator(input[i - 1]))) 
        {

            int minus_count = 0;

            while (input[i] == '+' || input[i] == '-') 
            {
                if (input[i] == '-')
                    minus_count++;

                i++;   // move to next character
            }

            if (minus_count % 2 == 0)
            {
                temp_buffer[temp_index] = '+';
            }
            else
            {
                temp_buffer[temp_index] = '-';
            }
            
            temp_index++;

             // Now input[i] should be a digit or decimal
            if (!((input[i] >= '0' && input[i] <= '9') || input[i] == '.'))
            {
                printf("Invalid expression after sign sequence!\n");
                return 1;
            }

            i--; 
            continue;
        }

        // If digit or decimal point → add to temp buffer
        else if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') 
        {
            temp_buffer[temp_index] = input[i];
            temp_index++;
            continue;
        }

        // If operator
        else if (is_operator(input[i])) 
        {
            // Close number string
            temp_buffer[temp_index] = '\0';

            // Convert + store
            numbers[num_index] = strtod(temp_buffer, &ptr);
            num_index++;

            // Store operator
            operators[op_index] = input[i];
            op_index++;

            // Reset temp buffer
            temp_index = 0;
            temp_buffer[0] = '\0';
            
            continue;
        }

        else
        {
            // dealing with non-numbers / operators
            printf("Invalid input. Only numbers and operators (+,-,*,/) allowed!\n");
            return 1;
        }
    }

    // Store last number
    if (temp_index > 0) {
        temp_buffer[temp_index] = '\0';
        numbers[num_index] = strtod(temp_buffer, &ptr);
        num_index++;
    }

    // ----------------------------
    // HANDLE * and /
    // ----------------------------
    for (int i = 0; i < op_index; i++) {

        if (operators[i] == '*' || operators[i] == '/') 
        {
            // check for invalid multiplications and divisions sequence
            if (operators[i + 1] == '*' || operators[i + 1] == '/')
            {
                printf("Invalid expression: two * or / operators in a row!\n");
                return 1;
            }
            
            double temp;

            if (operators[i] == '*')
                temp = numbers[i] * numbers[i + 1];
            else if (operators[i] == '/' ) 
            {
                if (numbers[i + 1] == 0) {
                    printf("Error: Division by zero!\n");
                    return 1;
                }
                temp = numbers[i] / numbers[i + 1];
            }

            numbers[i] = temp;

            // Shift numbers left
            for (int j = i + 1; j < num_index - 1; j++) {
                numbers[j] = numbers[j + 1];
            }
            num_index--;

            // Shift operators left
            for (int j = i; j < op_index - 1; j++) {
                operators[j] = operators[j + 1];
            }
            op_index--;

            i--; // Check same index again

        }
    }

    // ----------------------------
    // HANDLE + and -
    // ----------------------------
    double result = numbers[0];

    for (int i = 0; i < op_index; i++) 
    {
        if (operators[i] == '+')
            result += numbers[i + 1];
        else if (operators[i] == '-')
            result -= numbers[i + 1];
    }
   
    
    printf("RESULT: %.3f\n", result);

    return 0;
}

int is_operator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;   // TRUE → it IS an operator
        default:
            return 0;   // FALSE → NOT an operator
    }
}
