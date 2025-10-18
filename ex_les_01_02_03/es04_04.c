#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> // per pid_t
#include <sys/wait.h>  // per wait

int main(int argc, char *argv[]){

    if(argc <= 1){
        printf("Errore nell'input \n");
        exit(1);
    }

    size_t n =  (size_t)atoi(argv[1]);

    pid_t pid;

    printf("Processo padre (PID = %d) prima della fork \n", getpid());

    for(size_t i = 0; i < n; i++){

        pid = fork();

        if(pid < 0){
            // codice gestione errore
            printf("Errore nella fork \n");
            exit(1);

        }else if(pid == 0){
            // codice figlio
            printf("Processo figlio (PID = %d) creato\n", getpid());

            sleep((getpid() % 10));

            printf("Processo figlio (PID = %d) termina \n", getpid());
            exit(0);

        }else{
            
            // codice padre
            wait(NULL); // aspetto la terminazione del figlio

            printf("PID processo figlio stampato da padre: %d\n", pid);

            printf("Processo padre (PID = %d) continua \n", getpid());

        }
    }


}