#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5
#define MAX_ORDERS 10

// Structure to store food item details
struct FoodItem {
    int id;
    char name[30];
    float price;
};

// Structure to store orders
struct Order {
    int foodId;
    int quantity;
};

// Function declarations 
void displayMenu(struct FoodItem menu[], int size);
void placeOrder(struct FoodItem menu[], int menuSize, struct Order orders[], int *orderCount);
void viewBill(struct FoodItem menu[], int menuSize, struct Order orders[], int orderCount);

// Main function
int main() {
    // Food Menu
    struct FoodItem menu[MAX_ITEMS] = {
        {1, "momo", 100.00},
        {2, "Chaumine", 90.00},
        {3, "Pasta", 80.00},
        {4, "Fries", 70.00},
        {5, "Coke", 50.00}
    };

    //2 Order array
    struct Order orders[MAX_ORDERS];
    int orderCount = 0;

    int choice;
    do {
        printf("\n1. View Menu\n2. Place Order\n3. View Bill\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, MAX_ITEMS);
                break;
            case 2:
                placeOrder(menu, MAX_ITEMS, orders, &orderCount);
                break;
            case 3:
                viewBill(menu, MAX_ITEMS, orders, orderCount);
                break;
            case 4:
                printf("Thank you for using Online Food Order System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to display the menu
void displayMenu(struct FoodItem menu[], int size) {
    printf("\nMenu:\n");
    printf("===================================\n");
    printf("ID\tFood Item\t\tPrice\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%-20s\t%.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("===================================\n");
}

//3 Function to place an order
void placeOrder(struct FoodItem menu[], int menuSize, struct Order orders[], int *orderCount) {
    int foodId, quantity;

    if (*orderCount >= MAX_ORDERS) {
        printf("\nYou have reached the maximum number of orders!\n");
        return;
    }

    displayMenu(menu, menuSize);

    printf("\nEnter the ID of the food item you want to order: ");
    scanf("%d", &foodId);

    int valid = 0;
    for (int i = 0; i < menuSize; i++) {
        if (menu[i].id == foodId) {
            valid = 1;
            break;
        }
    }

    if (!valid) {
        printf("\nInvalid Food ID! Please try again.\n");
        return;
    }

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("\nQuantity must be greater than 0! Please try again.\n");
        return;
    }

    orders[*orderCount].foodId = foodId;
    orders[*orderCount].quantity = quantity;
    (*orderCount)++;

    printf("\nOrder placed successfully!\n");
}

//4 Function to view the bill and apply discounts
void viewBill(struct FoodItem menu[], int menuSize, struct Order orders[], int orderCount) {
    if (orderCount == 0) {
        printf("\nNo orders placed yet!\n");
        return;
    }

    printf("\nYour Order Summary:\n");
    printf("===================================\n");
    printf("Item\t\tQuantity\tPrice\n");
    printf("-----------------------------------\n");

    float total = 0.0;
    for (int i = 0; i < orderCount; i++) {
        for (int j = 0; j < menuSize; j++) {
            if (menu[j].id == orders[i].foodId) {
                float price = menu[j].price * orders[i].quantity;
                total += price;
                printf("%-15s\t%d\t\t%.2f\n", menu[j].name, orders[i].quantity, price);
                break;
            }
        }
    }

    printf("===================================\n");

    float discount = 0.0;
    if (total > 500) {
        discount = total * 0.10;
        printf("Discount Applied: %.2f\n", discount);
    }

    float finalAmount = total - discount;
    printf("Total Bill (after discount): %.2f\n", finalAmount);


//5 save bill
    char saveOption;
    printf("\nDo you want to save the bill to a file? (y/n): ");
    scanf(" %c", &saveOption);

    if (saveOption == 'y' || saveOption == 'Y') {
        FILE *file = fopen("bill.txt", "w");
        if (file == NULL) {
            printf("Error saving the bill to a file.\n");
        } else {
            fprintf(file, "Your Order Summary:\n");
            fprintf(file, "===================================\n");
            fprintf(file, "Item\t\tQuantity\tPrice\n");
            fprintf(file, "-----------------------------------\n");

            for (int i = 0; i < orderCount; i++) {
                for (int j = 0; j < menuSize; j++) {
                    if (menu[j].id == orders[i].foodId) {
                        float price = menu[j].price * orders[i].quantity;
                        fprintf(file, "%-15s\t%d\t\t%.2f\n", menu[j].name, orders[i].quantity, price);
                        break;
                    }
                }
            }

            fprintf(file, "===================================\n");
            fprintf(file, "Total Bill: %.2f\n", total);
            fprintf(file, "Discount Applied: %.2f\n", discount);
            fprintf(file, "Total (after discount): %.2f\n", finalAmount);
            fclose(file);
            printf("Bill saved successfully to 'bill.txt'\n");
        }
    }
}