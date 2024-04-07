#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the given character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

// Function to return precedence of operators
int precedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    return -1;
}

// Function to push an element to the stack
void push(struct Stack* stack, char item) {
    if (stack->top == stack->capacity - 1)
        return;
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (stack->top == -1)
        return '\0';
    return stack->array[stack->top--];
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix) {
    struct Stack* stack = createStack(MAX_SIZE);
    int i, j;
    for (i = 0, j = -1; infix[i]; ++i) {
        if (isalnum(infix[i]))
            infix[++j] = infix[i];
        else if (infix[i] == '(')
            push(stack, infix[i]);
        else if (infix[i] == ')') {
            while (stack->top != -1 && stack->array[stack->top] != '(')
                infix[++j] = pop(stack);
            if (stack->top != -1 && stack->array[stack->top] != '(')
                return; // Invalid expression
            else
                pop(stack);
        } else { // Operator
            while (stack->top != -1 && precedence(infix[i]) <= precedence(stack->array[stack->top]))
                infix[++j] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (stack->top != -1)
        infix[++j] = pop(stack);
    infix[++j] = '\0';
    printf("Postfix Expression: %s\n", infix);
    free(stack->array);
    free(stack);
}

int main() {
    char infix[MAX_SIZE];
    printf("Enter the infix expression: ");
    fgets(infix, MAX_SIZE, stdin);


    // Remove newline character if present
    if (infix[strlen(infix) - 1] == '\n')
        infix[strlen(infix) - 1] = '\0';

    infixToPostfix(infix);
    return 0;
}

