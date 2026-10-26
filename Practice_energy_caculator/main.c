#include <stdio.h>
#include <float.h>
#include <limits.h>

/* Menu choices */
#define MENU_EXIT         0U
#define MENU_KE           1U
#define MENU_PE           2U
#define MENU_FREE_FALL    3U
#define MENU_INVALID     (UINT_MAX - 1U)
#define MENU_INPUT_END   UINT_MAX

/* Physical constants and unit conversions */
#define GRAVITY           9.81
#define HALF              0.5
#define TABLE_DIVISIONS   5U
#define FIRST_POINT       0U
#define UNIT_THRESHOLD    1000.0
#define UNIT_SCALE        1000.0
#define ENERGY_REL_TOL    1.0e-10

/* Input types and validation */
#define INPUT_MASS        1U
#define INPUT_VELOCITY    2U
#define INPUT_HEIGHT      3U
#define MIN_QUANTITY      0.0
#define INVALID_QUANTITY (-1.0)
#define INPUT_SUCCESS     1
#define INPUT_INVALID     0

/* Calculation and program status */
#define CALCULATION_SUCCESS 1
#define CALCULATION_FAILURE 0
#define PROGRAM_SUCCESS     0
#define PROGRAM_FAILURE     1

/* Function declarations: implementations are placed after main. */
void print_menu(void);
unsigned int read_menu(void);
int consume_input_line(void);
int is_valid_quantity(double value);
int is_valid_energy(double energy);
double read_quantity(unsigned int type);
double KE_caculator(double mass, double velocity);
double PE_caculator(double mass, double height);
void print_height(double height);
void print_energy(double energy);
int FF_Table_plot(double mass, double h_zero);
int run_calculation(unsigned int choice);

int main(void)
{
    unsigned int choice;

    while (1) {
        choice = read_menu();

        switch (choice) {
            case MENU_EXIT:
                printf("Exiting calculator.\n");
                return PROGRAM_SUCCESS;

            case MENU_KE:
            case MENU_PE:
            case MENU_FREE_FALL:
                if (run_calculation(choice) == CALCULATION_FAILURE) {
                    printf("\nInput ended. Program stopped.\n");
                    return PROGRAM_FAILURE;
                }
                break;

            case MENU_INPUT_END:
                printf("\nInput ended. Program stopped.\n");
                return PROGRAM_FAILURE;

            default:
                printf("Invalid menu input. Choose 0, 1, 2, or 3.\n");
                break;
        }
    }
}

/* No input parameters, no return value. */
void print_menu(void)
{
    printf("\n===== Mechanical Energy Calculator =====\n");
    printf("%u. Kinetic energy\n", MENU_KE);
    printf("%u. Potential energy\n", MENU_PE);
    printf("%u. Free-fall table\n", MENU_FREE_FALL);
    printf("%u. Exit\n", MENU_EXIT);
    printf("Select an option: ");
    fflush(stdout);
}

/* Output-only function (return value, no parameters).
   Read exactly one menu digit to reject signs, extra text, and overflow. */
unsigned int read_menu(void)
{
    int ch;
    int has_digit = INPUT_INVALID;
    int invalid = INPUT_INVALID;
    unsigned int choice = MENU_INVALID;

    print_menu();

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch >= '0' && ch <= '9') {
            if (has_digit == INPUT_SUCCESS || invalid == INPUT_SUCCESS) {
                invalid = INPUT_SUCCESS;
            } else {
                choice = (unsigned int)(ch - '0');
                has_digit = INPUT_SUCCESS;
            }
        } else if (ch != ' ' && ch != '\t' && ch != '\r') {
            invalid = INPUT_SUCCESS;
        }
    }

    if (ch == EOF && has_digit == INPUT_INVALID && invalid == INPUT_INVALID) {
        return MENU_INPUT_END;
    }

    if (has_digit == INPUT_INVALID || invalid == INPUT_SUCCESS ||
        choice > MENU_FREE_FALL) {
        return MENU_INVALID;
    }

    return choice;
}

/* Reject any non-whitespace characters left after a numeric input. */
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

/* Accept positive finite real-world inputs only. */
int is_valid_quantity(double value)
{
    return (value > MIN_QUANTITY && value <= DBL_MAX);
}

/* Zero energy is allowed at the endpoints of free fall. */
int is_valid_energy(double energy)
{
    return (energy >= MIN_QUANTITY && energy <= DBL_MAX);
}

/* Has both an input parameter and a returned result. */
double read_quantity(unsigned int type)
{
    double value;
    int input_status;
    int line_status;

    while (1) {
        switch (type) {
            case INPUT_MASS:
                printf("Enter mass (kg, > 0): ");
                break;

            case INPUT_VELOCITY:
                printf("Enter speed (m/s, > 0): ");
                break;

            case INPUT_HEIGHT:
                printf("Enter height (m, > 0): ");
                break;

            default:
                return INVALID_QUANTITY;
        }

        fflush(stdout);
        input_status = scanf("%lf", &value);

        if (input_status == EOF) {
            return INVALID_QUANTITY;
        }

        line_status = consume_input_line();
        if (input_status != INPUT_SUCCESS || line_status != INPUT_SUCCESS ||
            !is_valid_quantity(value)) {
            printf("Invalid input. Enter one finite number greater than 0.\n");
            continue;
        }

        return value;
    }
}

/* Input parameters + return value: KE = 1/2 * m * v^2. */
double KE_caculator(double mass, double velocity)
{
    return HALF * mass * velocity * velocity;
}

/* Input parameters + return value: PE = m * g * h. */
double PE_caculator(double mass, double height)
{
    return mass * GRAVITY * height;
}

/* Input-only function (parameter, void return): meters + optional km. */
void print_height(double height)
{
    if (height >= UNIT_THRESHOLD) {
        printf("%12.3f m (%9.3f km)", height, height / UNIT_SCALE);
    } else {
        printf("%12.3f m%15s", height, "");
    }
}

/* Input-only function (parameter, void return): joules + optional kJ. */
void print_energy(double energy)
{
    if (energy >= UNIT_THRESHOLD) {
        printf("%12.3f J (%9.3f kJ)", energy, energy / UNIT_SCALE);
    } else {
        printf("%12.3f J%15s", energy, "");
    }
}

/* Six positions: h = 0, h_zero/5, ... , h_zero.
   The free-fall direction is from h_zero down to 0; rows are ascending.
   Return FAILURE if any intermediate calculation is not finite. */
int FF_Table_plot(double mass, double h_zero)
{
    unsigned int point;
    int all_conserved = CALCULATION_SUCCESS;
    double height;
    double force;
    double pe;
    double ke;
    double total;
    double expected_total;
    double absolute_error;
    double allowed_error;
    int row_conserved;

    force = mass * GRAVITY;
    expected_total = PE_caculator(mass, h_zero);
    if (!is_valid_quantity(force) || !is_valid_quantity(expected_total)) {
        return CALCULATION_FAILURE;
    }

    allowed_error = ENERGY_REL_TOL * expected_total;

    printf("\n---------------------- Free-fall Energy Table ----------------------\n");
    printf("Mass: %.3f kg | Initial height: ", mass);
    print_height(h_zero);
    printf("\nReference total energy: ");
    print_energy(expected_total);
    printf("\nFree fall: h_zero -> 0 m (table shown from 0 -> h_zero).\n");
    printf("KE = m*g*(h_zero - h), PE = m*g*h\n\n");
    printf("Step | %-29s | %-29s | %-29s | %-29s | Check\n",
           "Height", "PE", "KE", "Total energy");
    printf("-----+-------------------------------+-------------------------------+"
           "-------------------------------+-------------------------------+------\n");

    for (point = FIRST_POINT; point <= TABLE_DIVISIONS; ++point) {
        height = h_zero * ((double)point / (double)TABLE_DIVISIONS);
        pe = PE_caculator(mass, height);
        ke = force * (h_zero - height);
        total = pe + ke;

        if (!is_valid_energy(pe) || !is_valid_energy(ke) ||
            !is_valid_energy(total)) {
            printf("Calculation overflow/invalid energy in table.\n");
            return CALCULATION_FAILURE;
        }

        absolute_error = total - expected_total;
        if (absolute_error < MIN_QUANTITY) {
            absolute_error = -absolute_error;
        }

        row_conserved = (absolute_error <= allowed_error);
        if (!row_conserved) {
            all_conserved = CALCULATION_FAILURE;
        }

        printf("%4u | ", point);
        print_height(height);
        printf(" | ");
        print_energy(pe);
        printf(" | ");
        print_energy(ke);
        printf(" | ");
        print_energy(total);
        printf(" | %s\n", row_conserved ? "PASS" : "FAIL");
    }

    printf("\nEnergy conservation (relative tolerance %.1e): %s\n",
           ENERGY_REL_TOL, all_conserved ? "PASS" : "FAIL");

    return CALCULATION_SUCCESS;
}

/* Repeat both physical inputs if their calculated result overflows. */
int run_calculation(unsigned int choice)
{
    double mass;
    double second_input;
    double energy;

    while (1) {
        mass = read_quantity(INPUT_MASS);
        if (mass == INVALID_QUANTITY) {
            return CALCULATION_FAILURE;
        }

        switch (choice) {
            case MENU_KE:
                second_input = read_quantity(INPUT_VELOCITY);
                if (second_input == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                energy = KE_caculator(mass, second_input);
                if (is_valid_quantity(energy)) {
                    printf("\nKinetic energy (KE): ");
                    print_energy(energy);
                    printf("\n");
                    return CALCULATION_SUCCESS;
                }
                break;

            case MENU_PE:
                second_input = read_quantity(INPUT_HEIGHT);
                if (second_input == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                energy = PE_caculator(mass, second_input);
                if (is_valid_quantity(energy)) {
                    printf("\nPotential energy (PE): ");
                    print_energy(energy);
                    printf("\nHeight: ");
                    print_height(second_input);
                    printf("\n");
                    return CALCULATION_SUCCESS;
                }
                break;

            case MENU_FREE_FALL:
                second_input = read_quantity(INPUT_HEIGHT);
                if (second_input == INVALID_QUANTITY) {
                    return CALCULATION_FAILURE;
                }
                if (FF_Table_plot(mass, second_input) == CALCULATION_SUCCESS) {
                    return CALCULATION_SUCCESS;
                }
                break;

            default:
                return CALCULATION_FAILURE;
        }

        printf("Calculation overflow or underflow. Please enter both values again.\n");
    }
}
