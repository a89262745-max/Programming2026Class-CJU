
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Parking rules */
#define MIN_CARS 1
#define MAX_CARS 10
#define MIN_PARKING_MINUTES 0
#define FREE_MINUTES 30
#define UNIT_MINUTES 10
#define UNIT_FEE 500
#define MAX_DAILY_FEE 20000

/* Vehicle types */
#define CAR_COMPACT 1
#define CAR_REGULAR 2
#define CAR_ELECTRIC 3

/* Discount rates (percent) */
#define DISCOUNT_COMPACT 50
#define DISCOUNT_REGULAR 0
#define DISCOUNT_ELECTRIC 30
#define PERCENT_BASE 100

/* Read an integer and reject trailing non-whitespace characters. */
int read_int(const char *prompt)
{
    int value, result, ch, valid;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == EOF) {
            fprintf(stderr, "Input ended unexpectedly.\n");
            exit(EXIT_FAILURE);
        }

        valid = (result == 1);

        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (!isspace((unsigned char)ch)) {
                valid = 0;
            }
        }

        if (valid) {
            return value;
        }

        printf(" -> Please enter a valid integer.\n");
    }
}

int main(void)
{
    int num_cars, car_type, minutes;
    int total_fee = 0;
    int max_fee = -1;
    int max_car_number = 0;

    /* 1. Validate the number of vehicles. */
    do {
        num_cars = read_int("Number of vehicles (1-10): ");

        if (num_cars < MIN_CARS || num_cars > MAX_CARS) {
            printf(" -> Enter a number from %d to %d.\n",
                   MIN_CARS, MAX_CARS);
        }

    } while (num_cars < MIN_CARS || num_cars > MAX_CARS);

    /* 2. Process each vehicle. */
    for (int i = 1; i <= num_cars; i++) {

        int fee = 0;
        int discount = DISCOUNT_REGULAR;

        printf("\n[Vehicle %d]\n", i);

        car_type = read_int(
            "Type (1:Compact 2:Regular 3:Electric): "
        );

        do {
            minutes = read_int("Parking duration (minutes): ");

            if (minutes < MIN_PARKING_MINUTES) {
                printf(" -> Enter a duration of %d or more.\n",
                       MIN_PARKING_MINUTES);
            }

        } while (minutes < MIN_PARKING_MINUTES);

        /* 3. Apply the free period, rounding, and fee cap. */
        if (minutes > FREE_MINUTES) {

            int extra_minutes = minutes - FREE_MINUTES;
            int charge_units = extra_minutes / UNIT_MINUTES;

            if (extra_minutes % UNIT_MINUTES != 0) {
                charge_units++;
            }

            if (charge_units >= MAX_DAILY_FEE / UNIT_FEE) {
                fee = MAX_DAILY_FEE;
            }
            else {
                fee = charge_units * UNIT_FEE;
            }
        }

        /* 4. Apply the vehicle discount after the fee cap. */
        switch (car_type) {

            case CAR_COMPACT:
                discount = DISCOUNT_COMPACT;
                break;

            case CAR_REGULAR:
                discount = DISCOUNT_REGULAR;
                break;

            case CAR_ELECTRIC:
                discount = DISCOUNT_ELECTRIC;
                break;

            default:
                printf(" -> Unknown type: regular rate applied.\n");
                break;
        }

        fee = fee * (PERCENT_BASE - discount) / PERCENT_BASE;

        /* 5. Display and accumulate the fees. */
        printf("Fee: %d KRW (discount %d%%)\n", fee, discount);

        total_fee += fee;

        if (fee > max_fee) {
            max_fee = fee;
            max_car_number = i;
        }
    }

    printf("\nTotal fee: %d KRW\n", total_fee);

    printf("Highest fee: Vehicle %d (%d KRW)\n",
           max_car_number, max_fee);

    return 0;
}