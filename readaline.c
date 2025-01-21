#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  // for size_t
#include "readaline.h"

/* Maximum allowed line length -> aiming for partial credit */ 
#define MAX_LINE_LENGTH 1000  

/* readaline function based off "readaline.h" function declaration*/
size_t readaline(FILE *inputfd, char **datapp) {
    /* Error check for null arguments */
    if (inputfd == NULL || datapp == NULL) {
        fprintf(stderr, "readaline: NULL argument\n");
        /* Exit error code */
        exit(4); 
    }

    /* Initial buffer size (will expand as needed) */
    size_t buffer_size = 100;  
    /* To track length of the line */
    size_t length = 0; 

    /* Allocate initial buffer using malloc */ 
    /* ??? should we do char *buffer = malloc(capacity) ???*/
    *datapp = (char *)malloc(buffer_size);
    if (*datapp == NULL) {
        fprintf(stderr, "readaline: memory allocation failed\n");
        exit(4); 
    }

    /* Read the input character by character */ 
    int c;
    while ((c = fgetc(inputfd)) != EOF) {
        /* If we exceed the buffer size, reallocate */ 
        if (length >= buffer_size - 1) {
            /* Double buffer_size if needed */
            buffer_size *= 2;
            *datapp = (char *)realloc(*datapp, buffer_size);
            if (*datapp == NULL) {
                fprintf(stderr, "readaline: memory allocation failed\n");
                exit(4); 
            }
        }

        /* Store the character in the buffer */ 
        (*datapp)[length] = (char)c;
        length++;

        // If we encounter a newline, break
        if (c == '\n') {
            break;
        }

        /* If the line is too long, report an error and exit */ 
        if (length > MAX_LINE_LENGTH) {
            fprintf(stderr, "readaline: input line too long\n");
            exit(4); 
        }
    }

    // If we read nothing (EOF), set *datapp to NULL
    if (length == 0 && c == EOF) {
        *datapp = NULL;
        return 0;  // No more lines
    }

    // Null-terminate the string
    (*datapp)[length] = '\0';

    return length;  // Return the length of the line

    /* supposed to call free *datapp at some point? or buffer if change variable */
}

int main () {
    printf("Hello, World!\n");
    return 0;
}
