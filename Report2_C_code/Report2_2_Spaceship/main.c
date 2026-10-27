#include <stdio.h>
#include <limits.h>

/* Report #2 - Problem 2: Escape from a Black Hole */
#define ESCAPE_ENERGY       1LL
#define EVEN_DIVISOR       2LL
#define ODD_MULTIPLIER     3LL
#define ODD_INCREMENT      1LL
#define FIRST_STEP         0

/* Function declaration: definition is below main(). */
int is_clean_line(void);

int main(void)
{
    long long energy;
    long long max_altitude;
    unsigned long long steps = FIRST_STEP;

    printf("Enter the initial engine energy: ");

    /* Reject nonnumeric input, extra characters and nonpositive values. */
    if (scanf("%lld", &energy) != 1 || !is_clean_line()) {
        printf("Invalid input: enter one positive integer.\n");
        return 1;
    }
    if (energy < ESCAPE_ENERGY) {
        printf("Initial energy must be a positive integer.\n");
        return 1;
    }

    max_altitude = energy;
    printf("Sequence: %lld", energy);

    /* Collatz rule: even -> n/2, odd -> 3*n+1. */
    while (energy != ESCAPE_ENERGY) {
        if (energy % EVEN_DIVISOR == 0) {
            energy /= EVEN_DIVISOR;
        }
        else {
            /* Check before multiplication to avoid integer overflow. */
            if (energy > (LLONG_MAX - ODD_INCREMENT) / ODD_MULTIPLIER) {
                printf("\nEnergy is too large to calculate safely.\n");
                return 1;
            }
            energy = energy * ODD_MULTIPLIER + ODD_INCREMENT;
        }

        steps++;
        if (energy > max_altitude) {
            max_altitude = energy;
        }

        printf(" -> %lld", energy);
    }

    printf("\nEscape successful!\n");
    printf("Total steps: %llu\n", steps);
    printf("Maximum altitude reached: %lld\n", max_altitude);

    return 0;
}

/* Verify that the rest of the line contains only whitespace. */
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
