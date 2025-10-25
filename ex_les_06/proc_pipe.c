// ...existing code...
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_S 100

int main(int argc, char *argv[]){

    int pipefd[2];
    char buf[BUFFER_S];
    ssize_t num_read;

    // condizioni di utulizzo
    if (argc != 2 || strcmp(argv[1], "--help") == 0){
        fprintf(stderr, "Usage: %s string_to_send\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    // controllo errori pipe
    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    int pid = fork();

    switch(pid){
        case -1: // gestisco errore
            perror("fork");
            exit(EXIT_FAILURE);

        case 0: // codice figlio

            if(close(pipefd[1]) == -1){ // chiudo lato scrittura
                perror("Figlio close pipefd[1]");
                exit(EXIT_FAILURE);
            }

            
            for(;;){
                // lettura dal pipe
                num_read = read(pipefd[0], buf, BUFFER_S);
                printf("Ho letto %zd bytes\n", num_read);

                // gestione errori read
                if(num_read == -1){
                    perror("read");
                    exit(EXIT_FAILURE);
                }else if(num_read == 0){ // End of file 
                    break; 
                }else{ // scrivo su stdout i dati letti
                    if(write(STDOUT_FILENO, buf, num_read) != num_read){
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                    // Aggiungo una nuova linea per chiarezza
                    if (write(STDOUT_FILENO, "\n", 1) != 1) {
                        perror("write newline");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            // chiudo lato lettura
            if(close(pipefd[0]) == -1){ 
                perror("Figlio close pipefd[0]");
                exit(EXIT_FAILURE);
            }

            _exit(EXIT_SUCCESS);

        default: // codice padre

            // chiudo lato lettura
            if(close(pipefd[0]) == -1){ 
                perror("Padre close pipefd[0]");
                exit(EXIT_FAILURE);
            }
            
            // scrivo sul pipe e gestisco errori
            if(write(pipefd[1], argv[1], (ssize_t)strlen(argv[1])) != (ssize_t)strlen(argv[1])){
                perror("write");
                exit(EXIT_FAILURE);
            }


            printf("Ho scritto %zu bytes\n", strlen(argv[1]));

            // chiudo lato scrittura
            if(close(pipefd[1]) == -1){ 
                perror("Padre close pipefd[1]");
                exit(EXIT_FAILURE);
            }

            wait(NULL); // attendo terminazione figlio

            exit(EXIT_SUCCESS);
    }

    return 0;
}