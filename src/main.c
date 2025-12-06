#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <dirent.h>

#include "utils.h"

//on startup initialize all serial ports connected and put them in an object with their fd and path
//create a worker thread for each port
//create a monitoring thread to watch for disconected by comparing to the ports obj, and open new thread with a new fd
//have an atomic str be the msg needed to write updated by main()
//inside worker threads check if the str is equal to last written if not write the atomic string and change the local last written var
//on space click write whatever the json has as the game mode
//reset all vars to 0 and record
//another thread constantly writes counters to json on change
//on end write stop to all ports

int main() {
    updateOpenPorts();
    for (int i = 0; i<10; i++) {
        printf("open_ports = %s\n",open_ports[i]);
    }
    return 0;
}