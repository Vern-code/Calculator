#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_operator(char c);
int is_digit_or_decimal(char c);

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
    for (int i = 0; i < strlen(input); i++)
    {

        if (input[i] == ' ') 
        {
            continue;
        }
        


        // ------------------------
        // DEALING WITH BRACKETS
        //-----------------------
        if (input[i] == '(')
        {
            int start = i + 1;
            int end = start;

            // --- If there's a pending number in temp_buffer before '(' -> store it first ---
            if (temp_index > 0)
            {
                temp_buffer[temp_index] = '\0';
                numbers[num_index] = strtod(temp_buffer, &ptr);
                num_index++;
                // reset main temp buffer
                temp_index = 0;
                temp_buffer[0] = '\0';
            }

            // --- Insert implied multiplication BEFORE bracket if previous token is not an operator ---
            if (num_index > 0)
            {
                // if previous char is NOT an operator (so it's a digit or ')'), insert '*'
                if (i > 0 && !is_operator(input[i - 1]))
                {
                    operators[op_index] = '*';
                    op_index++;
                }
            }

            // Temporary buffer and counters for inside the bracket
            char brac_temp_buffer[100];
            int brac_temp_index = 0;
            double brac_numbers[100];
            char brac_operators[100];
            int brac_num_count = 0;
            int brac_op_count = 0;

            // Scan until closing ')'
            while (input[end] != ')' && input[end] != '\0')
            {
                // Unary +/-
                if ((input[end] == '-' || input[end] == '+') &&
                    (end == start || is_operator(input[end - 1])))
                {
                    int minus_count = 0;
                    while (input[end] == '+' || input[end] == '-')
                    {
                        if (input[end] == '-') minus_count++;
                        end++;
                    }

                    brac_temp_buffer[brac_temp_index] = (minus_count % 2 == 0) ? '+' : '-';
                    brac_temp_index++;
                    continue;
                }

                // Digit or decimal
                if (is_digit_or_decimal(input[end]))
                {
                    brac_temp_buffer[brac_temp_index] = input[end];
                    brac_temp_index++;
                    end++;
                    continue;
                }

                // Operator inside bracket
                if (is_operator(input[end]))
                {
                    brac_temp_buffer[brac_temp_index] = '\0';
                    brac_numbers[brac_num_count] = strtod(brac_temp_buffer, NULL);
                    brac_num_count++;

                    brac_operators[brac_op_count] = input[end];
                    brac_op_count++;

                    brac_temp_index = 0;
                    brac_temp_buffer[0] = '\0';

                    end++;
                    continue;
                }

                // Ignore other characters
                end++;
            }

            // Last number in bracket
            if (brac_temp_index > 0)
            {
                brac_temp_buffer[brac_temp_index] = '\0';
                brac_numbers[brac_num_count] = strtod(brac_temp_buffer, NULL);
                brac_num_count++;
            }

            // Evaluate * and /
            for (int j = 0; j < brac_op_count; j++)
            {
                if (brac_operators[j] == '*' || brac_operators[j] == '/')
                {
                    double temp;
                    if (brac_operators[j] == '*') temp = brac_numbers[j] * brac_numbers[j + 1];
                    else
                    {
                        if (brac_numbers[j + 1] == 0) { printf("Division by zero!\n"); return 1; }
                        temp = brac_numbers[j] / brac_numbers[j + 1];
                    }
                    brac_numbers[j] = temp;

                    // Shift left
                    for (int k = j + 1; k < brac_num_count - 1; k++) brac_numbers[k] = brac_numbers[k + 1];
                    brac_num_count--;
                    for (int k = j; k < brac_op_count - 1; k++) brac_operators[k] = brac_operators[k + 1];
                    brac_op_count--;
                    j--;
                }
            }

            // Evaluate + and -
            double brac_result = brac_numbers[0];
            for (int j = 0; j < brac_op_count; j++)
            {
                if (brac_operators[j] == '+') brac_result += brac_numbers[j + 1];
                else if (brac_operators[j] == '-') brac_result -= brac_numbers[j + 1];
            }

            // Store bracket result
            numbers[num_index] = brac_result;
            num_index++;

            // Move parser index to closing ')'
            i = end;
            i++; // continue from next char
            continue;
        }





        // ------------------------------------
        // GENERAL UNARY PLUS AND MINUS
        // ---------------------------------
        if ((input[i] == '-' || input[i] == '+') &&
            (i == 0 || is_operator(input[i - 1]))) 
        {

            int minus_count = 0;

            while (input[i] == '+' || input[i] == '-') 
            {
                if (input[i] == '-')
                {
                    minus_count++;
                }
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
            if (!(is_digit_or_decimal(input[i])))
            {
                printf("Invalid expression after sign sequence!\n");
                return 1;
            }

            i--; 
            continue;
        }

        // If digit or decimal point → add to temp buffer
        else if (is_digit_or_decimal(input[i])) 
        {
            temp_buffer[temp_index] = input[i];
            temp_index++;
            continue;
        }

        // If operator
        else if (is_operator(input[i])) 
        {
            // Check if two invalid operators occur in a row
            if (i > 0 && is_operator(input[i - 1])) {
        
            // Allow ONLY valid unary signs (-,+) after another operator
                if (!((input[i] == '+' || input[i] == '-') 
                && (input[i-1] == '+' || input[i-1] == '-' ))) 
                {
                    printf("Invalid operator sequence near '%c%c'\n", input[i-1], input[i]);
                    return 1;
                }
            }

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

        else if (input[i] == '(' || input[i] == ')')
        {
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

int is_operator(char c)
{
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

int is_digit_or_decimal(char c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.': 
        return 1; 
    default:
        return 0;
    }
}

