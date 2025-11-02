#include <stdio.h>
#include <string.h> 

void encodeMessage(char msg[]);
void decodeMessage(char msg[]);
void reverseString(char msg[]);
char toggleBits(char ch);
void inputString(char msg[]);

int main() {
    int choice;
    char message[200];

    do {
        printf("\n===== TCS Secure Message System =====\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch(choice) {
            case 1:
                printf("\nEnter message to ENCODE: ");
                inputString(message);
                encodeMessage(message);
                printf("\nEncoded Message: %s\n", message);
                break;

            case 2:
                printf("\nEnter message to DECODE: ");
                inputString(message);
                decodeMessage(message);
                printf("\nDecoded Message: %s\n", message);
                break;

            case 3:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while(choice != 3);

    return 0;
}

void inputString(char msg[]) {
    scanf("%[^\n]", msg);
    getchar();
	    msg[strcspn(msg, "\n")] = 0;
}

void reverseString(char msg[]) {
    int i, j;
    char temp;
    for(j = 0; msg[j] != '\0'; j++);
    j--;

    for(i = 0; i < j; i++, j--) {
        temp = msg[i];
        msg[i] = msg[j];
        msg[j] = temp;
    }
}

char toggleBits(char ch) {
    ch ^= (1 << 1);
    ch ^= (1 << 4);
    return ch;
}

void encodeMessage(char msg[]) {
    int i;
    reverseString(msg);
    for(i = 0; msg[i] != '\0'; i++) {
        msg[i] = toggleBits(msg[i]);
    }
}

void decodeMessage(char msg[]) {
    int i;
    for(i = 0; msg[i] != '\0'; i++) {
        msg[i] = toggleBits(msg[i]);
    }
    reverseString(msg);
}
