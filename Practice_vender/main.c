#include <stdio.h>
#include <string.h>

int main(void) {
    int menu, deposit, sku_price;
    int change;
    int won1000, won500, won100;
    int salesCount[3] = {0, 0, 0};
    int totalSales = 0;
    int adminMenu;
    char password[20];

    while (1) {
        printf("\n==== beverage vender ====\n");
        printf("1. cola   = 1200 won\n");
        printf("2. sprite = 1100 won\n");
        printf("3. coffee =  800 won\n");
        printf("4. quit\n");
        printf("0. admin\n");
        printf("Select a menu number: ");

        if (scanf("%d", &menu) != 1) {
            return 1;
        }

        // Select a beverage or open the administrator menu
        switch (menu) {
            case 1:
                sku_price = 1200;
                break;

            case 2:
                sku_price = 1100;
                break;

            case 3:
                sku_price = 800;
                break;

            case 4:
                printf("Goodbye!\n");
                return 0;

            case 0:
                printf("Password(admin): ");

                if (scanf("%19s", password) != 1) {
                    return 1;
                }

                // Check the administrator password
                if (strcmp(password, "admin") != 0) {
                    printf("Incorrect password.\n");
                    continue;
                }

                printf("\n==== Administrator Menu ====\n");
                printf("1. Exit sales system\n");
                printf("2. Today's sales report\n");
                printf("Select a menu number: ");

                if (scanf("%d", &adminMenu) != 1) {
                    return 1;
                }

                switch (adminMenu) {
                    case 1:
                        printf("Goodbye!\n");
                        return 0;

                    case 2:
                        // Display total sales and beverage quantities
                        printf("\n===[Schrodinger's Point Of Sale System v0.0.1]===\n\n");
                        printf("Total sales: %d won\n\n", totalSales);

                        printf("==== beverage vender sales quantity ====\n");
                        printf("1. cola   : %d\n", salesCount[0]);
                        printf("2. sprite : %d\n", salesCount[1]);
                        printf("3. coffee : %d\n", salesCount[2]);

                        // Return to the main menu when 0 is entered
                        do {
                            printf("\n==== Press 0 to main menu ====\n");

                            if (scanf("%d", &adminMenu) != 1) {
                                return 1;
                            }

                        } while (adminMenu != 0);

                        break;

                    default:
                        printf("Invalid administrator menu.\n");
                        break;
                }

                continue;

            default:
                printf("Invalid menu.\n");
                continue;
        }

        // Insert payment
        printf("\nPrice: %d won, Paid: 0 won\n", sku_price);
        printf("Please insert %d won.\n", sku_price);
        printf("Insert amount: ");

        if (scanf("%d", &deposit) != 1) {
            return 1;
        }

        // Check payment amount
        int validAmount = (deposit >= sku_price && deposit % 100 == 0);
        int rejectedBill = (deposit == 5000 || deposit == 10000 || deposit == 50000);

        if (!validAmount || rejectedBill) {
            printf("Rejected: %d won.\n", deposit);
            continue;
        }

        // Calculate change
        change = deposit - sku_price;

        won1000 = change / 1000;
        won500 = (change % 1000) / 500;
        won100 = (change % 500) / 100;

        // Update sales records
        totalSales += sku_price;
        salesCount[menu - 1]++;

        // Dispense beverage
        printf("\nYour beverage (menu %d) is ready!\n", menu);

        printf("Payment: %d won\n", deposit);
        printf("Change: %d won\n", change);

        // Change breakdown
        printf("Change breakdown:\n");
        printf("1000 won: %d\n", won1000);
        printf(" 500 won: %d\n", won500);
        printf(" 100 won: %d\n", won100);
    }

    return 0;
}