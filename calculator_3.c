#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char input[100];
    double numbers[100];
    char operators[100];
    int num_index = 0, op_index = 0;
    char temp_buffer[50];
    int temp_index = 0;
    char *ptr;

    // Get input
    printf("Enter expression to solve: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Parse input into numbers and operators
    for (int i = 0; i < strlen(input); i++) {
        if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
            temp_buffer[temp_index++] = input[i];
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            temp_buffer[temp_index] = '\0';
            numbers[num_index++] = strtod(temp_buffer, &ptr);

            operators[op_index++] = input[i];

            temp_index = 0;
            temp_buffer[0] = '\0';
        }
    }

    // Handle last number
    if (temp_index > 0) {
        temp_buffer[temp_index] = '\0';
        numbers[num_index++] = strtod(temp_buffer, &ptr);
    }

    // Step 1: Handle * and / first
    for (int i = 0; i < op_index; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            double temp;
            if (operators[i] == '*') temp = numbers[i] * numbers[i + 1];
            else {
                if (numbers[i + 1] == 0) {
                    printf("Error: Division by zero!\n");
                    return 1;
                }
                temp = numbers[i] / numbers[i + 1];
            }

            numbers[i] = temp;

            // Shift numbers left
            for (int j = i + 1; j < num_index - 1; j++)
                numbers[j] = numbers[j + 1];
            num_index--;

            // Shift operators left
            for (int j = i; j < op_index - 1; j++)
                operators[j] = operators[j + 1];
            op_index--;

            i--; // recheck current position
        }
    }

    // Step 2: Handle + and - left to right
    double result = numbers[0];
    for (int i = 0; i < op_index; i++) {
        if (operators[i] == '+') result += numbers[i + 1];
        else if (operators[i] == '-') result -= numbers[i + 1];
    }

    printf("RESULT: %.3f\n", result);
    return 0;
}
