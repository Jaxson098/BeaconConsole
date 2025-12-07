#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

//on startup initialize all serial ports connected and put them in an object with their fd and path
//create a worker thread for each port
//create a monitoring thread to watch for disconected by comparing to the ports obj, and open new thread with a new fd
//have an atomic str be the msg needed to write updated by main()
//inside worker threads check if the str is equal to last written if not write the atomic string and change the local last written var
//on space click write whatever the json has as the game mode
//reset all vars to 0 and record
//another thread constantly writes counters to json on change
//on end write stop to all ports

struct countersStruct {
	_Atomic int CF_B;
	_Atomic int CF_R;
	_Atomic int WM_G;
	_Atomic int M_B;
	_Atomic int M_G;
	_Atomic int M_Y;
	_Atomic int M_R;
	_Atomic int M_P;
};

struct countersStruct counters = {};

int main() {
	int fd, len;
	char text[255];
	struct termios options; /* Serial ports setting struct*/

	fd = open("/dev/ttyUSB0", O_RDWR | O_NDELAY | O_NOCTTY);
	if (fd < 0) {
		perror("Error opening serial port");
		return -1;
	}
	
	/* Set up serial port */
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; // setup baud rate, byte size, no modem needed only using local connetions, allow reading
	options.c_iflag = IGNPAR;
	options.c_oflag = 0; //output = raw data
	options.c_lflag = 0; //input = raw data

	/* Apply the settings */
	tcflush(fd, TCIOFLUSH); //flush everything
	tcsetattr(fd, TCSANOW, &options); //apply options to fd, make changes happen now

	/* Write to serial port */
	strcpy(text, "Hello from my RPi\n\r"); //put the string chars into the array text
	len = strlen(text);
	len = write(fd, text, len); //write

	/* Read from serial port */
	memset(text, 0, 255);
	len = read(fd, text, 255);
	printf("Received %d bytes\n", len);
	printf("Received string: %s\n", text);


	close(fd);
	return 0;
}