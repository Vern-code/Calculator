// calculator.c
// Added by Usman to practice Git workflow

#include <stdio.h>

int main(void) {
    double a, b;
    char op;

    printf("Enter expression (e.g. 2 + 3): ");
    if (scanf("%lf %c %lf", &a, &op, &b) == 3) {
        if (op == '+') printf("%g\n", a + b);
        else if (op == '-') printf("%g\n", a - b);
        else if (op == '*') printf("%g\n", a * b);
        else if (op == '/') {
            if (b != 0) printf("%g\n", a / b);
            else printf("Error: division by zero\n");
        } else printf("Unsupported operator\n");
    } else {
        printf("Invalid input\n");
    }

    return 0;

    // GitHub edit to practice git pull
}
