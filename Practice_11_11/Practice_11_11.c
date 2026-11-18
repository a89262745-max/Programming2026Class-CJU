#include<stdio.h>

#define DATA_ARRAY_SIZE 5

int main() {
    
    
    int arrData[DATA_ARRAY_SIZE] = { 75, 82, 83, 60, 50 };
    int nSizeData = sizeof(arrData) / sizeof(arrData[0]);
    
    //int *ptData = arrData; 
    int *ptData = arrData;
    //

    // 1. 값 비교
    printf("========== VALUE ==========\n");

    for (int i = 0; i < DATA_ARRAY_SIZE; i++) {
        printf("arrData[%d] = %d\n", i, arrData[i]);
        printf("arrData[%d] = %d\n", i, *(arrData + i));
        printf("ptData[%d] = %d\n", i, ptData[i]);
        printf("ptData[%d] = %d\n", i, *(ptData + i));
    }
      // 2. 주소 비교
    printf("\n========== ADDRESS ==========\n");
     for (int i = 0; i < DATA_ARRAY_SIZE; i++) {
        printf("arrData[%d] = %x\n", i, &arrData[i]);
        printf("arrData[%d] = %x\n", i, (arrData + i));
        printf("ptData[%d] = %x\n", i, ptData[i]);
        printf("ptData[%d] = %x\n", i, (ptData + i));
    }
    // 3. 메모리 크기 비교
    printf("\n========== MEMORY SIZE ==========\n");

    printf("sizeof(arrData) = %zu bytes\n", sizeof(arrData));

    printf("sizeof(ptData)  = %zu bytes\n", sizeof(ptData));

    return 0;
}