#include <stdio.h>
#define MAX 5   

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int stack[MAX], top = -1, choice;

    do {
        printf("\n===== STACK MENU =====");
        printf("\n1. PUSH");
        printf("\n2. POP");
        printf("\n3. PEEK");
        printf("\n4. DISPLAY");
        printf("\n5. EXIT");
        printf("\n=======================");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: push(stack, &top, MAX); break;
            case 2: pop(stack, &top); break;
            case 3: peek(stack, top); break;
            case 4: display(stack, top); break;
            case 5: printf("\nExiting program...\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while(choice != 5);

    return 0;
}

void push(int stack[], int *top, int maxSize) {
    int value;

    if(*top == maxSize - 1) {
        printf("\nStack Overflow! Cannot push element.\n");
    } else {
        printf("Enter value to PUSH: ");
        scanf("%d", &value);
        (*top)++;
        stack[*top] = value;
        printf("Element %d pushed successfully.\n", value);
    }
}

void pop(int stack[], int *top) {
    if(*top == -1) {
        printf("\nStack Underflow! No element to pop.\n");
    } else {
        printf("Popped element: %d\n", stack[*top]);
        (*top)--;
    }
}

void peek(int stack[], int top) {
    if(top == -1) {
        printf("\nStack is empty! Nothing to peek.\n");
    } else {
        printf("Top element is: %d\n", stack[top]);
    }
}

void display(int stack[], int top) {
    if(top == -1) {
        printf("\nStack is empty!\n");
    } else {
        printf("\nStack elements:\n");
        for(int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}
