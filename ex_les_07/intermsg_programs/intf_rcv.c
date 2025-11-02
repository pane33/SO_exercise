#include "f_header.h"

int main(){

    int msqid;

    msqid = msgget(KEY, 0666 | IPC_CREAT);

    if(msqid == -1){
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // receiving messages

    struct msg_buffer message;

    int type_select;

    // Get message type to receive from user
    printf("Enter message type to receive (long > 0): ");
    if (scanf("%d", &type_select) != 1 || type_select <= 0) {
        fprintf(stderr, "Tipo non valido. Uscita.\n");
        exit(EXIT_FAILURE);
    }

    /* Leggo tutti i messaggi disponibili; esco quando non ce ne sono più */
    while (1) {
        
        ssize_t r = msgrcv(msqid, &message, sizeof(message.mtext), type_select, IPC_NOWAIT);
        if (r == -1) {
            if (errno == ENOMSG) { /* nessun messaggio disponibile */ 
                break;
            } else {
                perror("msgrcv failed");
                exit(EXIT_FAILURE);
            }
        }

        printf("Message of type %ld received.\n", message.mtype);
        printf("Message received: %s\n", message.mtext);
        printf("\n");

    }


    // --- dealloco la coda ---
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }
    
    printf("\nCoda messaggi %d rimossa.\n", msqid);    

    return 0;
}