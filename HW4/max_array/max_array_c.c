#include "max_array.h"
unsigned int max_array_c(unsigned int *arr, int size){
    int max_num = arr[0];
    int i;
    for(i = 0; i < size; i++){
        if(arr[i] > max_num){
            max_num = arr[i];
        }
    }
    return max_num;
}
