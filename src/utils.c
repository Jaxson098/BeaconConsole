#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <dirent.h>

#include "utils.h"

struct countersStruct counters = {0};

char open_ports[10][1029] = {};

void updateOpenPorts() {
    DIR* dir = opendir("/dev");

    struct dirent* entity;
    entity = readdir(dir);

    int i = 0;
    while(entity != NULL) {
        // printf("name %s\n", entity->d_name);
        if (strstr(entity->d_name,"tty") != NULL && i<10) {
            strcpy(open_ports[i],"/dev");
            strcat(open_ports[i],entity->d_name);
            i++;
        }
        entity=readdir(dir);
    }
    for (int f = i; f>10; f++) {
        strcpy(open_ports[f],"");
    }
    closedir(dir);
}