#include <stdio.h>
#include <string.h>

#define MP 4
#define MCI 10

int productCodes[MP] = {1, 2, 3, 4};
char productNames[MP][20] = {"Milk", "Bread", "Eggs", "Cereal"};
int quantities[MP] = {50, 10, 20, 8};
float prices[MP] = {100, 200, 300, 150};

int cartCodes[MCI];
int cartQty[MCI];
int cartCount = 0;

char customerName[50], customerCNIC[20];

float subTotal = 0, finalTotal = 0, discount = 0;

void getCustomerInfo();
void displayMenu();
void displayInventory();
int findProductIndex(int code);
void updateInventory(int code, int qty);
void addToCart();
void displayTotalBill();
void printInvoice();
void exitSystem();

int main() {
    int choice;
    getCustomerInfo();

    do {
        displayMenu();
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayInventory(); break;
            case 2: addToCart(); break;
            case 3: displayTotalBill(); break;
            case 4: printInvoice(); break;
            case 5: getCustomerInfo(); break;
            case 6: exitSystem(); break;
            default: printf("\nInvalid choice! Try again.\n");
        }
    } while(choice != 6);

    return 0;
}


void getCustomerInfo() {
    printf("\n--- Enter Customer Information ---\n");
    
    while(getchar()!='\n');
    printf("Enter Name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName,"\n")] = 0;

    printf("Enter CNIC: ");
    fgets(customerCNIC, sizeof(customerCNIC), stdin);
    customerCNIC[strcspn(customerCNIC,"\n")] = 0;

    printf("Customer details saved.\n");
}


void displayMenu() {
    printf("\n===== SUPERMARKET MENU =====");
    printf("\n1. Display Inventory");
    printf("\n2. Add to Cart");
    printf("\n3. Display Total Bill");
    printf("\n4. Show Invoice");
    printf("\n5. Re-enter Customer Info");
    printf("\n6. Exit");
    printf("\n============================");
}


void displayInventory() {
    printf("\n------ Inventory ------\n");
    printf("Code | Name   | Qty | Price\n");
    printf("----------------------------\n");

    for(int i=0;i<MP;i++) {
        printf("%d\t%s\t%d\t%.2f\n",
            productCodes[i], productNames[i], quantities[i], prices[i]);
    }
}


int findProductIndex(int code) {
    for(int i=0;i<MP;i++)
        if(productCodes[i] == code) return i;
    return -1;
}


void updateInventory(int code, int qty) {
    int idx = findProductIndex(code);
    if(idx != -1) quantities[idx] -= qty;
}


void addToCart() {
    if(cartCount >= MCI) {
        printf("\nCart Full! Checkout first.\n");
        return;
    }

    int code, qty;
    printf("\nEnter product code: ");
    scanf("%d", &code);

    int idx = findProductIndex(code);
    if(idx == -1) {
        printf("Invalid product code.\n");
        return;
    }

    printf("Enter quantity (Stock: %d): ", quantities[idx]);
    scanf("%d", &qty);

    if(qty <= 0 || qty > quantities[idx]) {
        printf("Invalid quantity.\n");
        return;
    }

    cartCodes[cartCount] = code;
    cartQty[cartCount] = qty;
    cartCount++;

    updateInventory(code, qty);
    printf("Added to cart!\n");
}


void displayTotalBill() {
    if(cartCount == 0) {
        printf("\nCart empty.\n");
        return;
    }

    subTotal = 0; discount = 0;

    printf("\n----- BILL -----\n");
    printf("Item | Qty | Price | Total\n");
    printf("----------------------------\n");

    for(int i=0;i<cartCount;i++) {
        int code = cartCodes[i], qty = cartQty[i];
        int idx = findProductIndex(code);
        float line = prices[idx] * qty;
        subTotal += line;
        printf("%s  %d   %.2f   %.2f\n", productNames[idx], qty, prices[idx], line);
    }

    while(getchar()!='\n');
    char promo[20];
    printf("\nEnter promo code (if any): ");
    fgets(promo, sizeof(promo), stdin);
    promo[strcspn(promo,"\n")] = 0;

    if(strcmp(promo,"Eid2025")==0) {
        discount = subTotal * 0.25;
        printf("Promo applied! 25%% OFF\n");
    }

    finalTotal = subTotal - discount;
    printf("\nSub Total: %.2f", subTotal);
    printf("\nDiscount:  %.2f", discount);
    printf("\nFinal Total: %.2f\n", finalTotal);
}


void printInvoice() {
    if(cartCount == 0) {
        printf("\nAdd items first.\n");
        return;
    }

    printf("\n========== INVOICE ==========\n");
    printf("Customer: %s\nCNIC: %s\n", customerName, customerCNIC);
    printf("------------------------------\n");

    for(int i=0;i<cartCount;i++) {
        int idx = findProductIndex(cartCodes[i]);
        printf("%s x %d = %.2f\n",
            productNames[idx], cartQty[i], prices[idx] * cartQty[i]);
    }

    printf("------------------------------\n");
    printf("Subtotal: %.2f\nDiscount: %.2f\nPayable: %.2f\n", subTotal, discount, finalTotal);
    printf("Thank you for shopping!\n");
}


void exitSystem() {
    printf("\nExiting... Goodbye!\n");
}
