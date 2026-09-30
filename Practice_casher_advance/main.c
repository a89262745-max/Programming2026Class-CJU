#include <stdio.h>

int main() {
    int sku_price = 1500;
    int nPcs = 3;

    printf("This price is %d won:\n", sku_price);
    printf("How many are you going to buy? Enter the quantity.:\n");
    scanf("%d", &nPcs);

    int total = sku_price * nPcs;
    int discount_rate = 10;
    int discount = (total * discount_rate) / 100;
    unsigned int final_price = total - discount;

    unsigned int uPayment = 0;

    char strMet[20]= "cash";
    printf("So, you are going to pay %u won:\n", final_price);
    printf("How would you like to make the payment?(cash or card):\n");
    scanf("%s", strMet);

    if (strcmp(strMet, "cash") == 0) {
        printf("You have selected cash payment.\n");
        printf("Enter the amount you are going to pay:\n");
        scanf("%u", &uPayment);


        if (uPayment < final_price) {
            printf("You don't have enough money to pay for this purchase.\n");
            printf("Please select a different payment method.\n");
        
            return 1;
        }

        int change = uPayment - final_price;
        printf("Your change is %d won:\n", change);

        int won1000 = change / 1000;
        int won500 = (change % 1000) / 500;
        int won100 = (change % 500) / 100;
        int won50 = (change % 100) / 50;

        printf("Total: %d won\n", total);
        printf("Discount: %d won\n", discount);
        printf("Payment: %d won\n", uPayment);
        printf("Change: %d won\n", change);

        printf("Change breakdown:\n");
        printf("1000 won: %d\n", won1000);
        printf("500 won: %d\n", won500);
        printf("100 won: %d\n", won100);
        printf("50 won: %d\n", won50);
    
        return 0;
    } else if (strcmp(strMet, "card") == 0) {
        printf("You have selected card payment.\n");
        return 0;
    } else {
        printf("Invalid payment method. Please select either 'cash' or 'card'.\n");
        return 1;
    }
    
   
}