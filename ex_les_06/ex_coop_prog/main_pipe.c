#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DIM_BUFFER 100

int main(){

    FILE* pipe_fp = popen("./filter", "r"); // apro in lettura tramite pipe

    // gestisco l'errore
    if(pipe_fp == NULL){
        perror("popen");
        exit(EXIT_FAILURE);
    }

    int c;
    
    // leggo i caratteri mano a mano che vengono inseriti da tastiera tramite "filter.exe"
    while((c = fgetc(pipe_fp)) != EOF){
        putchar(c); // scrivo in stout
        fflush(stdout); // forzo il tempo reale
    }


    // chiudo pipe
    pclose(pipe_fp);
    return 0;
}