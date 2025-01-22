#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <float.h>

typedef struct {
    int integer;
    char title[50];
    int intger2;
    char label[50];
    char flavor[50];
}Info;

int parsing(char *line, Info *information){
    char buffer[4000];
    strcpy(buffer,line);
    char *token= strtok(buffer, ",");
    if(!token){
        return -1;
    }
    information->integer = atoi(token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->title, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    information->intger2 = atoi(token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->label, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->flavor, token);
    
    

    return 0;
}

int load_data(char *filename, Info **info){
    FILE *file = fopen(filename, "r");
    if(!file){
        perror("Error: can't open file");
        return -1;
    }
    char line[1024];
    int line_num = 0;
    int count = 0;
    *info = malloc(3143 * sizeof(Info));
    while(fgets(line, sizeof(line), file)){
        line_num++;
        if(line_num == 1){
            continue;
        }
        Info information;
        if(parsing(line, &information) == -1){
            continue;
        }
        (*info)[count++] = information;

    }
    fclose(file);
    return count;
}

int main(int argc, char*argv[]){
    Info *information = NULL;
    int count = load_data(argv[1], &information);

    if(count == -1){
        perror("Error: fail to load data\n");
        return 1;
    }
    for(int i = 0; i < count; i++){
        printf("INSERT INTO albums (AId, Title, Year, Label, Type) VALUES (%d, '%s',%d, '%s', '%s');\n", information[i].integer, information[i].title, information[i].intger2, information[i].label, information[i].flavor);
    }
    free(information);
    return 0;
}

