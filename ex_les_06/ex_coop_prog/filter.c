#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main() {

    int c;

    while ((c = getchar()) != EOF) {

        c = toupper(c);
        putchar(c);
        fflush(stdout);

    }
    
    return 0;
}