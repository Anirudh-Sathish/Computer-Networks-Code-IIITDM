#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char *tmp = "This string literal is arbitrary";

int main(int argc, char *argv[]){
    char *str = malloc(strlen(tmp));

    printf("%s\n", strncpy(str, tmp, 4));
    printf("%s\n", strncpy(str, tmp + 5, 10));

    free(str);
    exit(EXIT_SUCCESS);
}