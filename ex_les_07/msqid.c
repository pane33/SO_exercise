#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
/*
@brief Creates a new message queue or accesses an existing one.
@param key A unique identifier for the message queue.
@param msgflg Flags that determine the behavior of the message queue creation/access.
@return On success, returns the message queue identifier (msqid). On failure, returns -1

int msgget(key_t key, int msgflg);
*/

// msg structure
struct msg_buffer {
    long mtype;       // Tipo (deve essere > 0)
    char mtext[100];  // Dati
};

int main() {

    int msqid;
    key_t key = 1234; // Unique key for the message queue

    struct msqid_ds ds_buffer;

    // Create a new message queue or access an existing one
    msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    printf("Coda di messaggi creata con ID: %d\n", msqid);

    // ask kernel to fill the struct decleared
    if(msgctl(msqid, IPC_STAT, &ds_buffer) == -1){
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    // print the stats
    printf("--- Statistiche della coda ---\n");
    printf("Dimensione massima della coda (msg_qbytes):  %lu bytes\n", ds_buffer.msg_qbytes);
    printf("Numero messaggi in coda (msg_qnum):   %lu messaggi\n", ds_buffer.msg_qnum);
    printf("Tempo dall'ultimo messaggio inviato (msg_stime):   %lu messaggi\n", ds_buffer.msg_stime);
    printf("------------------------------\n");

    // sending a massage to the queue

    struct msg_buffer message;
    message.mtype = 1; // Message type
    strcpy(message.mtext, "Hello, World!");

    if(msgsnd(msqid, &message, strlen(message.mtext), IPC_NOWAIT) == -1){
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Messaggio inviato con successo alla coda (dimensione: %ld bytes).\n\n", strlen(message.mtext));

    // --- Statistiche POST ---
    // ask kernel to fill the struct decleared (upgrading stats)
    if(msgctl(msqid, IPC_STAT, &ds_buffer) == -1){
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("--- Statistiche (Dopo) ---\n");
    printf("Numero messaggi in coda (msg_qnum):   %lu\n", ds_buffer.msg_qnum);
    printf("Byte correnti in coda (msg_cbytes): %lu\n", ds_buffer.__msg_cbytes);
    printf("Tempo ultimo invio (msg_stime):     %ld (secondi)\n", ds_buffer.msg_stime);
    // Stampiamolo in modo leggibile
    printf("Tempo ultimo invio (leggibile):   %s", ctime(&ds_buffer.msg_stime));
    printf("------------------------------\n");

    // --- dealloco ---
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }
    printf("\nCoda messaggi %d rimossa.\n", msqid);

    return 0;

}