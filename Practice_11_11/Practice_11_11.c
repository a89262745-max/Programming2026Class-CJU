#include<stdio.h>

#define DATA_ARRAY_SIZE 5

int main() {
    
    int arrData[DATA_ARRAY_SIZE] = { 75, 82, 83, 60, 50 };
    //int *ptData = arrData; 
    int *ptData = arrData;
    //
    for (int i = 0; i < DATA_ARRAY_SIZE; i++) {
        printf("arrData[%d] = %d\n", i, arrData[i]);
        printf("arrData[%d] = %d\n", i, *(arrData + i));
        printf("ptData[%d] = %d\n", i, ptData[i]);
        printf("ptData[%d] = %d\n", i, *(ptData + i));
    }
    return 0;
}