#include "render.h"

char *Render(char *filename){
    FILE *file = fopen(filename, "r");
    
    if(file == NULL){
        printf("Error, no existe el fichero");
        return NULL;
    }
    if(fseek(file, 0, SEEK_END)) return NULL;
    long fsize = ftell(file);
    rewind(file);

    char *contents = calloc(1+fsize, sizeof(char));
    char ch;
    int i = 0;
    while((ch = fgetc(file)) != EOF){
        contents[i] = ch;
        i++;
    }
    fclose(file);
    return contents;
}
