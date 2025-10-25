#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_S 100

int main (int argc, char* argv[]){

    int pipefd[2];
    char buf[BUFFER_S];
    size_t n = argc;
    ssize_t num_read;
    pid_t pid;


    pipe(pipefd);

    for(size_t i = 1; i < n; i++){

        pid = fork();

        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }else if(pid == 0){ // codice figlio

            printf("sono il figlio %zu\n", i);
            if(close(pipefd[0]) == -1){ // chiudo lato lettura
                perror("Figlio close pipefd[0]");
                exit(EXIT_FAILURE);
            }

            printf("figlio aspetta %zu\n", i);
            
            int sec = atoi(argv[i]);

            sleep(sec);

            if(close(pipefd[1]) == -1){ // chiudo lato scrittura
                perror("Figlio close pipefd[1]");
                exit(EXIT_FAILURE);
            }

            printf("figlio %zu termina\n", i);
            exit(EXIT_SUCCESS);

        }
    }

    if(pid > 0){ // codice padre

        printf("sono il padre\n");

        if(close(pipefd[1]) == -1){ // chiudo lato scrittura
                perror("padre close pipefd[1]");
                exit(EXIT_FAILURE);
        }

        for(;;){

            num_read = read(pipefd[0], buf, BUFFER_S);
            
            // gestione errori read
            if(num_read == -1){
                perror("read");
                exit(EXIT_FAILURE);
            }else if(num_read == 0){ // End of file 
                printf("EOF\n");
                break; 
            }else{ // scrivo su stdout i dati letti
                break;
            }   

        }

        if(close(pipefd[0]) == -1){ // chiudo lato lettura
            perror("padre close pipefd[0]");
            exit(EXIT_FAILURE);
        }

    }
}