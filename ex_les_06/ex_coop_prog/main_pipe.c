#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DIM_BUFFER 100

int main(){

    FILE* pipe_fp = popen("./filter", "r");

    if(pipe_fp == NULL){
        perror("popen");
        exit(EXIT_FAILURE);
    }

    int c;

    while((c = fgetc(pipe_fp)) != EOF){
        putchar(c);
        fflush(stdout);
    }

    pclose(pipe_fp);
    return 0;
}