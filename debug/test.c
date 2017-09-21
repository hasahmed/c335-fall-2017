#include <stdio.h>

int foo(int param){
    int i = 0;
    for(i; i < 3; i++){
        param = param << 1;
    }
    return param;
}

int main(){
    int i = 1;
    printf("%d\n", foo(i));
}
