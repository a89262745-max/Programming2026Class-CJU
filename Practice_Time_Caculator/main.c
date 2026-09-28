#include<stdio.h>

int main() {
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