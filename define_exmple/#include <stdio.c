#include <stdio.h>
#define PI 3.14159
#define LIMIT 100.0
#define MSG "passed!"
#define ERR_PRN "Error: value exceeds limit.\n"

int main() {
    double radius, area;

    printf("Enter the radius of the circle(below 100): ");
    scanf("%lf", &radius);

    area = PI * radius * radius;

    if (radius > LIMIT) {
        printf(ERR_PRN);
    } else {
        printf("Area of the circle: %.2lf\n", area, MSG);
    }
}