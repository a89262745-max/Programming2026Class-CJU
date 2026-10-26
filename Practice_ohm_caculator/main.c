#include <stdio.h>
#include <float.h>

/* Menu constants */
#define MENU_EXIT        0U
#define MENU_VOLTAGE     1U
#define MENU_CURRENT     2U
#define MENU_RESISTANCE  3U

/* Input rules */
#define ALLOW_ZERO          0U
#define REQUIRE_POSITIVE   1U
#define MIN_QUANTITY       0.0f
#define INVALID_QUANTITY (-1.0f)

/* Status constants */
#define INPUT_SUCCESS       1
#define INPUT_INVALID       0
#define CALCULATION_SUCCESS 1
#define CALCULATION_FAILURE 0
#define PROGRAM_SUCCESS     0
#define PROGRAM_FAILURE     1

/* Function declarations */
void print_menu(void);
int consume_input_line(void);
int is_valid_quantity(float value);
float read_quantity(unsigned int type, unsigned int require_positive);
float calculate_voltage(float current, float resistance);
float calculate_current(float voltage, float resistance);
float calculate_resistance(float voltage, float current);
float calculate_power(float voltage, float current);
void print_results(float voltage, float current, float resistance, float power);
int run_calculation(unsigned int choice);

int main(void)
{
    unsigned int choice;
    int input_status;
    int line_status;

    while (1) {
        print_menu();

        input_status = scanf("%u", &choice);
        if (input_status == EOF) {
            printf("\nInput ended. Program stopped.\n");
            return PROGRAM_FAILURE;
        }

        line_status = consume_input_line();

        if (input_status != INPUT_SUCCESS || line_status != INPUT_SUCCESS) {
            printf("Invalid menu input. Please try again.\n");
            continue;
        }

        switch (choice) {
            case MENU_EXIT:
                printf("Exiting calculator.\n");
                return PROGRAM_SUCCESS;

            case MENU_VOLTAGE:
            case MENU_CURRENT:
            case MENU_RESISTANCE:
                if (run_calculation(choice) == CALCULATION_FAILURE) {
                    printf("\nInput ended. Program stopped.\n");
                    return PROGRAM_FAILURE;
                }
                break;

            default:
                printf("Invalid option. Choose 0, 1, 2, or 3.\n");
                break;
        }
    }
}


/* No parameters, no return value */
void print_menu(void)
{
    printf("\n===== Ohm's Law Calculator =====\n");
    printf("%u. Voltage\n", MENU_VOLTAGE);
    printf("%u. Current\n", MENU_CURRENT);
    printf("%u. Resistance\n", MENU_RESISTANCE);
    printf("%u. Exit\n", MENU_EXIT);
    printf("Select an option: ");
}

/* Consume the rest of an input line and report unwanted characters */
int consume_input_line(void)
{
    int ch;
    int valid = INPUT_SUCCESS;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\r') {
            valid = INPUT_INVALID;
        }
    }

    return valid;
}

/* Check that a quantity is nonnegative and within float range */
int is_valid_quantity(float value)
{
    return (value >= MIN_QUANTITY && value <= FLT_MAX);
}

/* No pointer or array parameters; repeat only the incorrect quantity */
float read_quantity(unsigned int type, unsigned int require_positive)
{
    float value;
    int input_status;
    int line_status;

    while (1) {
        switch (type) {
            case MENU_VOLTAGE:
                printf("Enter voltage (V): ");
                break;

            case MENU_CURRENT:
                if (require_positive == REQUIRE_POSITIVE) {
                    printf("Enter current (A, > 0): ");
                } else {
                    printf("Enter current (A): ");
                }
                break;

            case MENU_RESISTANCE:
                if (require_positive == REQUIRE_POSITIVE) {
                    printf("Enter resistance (ohm, > 0): ");
                } else {
                    printf("Enter resistance (ohm): ");
                }
                break;

            default:
                return INVALID_QUANTITY;
        }

        input_status = scanf("%f", &value);
        if (input_status == EOF) {
            return INVALID_QUANTITY;
        }

        line_status = consume_input_line();

        if (input_status != INPUT_SUCCESS || line_status != INPUT_SUCCESS ||
            !is_valid_quantity(value) ||
            (require_positive == REQUIRE_POSITIVE && value == MIN_QUANTITY)) {
            printf("Invalid input, division by zero, or numeric overflow.\n");
            continue;
        }

        return value;
    }
}

/* Parameters and return values */
float calculate_voltage(float current, float resistance)
{
    return current * resistance;
}

float calculate_current(float voltage, float resistance)
{
    return voltage / resistance;
}

float calculate_resistance(float voltage, float current)
{
    return voltage / current;
}

float calculate_power(float voltage, float current)
{
    return voltage * current;
}

/* Parameters, no return value */
void print_results(float voltage, float current, float resistance, float power)
{
    printf("\n----- Calculation Results -----\n");
    printf("Voltage (V):    %.3f V\n", voltage);
    printf("Current (I):    %.3f A\n", current);
    printf("Resistance (R): %.3f ohm\n", resistance);
    printf("Power (P):      %.3f W\n", power);
}

/* Run a calculation and retry if the result overflows */
int run_calculation(unsigned int choice)
{
    float voltage;
    float current;
    float resistance;
    float power;

    while (1) {
        voltage = MIN_QUANTITY;
        current = MIN_QUANTITY;
        resistance = MIN_QUANTITY;

        switch (choice) {
            case MENU_VOLTAGE:
                current = read_quantity(MENU_CURRENT, ALLOW_ZERO);
                if (current == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                resistance = read_quantity(MENU_RESISTANCE, ALLOW_ZERO);
                if (resistance == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                voltage = calculate_voltage(current, resistance);
                break;

            case MENU_CURRENT:
                voltage = read_quantity(MENU_VOLTAGE, ALLOW_ZERO);
                if (voltage == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                resistance = read_quantity(MENU_RESISTANCE, REQUIRE_POSITIVE);
                if (resistance == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                current = calculate_current(voltage, resistance);
                break;

            case MENU_RESISTANCE:
                voltage = read_quantity(MENU_VOLTAGE, ALLOW_ZERO);
                if (voltage == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                current = read_quantity(MENU_CURRENT, REQUIRE_POSITIVE);
                if (current == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                resistance = calculate_resistance(voltage, current);
                break;

            default:
                return CALCULATION_FAILURE;
        }

        power = calculate_power(voltage, current);

        if (!is_valid_quantity(voltage) || !is_valid_quantity(current) ||
            !is_valid_quantity(resistance) || !is_valid_quantity(power)) {
            printf("Invalid input, division by zero, or numeric overflow.\n");
            printf("Please enter the two quantities again.\n");
            continue;
        }

        print_results(voltage, current, resistance, power);
        return CALCULATION_SUCCESS;
    }
}


