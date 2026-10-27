#include <stdio.h>

/* Report #2 - Problem 3: Goblin's Vending Machine */
#define MENU_EXIT           0
#define MENU_RED_POTION     1
#define MENU_MAGIC_SCROLL   2
#define MENU_ELIXIR         3

/* Original product prices (G). */
#define PRICE_RED_POTION    1000
#define PRICE_MAGIC_SCROLL  2000
#define PRICE_ELIXIR        3000

/* A 50 percent discount on each third successful purchase. */
#define BLESSING_INTERVAL   3
#define DISCOUNT_PERCENT    50
#define PERCENT_BASE       100
#define MIN_BALANCE         0

/* Function declarations: definitions are below main(). */
int is_clean_line(void);
void print_menu(void);
int get_price(int menu);

int main(void)
{
    int balance;
    int menu;
    int price;
    int purchase_count = 0;
    int next_purchase;
    int is_blessed;
    int input_result;

    /* Ask for a nonnegative starting balance. */
    while (1) {
        printf("Insert coins (Current Balance): ");
        input_result = scanf("%d", &balance);

        if (input_result == EOF) {
            printf("\nInput ended.\n");
            return 1;
        }
        if (input_result != 1 || !is_clean_line()) {
            printf("Invalid input: enter one nonnegative integer.\n");
            if (input_result != 1) {
                is_clean_line();
            }
            continue;
        }
        if (balance < MIN_BALANCE) {
            printf("Balance cannot be negative.\n");
            continue;
        }
        break;
    }

    /* Keep offering products until the customer chooses Exit. */
    while (1) {
        print_menu();
        printf("Select an item: ");
        input_result = scanf("%d", &menu);

        if (input_result == EOF) {
            printf("\nReturning %d G. Goodbye!\n", balance);
            return 0;
        }
        if (input_result != 1 || !is_clean_line()) {
            printf("Invalid input: enter a menu number.\n");
            if (input_result != 1) {
                is_clean_line();
            }
            continue;
        }

        if (menu == MENU_EXIT) {
            printf("Returning %d G. Goodbye!\n", balance);
            break;
        }

        /* Reject invalid menu numbers before calculating the price. */
        price = get_price(menu);
        if (price == 0) {
            printf("Invalid menu. Please choose 0 to 3.\n");
            continue;
        }

        /* Only successful purchases count toward the blessing. */
        next_purchase = purchase_count + 1;
        is_blessed = (next_purchase % BLESSING_INTERVAL == 0);
        if (is_blessed) {
            price = price * (PERCENT_BASE - DISCOUNT_PERCENT) / PERCENT_BASE;
        }

        /* A rejected purchase does not decrease the balance or count. */
        if (balance < price) {
            printf("Not enough balance!\n");
            continue;
        }

        balance -= price;
        purchase_count++;

        if (is_blessed) {
            printf("*** GOBLIN'S BLESSING! %d%% DISCOUNT! ***\n",
                   DISCOUNT_PERCENT);
        }

        switch (menu) {
            case MENU_RED_POTION:
                printf("[Purchased] Red Potion for %d G. Balance: %d G\n",
                       price, balance);
                break;
            case MENU_MAGIC_SCROLL:
                printf("[Purchased] Magic Scroll for %d G. Balance: %d G\n",
                       price, balance);
                break;
            case MENU_ELIXIR:
                printf("[Purchased] Elixir for %d G. Balance: %d G\n",
                       price, balance);
                break;
            default:
                break;
        }
    }

    return 0;
}

/* Return 1 when no unexpected characters remain in the line. */
int is_clean_line(void)
{
    int ch;
    int valid = 1;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\r') {
            valid = 0;
        }
    }

    return valid;
}

/* Display the original prices each time the customer chooses an item. */
void print_menu(void)
{
    printf("\n--- Goblin's Vending Machine ---\n");
    printf("%d. Red Potion (%d G)\n", MENU_RED_POTION, PRICE_RED_POTION);
    printf("%d. Magic Scroll (%d G)\n", MENU_MAGIC_SCROLL, PRICE_MAGIC_SCROLL);
    printf("%d. Elixir (%d G)\n", MENU_ELIXIR, PRICE_ELIXIR);
    printf("%d. Exit\n", MENU_EXIT);
    printf("--------------------------------\n");
}

/* Convert the selected menu number to its original price. */
int get_price(int menu)
{
    switch (menu) {
        case MENU_RED_POTION:
            return PRICE_RED_POTION;
        case MENU_MAGIC_SCROLL:
            return PRICE_MAGIC_SCROLL;
        case MENU_ELIXIR:
            return PRICE_ELIXIR;
        default:
            return 0;
    }
}
