#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


// legge caratteri da tstiera 
int main() {

    int c;

    while ((c = getchar()) != EOF) { // prendo tramite stdinput i caratteri singoli

        c = toupper(c); // metto in maiuscolo
        putchar(c); // scrivo in stdoutput
        fflush(stdout); // forzo la scrittura in tempo reale per evitare che la scrittura venga rimandata

    }
    
    return 0;
}