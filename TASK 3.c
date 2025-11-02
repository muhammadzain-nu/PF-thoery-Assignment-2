#include <stdio.h>

#define ROWS 3
#define COLS 3

#define POWER 0        
#define OVERLOAD 1     
#define MAINT 2      

void displayMenu();
void updateSector(int grid[ROWS][COLS]);
void querySector(int grid[ROWS][COLS]);
void runDiagnostics(int grid[ROWS][COLS]);

int main() {
    int grid[ROWS][COLS] = {0};  
    int choice;

    do {
        displayMenu();
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: updateSector(grid); break;
            case 2: querySector(grid); break;
            case 3: runDiagnostics(grid); break;
            case 4: printf("\nExiting system, Goodbye!\n"); break;
            default: printf("\nInvalid choice try again.\n");
        }

    } while(choice != 4);

    return 0;
}

void displayMenu() {
    printf("\n====== IESCO GRID SYSTEM ======");
    printf("\n1. Update Sector Status");
    printf("\n2. Query Sector Status");
    printf("\n3. Run System Diagnostic");
    printf("\n4. Exit");
    printf("\n================================");
}

void updateSector(int grid[ROWS][COLS]) {
    int r, c, bit, value;

    printf("\nEnter row (0-%d): ", ROWS-1);
    scanf("%d", &r);
    printf("Enter column (0-%d): ", COLS-1);
    scanf("%d", &c);

    if(r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        printf("\nInvalid coordinates!\n");
        return;
    }

    printf("Select Status Bit (0=Power, 1=Overload, 2=Maintenance): ");
    scanf("%d", &bit);

    printf("Set(1) or Clear(0)?: ");
    scanf("%d", &value);

    if(value == 1)
        grid[r][c] |= (1 << bit);  
    else
        grid[r][c] &= ~(1 << bit); 

    printf("\nStatus updated successfully.\n");
}

void querySector(int grid[ROWS][COLS]) {
    int r, c;

    printf("\nEnter row: ");
    scanf("%d", &r);
    printf("\nEnter column: ");
    scanf("%d", &c);

    if(r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        printf("\nInvalid coordinates!\n");
        return;
    }

    int status = grid[r][c];

    printf("\n--- Sector (%d,%d) Status ---\n", r, c);
    printf("Power        : %s\n", (status & (1<<POWER)) ? "ON" : "OFF");
    printf("Overload     : %s\n", (status & (1<<OVERLOAD)) ? "YES" : "NO");
    printf("Maintenance  : %s\n", (status & (1<<MAINT)) ? "REQUIRED" : "NO");
}

void runDiagnostics(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;

    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            if(grid[i][j] & (1<<OVERLOAD)) overloadCount++;
            if(grid[i][j] & (1<<MAINT)) maintenanceCount++;
        }
    }

    printf("\n===== GRID DIAGNOSTIC REPORT =====\n");
    printf("Total Overloaded Sectors      : %d\n", overloadCount);
    printf("Total Maintenance Required    : %d\n", maintenanceCount);
    printf("==================================\n");
}
