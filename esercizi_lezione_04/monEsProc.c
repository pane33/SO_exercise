#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

static void signal_handler(int sig){

    if(sig == 0){

        printf("Genitore: segnale zero ricevuto\n");

    }

}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("uso: %s <PID_figlio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(0, signal_handler);

    pid_t pid = atoi(argv[1]);

    kill(pid, 0); // invio segnale zero

    if(errno == ESRCH){
        printf("Genitore: processo_figlio_non_esiste\n");
    }else if(errno == EPERM){
        printf("Genitore: nessun_permesso_per_inviare_segnale_figlio\n");
    }else{
        printf("Genitore: segnale_inviato_con_successo_a_figlio (PID = %d)\n", pid);
    }

}