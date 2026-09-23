#include <stdio.h>

int main() {

    int age;
    double height;

    printf("Enter your age and height: ");
    scanf("%d%lf", &age, &height);
    printf("my age is %d, height is %.1lfcm\n", age, height);

    return 0;
}