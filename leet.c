#include <stdio.h>
#include <stdlib.h>

int *getLeastNumbers(int *arr, int arrSize, int k, int *returnSize);

int main() {
    int arr1[6] = {7, 2, 9, 5, 10, 4};
    int *arr = arr1;
//    leet.c:9:16: warning: incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
//    int *arr ={7, 2, 9, 5, 10, 4};
//    ^
//    leet.c:9:19: warning: excess elements in scalar initializer
//    int *arr ={7, 2, 9, 5, 10, 4};

//    int *arr ={7, 2, 9, 5, 10, 4};
    int arrSize = 6;
    int k = 4;
    int *returnSize = (int *) malloc(sizeof(int));
    int *result = getLeastNumbers(arr, arrSize, k, returnSize);
    printf("returnSize2 = %d\n", *returnSize);
    for (int i = 0; i < *returnSize; i++) {
        printf("result[%d] = %d#####%d\n", i, result[i], *returnSize);
    }
    return 0;
}

int *getLeastNumbers(int *arr, int arrSize, int k, int *returnSize) {
    int *result = (int *) malloc(sizeof(int) * k);
    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[i]) {
                int tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < arrSize && i < k; i++) {
//        printf("arr[%d] = %d\n", i, arr[i]);
        result[counter++] = arr[i];
    }
//    returnSize = &counter;
    *returnSize = counter;  // 上面那句，无法将值保存到returnSize，并在函数外可访问
//    printf("returnSize = %d\n", *returnSize);
    return result;

}