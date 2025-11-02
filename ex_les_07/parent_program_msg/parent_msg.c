#include "../intermsg_programs/f_header.h"


int main(){

    int msqid;

    msqid = msgget(KEY, 0666 | IPC_CREAT);

    if(msqid == -1){
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process: execute sender program
        
        struct msg_buffer message;
        message.mtype = 1; // Message type
        strcpy(message.mtext, "Hello from child process!");
        size_t msg_len = strlen(message.mtext) + 1; // +1 to include null terminator

        if(msgsnd(msqid, &message, msg_len, IPC_NOWAIT) == -1){
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        printf("Messaggio inviato con successo alla coda (dimensione: %ld bytes) dal processo figlio.\n\n", msg_len);

        // Exit child process
        exit(EXIT_SUCCESS);

    }
    else
    {
        // Parent process: execute receiver program
        
        struct msg_buffer message;
        if(msgrcv(msqid, &message, sizeof(message.mtext), 1, 0) == -1){
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        printf("Messaggio ricevuto dal processo padre: %s\n", message.mtext);

        // Wait for child process to finish
        wait(NULL);

        // --- dealloco ---
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl IPC_RMID");
            exit(EXIT_FAILURE);
        }
        printf("\nCoda messaggi %d rimossa.\n", msqid);

        exit(EXIT_SUCCESS);
    }
    

}