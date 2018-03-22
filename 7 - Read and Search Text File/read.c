#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

int main() {
    char buffer[SIZE+1];
    size_t nread;

    int lineNo = 1, index = 0;

    int results[SIZE];
    for(int i = 0; i < SIZE; i++)
        results[i] = 0;

    FILE *file = fopen("test.txt", "r");
    if (file) {
        while ((nread = fread(buffer, 1, 1024, file)) > 0) {
            if(strstr(buffer, "vsgshsajkdlsandabsdksadn")) {
                results[index] = lineNo;
                index++;
            }
            lineNo++;
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Cannot open input file test.txt\n");
        exit(1);
    }

    for(int i = 0; i < SIZE; i++)
        if(results[i] != 0) {
            printf("%d ", results[i]);
            fflush(stdout);
        }       
    
}