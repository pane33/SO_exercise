#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void signal_handler(int sig){

    if(sig == SIGINT){

        printf("Genitore: segnale_stato_figlio_ricevuto\n");

    }

}

int main(){

    pid_t pid_figlio;

    signal(SIGINT, signal_handler);

    pid_figlio = fork();

    if(pid_figlio < 0){
        printf("errore_fork");
        exit(EXIT_FAILURE);

    }else if(pid_figlio == 0){
        
        // codice figlio
        printf("inizio_attivita_figlio (PID = %d)\n", getpid());

        for(size_t i = 0; i < 10; i++){

            printf("%ld\n", i);

            if(i == 5) {
                printf("completata_meta_attivita_figlio_avviso_genitore\n");
                kill(getpid(), SIGINT);
            }

            sleep(1);
        }
        

        printf("Figlio: terminato\n");

        exit(EXIT_SUCCESS);

    }else{
        //codice padre

        printf("Genitore: attendo_segnale_figlio\n");
        
        wait(NULL); // il genitore attende il segnale

        

        printf("Genitore: figlio terminato. FINE PROG\n");

    }

    return 0;

}