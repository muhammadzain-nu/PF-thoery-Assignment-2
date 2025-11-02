#include <stdio.h>
#include <string.h>

#define mxbooks 100
#define length 50
#define threshold 5

void addnewbook(int isbns[], char titles[][length], float prices[], int quantities[], int *bookCount);
void processsale(int isbns[], int quantities[], int bookCount);
void lowstockreport(int isbns[], char titles[][length], float prices[], int quantities[], int bookCount);
int findbook(int isbns[], int bookCount, int isbn);

int main() {
    int isbns[mxbooks];
    char titles[mxbooks][length];
    float prices[mxbooks];
    int quantities[mxbooks];
    int bookCount = 0;
    int choice;

    do {
        printf("\nPlease Enter your Choice:\n");
        printf("1) Add New Book\n");
        printf("2) Process a Sale\n");
        printf("3) Make a Low Stock Report\n");
        printf("4) Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addnewbook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processsale(isbns, quantities, bookCount);
                break;
            case 3:
                lowstockreport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}


void addnewbook(int isbns[], char titles[][length], float prices[], int quantities[], int *bookCount) {
    if (*bookCount >= mxbooks) {
        printf("Inventory full! Cannot add more books.\n");
        return;
    }

    int isbn;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);
    getchar();

    if (findbook(isbns, *bookCount, isbn) != -1) {
        printf("Error: A book with this ISBN already exists!\n");
        return;
    }

    isbns[*bookCount] = isbn;

    printf("Enter the Title: ");
    fgets(titles[*bcount], length, stdin);
    titles[*bcount][strcspn(titles[*bcount], "\n")] = '\0'; // remove newline

    printf("Enter price: ");
    scanf("%f", &prices[*bcount]);

    printf("Enter quantity: ");
    scanf("%d", &quantities[*bcount]);

    (*bcount)++;
    printf("Book added successfully!\n");
}

void processsale(int isbns[], int quantities[], int bcount) {
    int isbn, soldQty;
    printf("Enter ISBN of book sold: ");
    scanf("%d", &isbn);

    int index = findbook(isbns, bcount, isbn);
    if (index == -1) {
        printf("Book not found!\n");
        return;
    }

    printf("Enter number of copies sold: ");
    scanf("%d", &soldQty);

    if (quantities[index] == 0) {
        printf("Out of stock!\n");
    } else if (soldQty > quantities[index]) {
        printf("Not enough copies in stock! Only %d available.\n", quantities[index]);
    } else {
        quantities[index] -= soldQty;
        printf("Sale processed. Remaining stock: %d\n", quantities[index]);
    }
}

void lowstockreport(int isbns[], char titles[][length], float prices[], int quantities[], int bcount) {
    int found = 0;
    printf("\n=== Low-Stock Report (Below %d) ===\n", threshold);
    printf("%-10s %-30s %-10s %-10s\n", "ISBN", "Title", "Price", "Quantity");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < bcount; i++) {
        if (quantities[i] < threshold) {
            printf("%-10d %-30s %-10.2f %-10d\n", isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No low-stock books found.\n");
    }
}

int findbook(int isbns[], int bcount, int isbn) {
    for (int i = 0; i < bcount; i++) {
        if (isbns[i] == isbn)
            return i;
    }
    return -1;
}