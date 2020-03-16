#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main() {
    int nums[] = {};

    for(int i = 0; i < 5; i++){
        nums[i] = i;
    }

    printf("nums[i] = %d\n", nums[0]);

    return 0;
}
