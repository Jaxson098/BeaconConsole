#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>

#include "utils.h"
#include "cJSON.h"

struct countersStruct counters = {0};

char open_ports[10][255] = {0};

pthread_mutex_t open_ports_lock;
pthread_mutex_t gamemode_lock;

//not use as a bool flag just toggled betwen 1 and 0 to see in the threads if something changed by comparing it to the last value
_Atomic int changedFlag = 0;
_Atomic int GM_changedFlag = 0;


void* updateOpenPorts(void* arg) {
    char open_ports_pre_change[10][255] = {0};

    DIR* dir = opendir("/dev");

    if (dir == NULL) {
        return NULL;
    }

    struct dirent* entity;
    entity = readdir(dir);

    int i;
    i = 0;

    while(1) {
        pthread_mutex_lock(&open_ports_lock);

        for (int k = 0; k<10; k++) {
            strcpy(open_ports_pre_change[k],open_ports[k]);
        }
        i = 0;
        while(entity != NULL && i<10) {
            // printf("name %s\n", entity->d_name);
            if (strstr(entity->d_name,"tty") != NULL) {
                strcpy(open_ports[i],"/dev/");
                strcat(open_ports[i],entity->d_name);
                i++;
            }
            entity=readdir(dir);
        }
        for (int f = i; f<10; f++) {
            strcpy(open_ports[f],"");
        }

        pthread_mutex_unlock(&open_ports_lock);

        for (int k = 0; k<10; k++) {
            if (strcmp(open_ports[k],open_ports_pre_change[k]) != 0) {
                if (changedFlag == 0) {changedFlag = 1;} else {changedFlag = 0;}
                break;
            }
        }
        rewinddir(dir);
        sleep(1);
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

        pthread_mutex_lock(&gamemode_lock);
        cJSON_AddStringToObject(json,"gamemode", gamemode);
        pthread_mutex_unlock(&gamemode_lock);
        
        char *json_str = cJSON_Print(json);

        truncate("./state.json",0);
        rewind(fp);
        fputs(json_str, fp);
        
        // free the JSON string and cJSON object
        cJSON_free(json_str);
        cJSON_Delete(json);

        usleep(100000);
    }
}

void* serialCom(void* arg) {
    int threadID = *((int*)arg);
    char lastSent[3] = "";
    int lastchangedFlag = changedFlag;
    int GM_lastchangedFlag = GM_changedFlag;
    char path[255];

    int fd;
	char text[3];
	struct termios options; //Serial ports setting struct

    //Set up serial port
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; // setup baud rate, byte size, no modem needed only using local connetions, allow reading
	options.c_iflag = IGNPAR;
	options.c_oflag = 0; //output = raw data
	options.c_lflag = 0; //input = raw data

    pthread_mutex_lock(&open_ports_lock);
    strcpy(path,open_ports[threadID]);
    pthread_mutex_unlock(&open_ports_lock);

    fd = open(path, O_RDWR | O_NDELAY | O_NOCTTY);
    if (fd < 0) {
        printf("Error opening serial port");
    }

    //Apply the settings
    tcflush(fd, TCIOFLUSH); //flush everything
    tcsetattr(fd, TCSANOW, &options); //apply options to fd, make changes happen now

    while (1) {
        if (strcmp(path,"") != 0) {
            //Read from serial port
            memset(text, 0, 3);
            read(fd, text, 3);
            printf("Received string: %s\n", text);

            if (strcmp(text,"CFB") == 0) {counters.CF_B++;}
            if (strcmp(text,"CFR") == 0) {counters.CF_R++;}
            if (strcmp(text,"WMG") == 0) {counters.WM_G++;}
            if (strcmp(text,"MB") == 0) {counters.M_B++;}
            if (strcmp(text,"MG") == 0) {counters.M_G++;}
            if (strcmp(text,"MY") == 0) {counters.M_Y++;}
            if (strcmp(text,"MR") == 0) {counters.M_R++;}
            if (strcmp(text,"MP") == 0) {counters.M_P++;}

        } if (lastchangedFlag != changedFlag) {

            pthread_mutex_lock(&open_ports_lock);
            strcpy(path,open_ports[threadID]);
            pthread_mutex_unlock(&open_ports_lock);

            fd = open(open_ports[threadID], O_RDWR | O_NDELAY | O_NOCTTY);
            if (fd < 0) {
                printf("Error opening serial port");
            }

            //Apply the settings
            tcflush(fd, TCIOFLUSH); //flush everything
            tcsetattr(fd, TCSANOW, &options); //apply options to fd, make changes happen now

            if (lastchangedFlag == 0) {lastchangedFlag = 1;} else {lastchangedFlag = 0;}

        } if (GM_lastchangedFlag != GM_changedFlag) {

            pthread_mutex_lock(&gamemode_lock);
            write(fd, gamemode, strlen(gamemode));
            pthread_mutex_unlock(&gamemode_lock);

            if (GM_lastchangedFlag == 0) {GM_lastchangedFlag = 1;} else {GM_lastchangedFlag = 0;}
        }
    }
	close(fd);
}