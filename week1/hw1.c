#include <stdio.h>
#include <stdlib.h>

void findNum(int arr[], int n, int num){
    for(int i = 0; i < n; i++){
        if (arr[i] == num){
            printf("Found number %d in array", num);
            exit(0);
        };
    };
    exit(1);
}

int main(){
    int arr[] = {1,3,4};
    int n = sizeof(arr) / sizeof(arr[0]);
    findNum(arr, n, 1);

    malloc(4*sizeof(n));
    free(4*sizeof(n));
    
    return 0;
}