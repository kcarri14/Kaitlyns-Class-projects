#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <float.h>

typedef struct {
    char name[100];
    char ep[100];
    char date[100];
    int number;
    char track_name[100];
    char artist[100];
}Info;

int parsing(char *line, Info *information){
    char buffer[4000];
    strcpy(buffer,line);
    char *token= strtok(buffer, ",");
    if(!token){
        return -1;
    }
    strcpy(information->name, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->ep, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->date, token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    information->number = atoi(token);

    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->track_name, token);
    token= strtok(NULL, ",");
    if(!token){
        return -1;
    }
    strcpy(information->artist, token);

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
        printf("INSERT INTO albums_and_songs (album_name, ep, album_release, track_number, track_name, artist) VALUES ('%s','%s','%s', %d, '%s','%s');\n", information[i].name, information[i].ep, information[i].date, information[i].number, information[i].track_name, information[i].artist);
    }
    free(information);
    return 0;
}

