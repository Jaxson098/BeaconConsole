#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"
#include "cJSON.h"

struct countersStruct counters = {0};

char open_ports[10][1029] = {};

// cJSON *json;

void* updateOpenPorts(void* arg) {
    DIR* dir = opendir("/dev");

    if (dir == NULL) {
        return NULL;
    }

    struct dirent* entity;
    entity = readdir(dir);

    int i;
    while(1) {
        i = 0;
        while(entity != NULL) {
            // printf("name %s\n", entity->d_name);
            if (strstr(entity->d_name,"tty") != NULL && i<10) {
                strcpy(open_ports[i],"/dev");
                strcat(open_ports[i],entity->d_name);
                i++;
            }
            entity=readdir(dir);
        }
        for (int f = i; f<10; f++) {
            strcpy(open_ports[f],"");
        }
        rewinddir(dir);
        usleep(100000);
    }
}

void* updateJSON(void* arg) {

    FILE *fp = fopen("./state.json", "w");

    while(1) {
        if (fp == NULL) {
            return NULL;
        }

        cJSON *json = cJSON_CreateObject();

        cJSON_AddNumberToObject(json, "CF_B", counters.CF_B);
        cJSON_AddNumberToObject(json, "CF_R", counters.CF_R);
        cJSON_AddNumberToObject(json, "WM_G", counters.WM_G);
        cJSON_AddNumberToObject(json, "M_B", counters.M_B);
        cJSON_AddNumberToObject(json, "M_G", counters.M_G);
        cJSON_AddNumberToObject(json, "M_Y", counters.M_Y);
        cJSON_AddNumberToObject(json, "M_R", counters.M_R);
        cJSON_AddNumberToObject(json, "M_P", counters.M_P);
        cJSON_AddStringToObject(json,"gamemode", gamemode);
        
        char *json_str = cJSON_Print(json);

        printf("%s", json_str);

        truncate("./state.json",0);
        rewind(fp);
        fputs(json_str, fp);
        
        // free the JSON string and cJSON object
        cJSON_free(json_str);
        cJSON_Delete(json);

        usleep(100000);
    }
}