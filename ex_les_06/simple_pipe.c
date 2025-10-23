#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#define BUF_SIZE 10

void errExit(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

// 
// 
int main(int argc, char *argv[]) {
    int pfd[2];                             /* Pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;

    // if (argc != 2 || strcmp(argv[1], "--help") == 0)
    //     usageErr("%s string\n", argv[0]);

		// printf(" [DEBUG] prima di pipe()\n");
    if (pipe(pfd) == -1) /* Create the pipe */
        errExit("pipe");

		// printf(" [DEBUG] prima di switch\n");
    switch (fork()) {
    case -1:
        errExit("fork");

    case 0: /* Child  - reads from pipe */
				// printf(" [DEBUG] figlio: prima di chiusura write-end\n");
        if (close(pfd[1]) == -1) /* Write end is unused */
            errExit("close - child");

        for (;;) { /* Read data from pipe, echo on stdout */
						// printf(" [DEBUG] figlio: prima di read()\n");
            numRead = read(pfd[0], buf, BUF_SIZE);
            printf("Ho letto %ld bytes\n",numRead);
            if (numRead == -1)
                errExit("read");
            if (numRead == 0)
                break; /* End-of-file */
						// printf(" [DEBUG] figlio: prima di write()\n");
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                errExit("child - partial/failed write");
            write(STDOUT_FILENO, "\n", 1);
        }


				// printf(" [DEBUG] figlio: prima di chiusura read-end\n");
        if (close(pfd[0]) == -1)
            errExit("close");
        _exit(EXIT_SUCCESS);

    default: /* Parent - writes to pipe */
				// printf(" [DEBUG] padre: prima di chiusura di read-end\n");
        if (close(pfd[0]) == -1) /* Read end is unused */
            errExit("close - parent");

				// printf(" [DEBUG] padre: prima di write()\n");
        if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
            errExit("parent - partial/failed write");
        printf("Ho scritto %ld bytes\n",strlen(argv[1]));
				// printf(" [DEBUG] padre: prima di chiusura di write-end\n");
        if (close(pfd[1]) == -1) /* Child will see EOF */
            errExit("close");
        //wait(NULL); /* Wait for child to finish */
        exit(EXIT_SUCCESS);
    }
}
