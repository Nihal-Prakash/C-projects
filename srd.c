#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pfile = fopen("Student_records.txt", "rb");

    if (pfile == NULL) {
        perror("File open failed");
        return 1;
    }

    fseek(pfile, 0, SEEK_END);
    long filesize = ftell(pfile);
    rewind(pfile);
    
    char *buffer = malloc(filesize + 1);

    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
        printf("%s", buffer);
    }

    free(buffer); //because malloc
    fclose(pfile);
    return 0;
}
