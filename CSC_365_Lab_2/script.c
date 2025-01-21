#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <float.h>

typedef struct {
    int Id;
    char airline[50];
    char abbrev[30];
    char country[3];
}Info;

int parsing(char *line, Info *information){
    char buffer[4000];
    strcpy(buffer,line);


    char *token= strtok(buffer, ",");
    if(!token){
        return -1;
    }
    information->Id = atoi(token);


    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->airline, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->abbrev, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->country, token);

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
            //printf("Error: line entry is malformed %d\n", line_num);
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
        printf("INSERT INTO AIRPLANES(ID, AIRLINE, ABBREV, COUNTRY) VALUES (%d, '%s', '%s', '%s');\n", information[i].Id, information[i].airline, information[i].abbrev, information[i].country);
    }
    free(information);
    return 0;
}