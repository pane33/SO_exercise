#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int idata = 111; // Variabile globale (segmento dati)

int main(int argc, char *argv[]) {
    int istack = 222; // Variabile locale (stack)
    pid_t procPid;

    switch (procPid = fork()) {
        case -1:
            exit(EXIT_FAILURE); // Gestione errore fork
        case 0: // Codice del figlio
            idata *= 3;
            istack *= 3;
            break;
        default: // Codice del genitore
            sleep(3); // Attende che il figlio esegua
            break;
    }

    // Entrambi i processi stampano i valori delle variabili
    printf("PID=%ld %s idata=%d istack=%d\n",
           (long) getpid(), (procPid == 0) ? "(child)" : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}