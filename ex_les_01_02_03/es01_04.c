#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> // per pid_t
#include <sys/wait.h>  // per wait

int main() {
    
    pid_t pid; // Variabile per memorizzare il PID del processo figlio

    printf("Processo padre (PID = %d) prima della fork \n", getpid());

    pid = fork(); // Creazione del processo figlio 

    if(pid < 0){
        printf("Errore nella fork \n");
        exit(1);
    } else if(pid == 0){
        // Codice del processo figlio
        printf("Processo figlio (PID = %d) \n", getpid());

        FILE *file_cond = fopen("file.txt", "a"); // apri dopo la fork per il figlio
        if (!file_cond) { perror("fopen"); exit(1); }

        fputs("riga\n", file_cond);
        fclose(file_cond);

        printf("Processo figlio (PID = %d) termina \n", getpid());
        exit(0);

    } else {
        printf("Processo padre (PID = %d) in attesa del figlio \n", getpid());
        
        wait(NULL); // Attende la terminazione del processo figlio

        printf("file.txt dopo la terminazione del figlio:\n");
        
        int ch;
        FILE *file_cond = fopen("file.txt", "r"); // apri dopo la fork per il padre (lettura)
        if (!file_cond) { perror("fopen"); exit(1); }

        while((ch = fgetc(file_cond)) != EOF) {
            putchar(ch); // Stampa il contenuto del file
        }

        fclose(file_cond);

        printf("Processo padre (PID = %d) continua \n", getpid());
    }
}