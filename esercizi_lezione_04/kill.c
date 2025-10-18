#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> // per getpid pid_t
#include <signal.h> // per kill

int main(){

    pid_t pid;

    pid = fork();

    if(pid < 0){

        printf("Errore nella fork\n");
        exit(1);

    }else if(pid == 0){
        //codice figlio

        printf("Figlio in esecuzione (PID = %d)\n", getpid());

        

        printf("Figlio in esecuzione (PID = %d)\n", getpid());

    }else{
        //codice padre
        sleep(3);
        
        printf("Padre in esecuzione (PID = %d) termina figlio (PID = %d)\n", getpid(), pid);

        kill(pid, SIGKILL);

        sleep(3);

        printf("Processo padre continua esecuzione (PID = %d)\n", getpid());

    }

}
