#include<stdio.h>

int main() {
    //The range for a standard int is -2,147,483,648 to 2,147,483,647.
    //Since time cannot be negative and durations may exceed 2.1 billion seconds,
    //unsigned long long is used instead..
    
    unsigned long long practice_time;
    printf("Enter your practice time in seconds: ");
    scanf("%llu", &practice_time);
    
    int hours = practice_time / 3600;
    int minutes = (practice_time % 3600) / 60;
    int seconds = practice_time % 60;
    
    printf("You have practiced for %d hours, %d minutes, and %d seconds.\n", hours, minutes, seconds);
    printf("Digital Clock Format: %02d:%02d:%02d\n", hours, minutes, seconds);
    return 0;
}