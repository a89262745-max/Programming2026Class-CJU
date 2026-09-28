#include <stdio.h>

int main(void) {

    //initalizing variables

    int nAge =  0;
    float fHeight = 0.0f;
    char cGender = 'DNF';
    char strName[20]= "Temporary";
    char strMajor[20]= "Temporary";

    //getting variables from user input
    // linux scanf_s() function is not available, so using scanf() instead

    printf("Enter your age, height, gender, name, and major:\n");
    scanf("%d %f %c %19s %19s", &nAge, &fHeight, &cGender, strName, strMajor);
    
    //printing the variables from user input
    printf("my age is %d, height is %.1fcm, gender is %c, name is %s, major is %s\n", nAge, fHeight, cGender, strName, strMajor);

    return 0;
}