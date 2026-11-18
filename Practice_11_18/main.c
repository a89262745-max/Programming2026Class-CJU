#include<stdio.h>
 #define ARRAY_SIZE 10

 void swap(int* pa, int* pb) 
 {
     int nTemp;
     nTemp = *pa;
     
     *pa = *pb;
    // 값을 바꿔주는놈
     *pb = nTemp;
     
     return;
 }

 void print_array(const int *pArr, int nSize) 
 {
     for (int i = 0; i < nSize; i++)
     {
         
         printf("%d ", *(pArr + i)); // printf("%d ", pArr[i]); 포인터 연산, 호환문법
     }
     printf("\n");

     return;
 }

 void bubble_sort(int* pArr, int nSize) 
 {
     for (int i = 0; i < nSize - 1; i++) //int i = 0; i < nSize - 1; i++ , nSize - 1 iteration, nSize - 1 times
     {
         for (int j = 0; j < nSize - 1 - i; j++)
         {
             if (pArr [j] > pArr [j + 1]) // 만약 pArr[j]가  pArr[j + 1]보다 크다면,
             {
                 swap(&pArr[j], &pArr[j + 1]); //
             }
         }
     }

     return;
 }

  void inverse_bubble_sort(int* pArr, int nSize) 
 {
     for (int i = 0; i < nSize - 1; i++) //int i = 0; i < nSize - 1; i++ , nSize - 1 iteration, nSize - 1 times
     {
         for (int j = 0; j < nSize - 1 - i; j++)
         {
             if (pArr [j] < pArr [j + 1]) // 만약 pArr[j]가  pArr[j + 1]보다 작다면,
             {
                 swap(&pArr[j], &pArr[j + 1]); //
             }
         }
     }

     return;
 }


 int main() {
     int nArrData[ARRAY_SIZE] = { 75, 2, 8, 61, 50, 92, 100, 70, 80, 95 };
     
     printf("Before Bubble Sort\n");
     print_array(nArrData, sizeof(nArrData) / sizeof(nArrData[0])); // 배열의 크기 계산, sizeof(nArrData) / sizeof(nArrData[0]) = 10
     printf("\n");
     
     printf("Sorting...\n");
     bubble_sort(nArrData, sizeof(nArrData) / sizeof(nArrData[0])); 
     printf("\n");
     printf("After Bubble Sort\n");
     print_array(nArrData, sizeof(nArrData) / sizeof(nArrData[0]));

     printf("Ayy...Here We go again \n");
     printf("Inverse Sorting...\n");
     inverse_bubble_sort(nArrData, sizeof(nArrData) / sizeof(nArrData[0]));
     printf("\n");
     printf("After Inverse Bubble Sort\n");
     print_array(nArrData, sizeof(nArrData) / sizeof(nArrData[0]));
     return 0;
 }