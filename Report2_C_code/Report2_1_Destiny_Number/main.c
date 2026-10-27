#include <stdio.h>

// Constants for birthdate validation and digit summation
#define MIN_BIRTHDATE       10000101
#define MAX_BIRTHDATE       99991231
#define YEAR_DIVISOR        10000
#define DATE_PART_DIVISOR   100
#define DECIMAL_BASE        10
#define MIN_MONTH           1
#define MAX_MONTH           12
#define MIN_DAY             1
#define FEBRUARY            2
#define APRIL               4
#define JUNE                6
#define SEPTEMBER           9
#define NOVEMBER            11
#define DAYS_IN_FEBRUARY    28
#define DAYS_IN_LEAP_FEB    29
#define DAYS_IN_SHORT_MONTH 30
#define DAYS_IN_LONG_MONTH  31
#define LEAP_DIVISOR        4
#define CENTURY_DIVISOR     100
#define FOUR_CENTURY_DIVISOR 400

// Function declarations: definitions are below main().
int is_clean_line(void);
int is_valid_birthdate(int birthdate);
int sum_digits(int number);
void print_destiny_message(int number);

// main function: read birthdate, calculate destiny number, and print message.
int main(void)
{
    int birthdate;
    int destiny_number;
    int input_result;
    int clean_line;

    // Repeat the entire program until the user exits.
    while (1)
    {
        printf("Enter your 8-digit birthdate (YYYYMMDD): ");

        input_result = scanf("%8d", &birthdate);

        // Exit when the input stream reaches EOF.
        if (input_result == EOF)
        {
            printf("\nProgram terminated.\n");
            break;
        }

        // Clear the remaining input characters.
        clean_line = is_clean_line();

        // Check whether the input is valid.
        if (input_result != 1 || !clean_line)
        {
            printf("Invalid input: enter exactly 8 digits.\n\n");
            continue;
        }

        // Check whether the birthdate is a real date.
        if (!is_valid_birthdate(birthdate))
        {
            printf("Invalid birthdate: check YYYY, MM and DD.\n\n");
            continue;
        }

        printf("\nCalculating...\n");

        destiny_number = birthdate;

        // Calculate the destiny number.
        while (destiny_number >= DECIMAL_BASE)
        {
            destiny_number = sum_digits(destiny_number);

            printf("Sum of digits: %d\n", destiny_number);
        }

        printf("\nYour Destiny Number is %d!\n", destiny_number);

        print_destiny_message(destiny_number);

        // Return to the beginning of the outer while loop.
        printf("\n");
    }

    return 0;
}

// Return 1 only when the rest of the input line is whitespace.
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

// Check the calendar date, including February 29 in leap years.
int is_valid_birthdate(int birthdate)
{
    int year, month, day;
    int max_day = DAYS_IN_LONG_MONTH;
    int is_leap_year;

    if (birthdate < MIN_BIRTHDATE || birthdate > MAX_BIRTHDATE) {
        return 0;
    }

    year = birthdate / YEAR_DIVISOR;
    month = (birthdate / DATE_PART_DIVISOR) % DATE_PART_DIVISOR;
    day = birthdate % DATE_PART_DIVISOR;

    if (month < MIN_MONTH || month > MAX_MONTH || day < MIN_DAY) {
        return 0;
    }

    is_leap_year = (year % LEAP_DIVISOR == 0) &&
                   ((year % CENTURY_DIVISOR != 0) ||
                    (year % FOUR_CENTURY_DIVISOR == 0));

    if (month == FEBRUARY) {
        max_day = is_leap_year ? DAYS_IN_LEAP_FEB : DAYS_IN_FEBRUARY;
    }
    else if (month == APRIL || month == JUNE ||
             month == SEPTEMBER || month == NOVEMBER) {
        max_day = DAYS_IN_SHORT_MONTH;
    }

    return day <= max_day;
}

// Separate each decimal digit using % and /, and add them.
int sum_digits(int number)
{
    int sum = 0;

    while (number > 0) {
        sum += number % DECIMAL_BASE;
        number /= DECIMAL_BASE;
    }

    return sum;
}

// Use a switch statement to print the fortune for numbers 1 to 9.
void print_destiny_message(int number)
{
    printf("\n[Destiny Message]\n");

    switch (number) {
        case 1:
            printf("You are a pioneer who finds a new flight path!\n");
            break;
        case 2:
            printf("Teamwork is your strongest navigation system!\n");
            break;
        case 3:
            printf("Your creativity will reach beyond the sky!\n");
            break;
        case 4:
            printf("Your careful planning makes every mission stable!\n");
            break;
        case 5:
            printf("New adventures are waiting for you!\n");
            break;
        case 6:
            printf("Your kindness keeps your crew together!\n");
            break;
        case 7:
            printf("You are an analytical thinker and a seeker of truth!\n");
            break;
        case 8:
            printf("Your determination will power a successful launch!\n");
            break;
        case 9:
            printf("Your vision reaches far beyond the horizon!\n");
            break;
        default:
            printf("Destiny number calculation failed.\n");
            break;
    }
}
