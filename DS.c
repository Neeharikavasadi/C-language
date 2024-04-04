#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

char peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return '$';
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void infixToPostfix(char* expression) {
    struct Stack* stack = createStack(strlen(expression));
    int i, k;

    printf("Step-by-step process for Infix to Postfix conversion:\n\n");

    for (i = 0, k = -1; expression[i]; ++i) {
        printf("Current Token: %c\n", expression[i]);
        if (isalnum(expression[i])) {
            printf("Appending to Output: %c\n\n", expression[i]);
            expression[++k] = expression[i];
        } else if (expression[i] == '(') {
            printf("Pushing '(' to Stack\n\n");
            push(stack, expression[i]);
        } else if (expression[i] == ')') {
            printf("Encountered ')', Popping and Appending to Output until '(' is found\n\n");
            while (!isEmpty(stack) && peek(stack) != '(')
                expression[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(') {
                printf("Invalid Expression\n");
                return;
            } else {
                pop(stack); // Discard '(' from stack
            }
        } else {
            printf("Operator Encountered: %c\n", expression[i]);
            printf("Comparing Operator Precedence and Popping Operators from Stack\n");
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack))) {
                printf("Popping Operator: %c\n", peek(stack));
                expression[++k] = pop(stack);
            }
            printf("Pushing Current Operator to Stack\n\n");
            push(stack, expression[i]);
        }
    }

    while (!isEmpty(stack)) {
        printf("Popping Remaining Operators from Stack\n");
        expression[++k] = pop(stack);
    }

    expression[++k] = '\0';
    printf("Final Postfix Expression: %s\n", expression);
}

void infixToPrefix(char* expression) {
    struct Stack* stack = createStack(strlen(expression));
    int i, k;

    printf("\nStep-by-step process for Infix to Prefix conversion:\n\n");

    // Reverse the infix expression
    int len = strlen(expression);
    for (i = 0; i < len / 2; i++) {
        char temp = expression[i];
        expression[i] = expression[len - i - 1];
        expression[len - i - 1] = temp;
    }

    for (i = 0; expression[i]; ++i) {
        printf("Current Token: %c\n", expression[i]);
        if (isalnum(expression[i])) {
            printf("Appending to Output: %c\n\n", expression[i]);
            expression[++k] = expression[i];
        } else if (expression[i] == ')') {
            printf("Pushing ')' to Stack\n\n");
            push(stack, expression[i]);
        } else if (expression[i] == '(') {
            printf("Encountered '(', Popping and Appending to Output until ')' is found\n\n");
            while (!isEmpty(stack) && peek(stack) != ')')
                expression[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != ')') {
                printf("Invalid Expression\n");
                return;
            } else {
                pop(stack); // Discard ')' from stack
            }
        } else {
            printf("Operator Encountered: %c\n", expression[i]);
            printf("Comparing Operator Precedence and Popping Operators from Stack\n");
            while (!isEmpty(stack) && precedence(expression[i]) < precedence(peek(stack))) {
                printf("Popping Operator: %c\n", peek(stack));
                expression[++k] = pop(stack);
            }
            printf("Pushing Current Operator to Stack\n\n");
            push(stack, expression[i]);
        }
    }

    while (!isEmpty(stack)) {
        printf("Popping Remaining Operators from Stack\n");
        expression[++k] = pop(stack);
    }

    expression[++k] = '\0';

    // Reverse the resultant expression to get prefix
    len = strlen(expression);
    for (i = 0; i < len / 2; i++) {
        char temp = expression[i];
        expression[i] = expression[len - i - 1];
        expression[len - i - 1] = temp;
    }

    printf("Final Prefix Expression: %s\n", expression);
}

// (Previous code remains unchanged)

int main() {
    char expression[MAX_SIZE];
    int choice;
    char continueChoice;

    do {
        printf("Enter an infix expression: ");
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n\n\n")] = '\0';

        printf("Choose conversion:\n1. Infix to Postfix\n2. Infix to Prefix\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                infixToPostfix(expression);
                printf("___________________\n\n");
                break;
            case 2:
                infixToPrefix(expression);
                printf("___________________\n\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }

        printf("Do you want to continue? (Y/N): ");
        scanf("%c", &continueChoice);
        getchar(); // Consume newline character

    } while (continueChoice == 'Y' || continueChoice == 'y');
    if(continueChoice == 'n' || continueChoice == 'N')
    {
        printf("Exit");
    }

return 0;
}