#include <stdio.h>

int main() {
    int sku_price = 1500;
    int pcs = 3;

    int total = sku_price * pcs;
    int discount_rate = 10;
    int discount = (total * discount_rate) / 100;

    int payment = 10000;

    int change = payment - (total - discount);

    int won1000 = change / 1000;
    int won500 = (change % 1000) / 500;
    int won100 = (change % 500) / 100;
    int won50 = (change % 100) / 50;

    printf("Total: %d won\n", total);
    printf("Discount: %d won\n", discount);
    printf("Payment: %d won\n", payment);
    printf("Change: %d won\n", change);

    printf("Change breakdown:\n");
    printf("1000 won: %d\n", won1000);
    printf("500 won: %d\n", won500);
    printf("100 won: %d\n", won100);
    printf("50 won: %d\n", won50);

    return 0;
}