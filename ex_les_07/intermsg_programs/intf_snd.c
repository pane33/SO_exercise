#include "f_header.h"

int main(){

    int msqid;

    msqid = msgget(KEY, 0666 | IPC_CREAT);

    if(msqid == -1){
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }



    while(1){ // wait for user input

        struct msg_buffer message;    

        // Get message type from user
        printf("Enter message type (long > 0): ");
        if (scanf("%ld", &message.mtype) != 1) {
            
            // controllo per EOF o errore di input
            if (feof(stdin) || ferror(stdin)) {
                printf("\nUscita.\n");
                break; // Esce dal loop while(1)
            }

            fprintf(stderr, "Tipo non valido. Riprova.\n");
            // Pulisce il buffer di input da caratteri non validi
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue; // Ritorna all'inizio del loop
        }
        
        // Consuma il '\n' lasciato da scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF);    

        // Get message text from user
        printf("Enter message text (max 100 char): ");
        if (fgets(message.mtext, sizeof(message.mtext), stdin) == NULL) {
            printf("\nUscita.\n");
            break;
        }
        // Rimuovi il carattere '\n' (a capo) che fgets include
        message.mtext[strcspn(message.mtext, "\n")] = '\0';

        // Send message
        if(msgsnd(msqid, &message, strlen(message.mtext), IPC_NOWAIT) == -1){
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        printf("Message sent: %s\n", message.mtext);
    }

    return 0;
}