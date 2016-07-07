#define _GNU_SOURCE
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

#include <stdint.h>
#include <limits.h> /* stdrol
#include "../inc/input.h"
#include "../inc/memory.h"
/************/


#define BUF_SIZE 256

char SERIAL_BUF[BUF_SIZE]; //buffer for where data is put

/* Prototypes */
void Signal_Handler_IO(int signo, siginfo_t *siginfo, void *ucontext); //definition of signal handler
void Signal_Handler_INT(int signo, siginfo_t *siginfo, void *ucontext); //definition of signal handler
/**************/

void Signal_Handler_IO(int signo, siginfo_t *siginfo, void *ucontext)

{

        int size = 0, i;
        printf("\nReceived SIGIO signal. (%d) for %d code %d", siginfo->si_signo, siginfo->si_fd, siginfo->si_code);
        if (siginfo->si_code == POLL_IN) // Check if signal indicates input
        {
                if ((size = read(siginfo->si_fd, SERIAL_BUF, BUF_SIZE)) == -1)
                        { perror("read"); return; }

                printf("\nRead %d bytes: ", size);

        }

        else if (siginfo->si_code == POLL_OUT) // Check if signal indicates output

        {

                printf("\nReady to Write\n");

                return;

        }

        if (size > 0)

        {

                for (i = 0; i < size; i++)//for chars in string

                {

                        printf("0x%x ",SERIAL_BUF[i]);

                }  //end of for all chars in string

                SERIAL_BUF[size] = '\0';

                printf("%s", SERIAL_BUF);

        }  //end if size > 0

        return;

}


void Signal_Handler_INT(int signo, siginfo_t *siginfo, void *ucontext)

{

        // Close program on CTRL-C

        printf("\nReceived SIGINT signal. (%d) for %d code %d", siginfo->si_signo, siginfo->si_fd, siginfo->si_code);

        // Close Port

        SerialOpen(NULL, 0);

        // Exit Program

        exit(0);

}

int SerialOpen(char *devicename, long BaudRate)

{

        static int fd; // File descriptor

        static struct termios oldtio, newtio; // Old and new settings for port

        struct sigaction saio; // Definition of signal action


        if(devicename == NULL) // Call with (0, 0) to close port

        {

                printf("\nClosing Port %d\n", fd);

                // Restore old port settings

                tcflush(fd, TCIOFLUSH);

                tcsetattr(fd, TCSANOW, &oldtio);

                if(close(fd) == -1) //close the com port

                        { perror("closing port"); return -1; }

                return 0;

        }


        //open the device (com port) to be non-blocking (read will return immediately)
        printf("\nOpening Serial Port %s", devicename);

        if((fd = open(devicename, O_RDWR | O_NOCTTY | O_NONBLOCK)) == -1)

                { perror(devicename); return -1; }

        printf("\nOpened port %s as %u\n", devicename, fd);


        // Install the interrupt handler

        saio.sa_sigaction = Signal_Handler_INT;

        sigemptyset(&saio.sa_mask); //saio.sa_mask = 0;

        saio.sa_flags = SA_SIGINFO;

        saio.sa_restorer = NULL;

        sigaction(SIGINT, &saio, NULL);


        // Install the serial handler before making the device asynchronous

        saio.sa_sigaction = Signal_Handler_IO;

        sigemptyset(&saio.sa_mask); //saio.sa_mask = 0;

        saio.sa_flags = SA_SIGINFO;

        saio.sa_restorer = NULL;

        sigaction(SIGIO, &saio, NULL);


        // allow the process to receive SIGIO

        if(fcntl(fd,F_SETOWN,getpid()) == -1) {perror(devicename);}

        // Set fd signals (needed for siginfo to be populated)

        if(fcntl(fd,F_SETSIG,SIGIO) == -1) {perror(devicename);}


        // Make the file descriptor asynchronous

        // FNONBLOCK causes read to return immediately, also FNDELAY

        fcntl(fd, F_SETFL, FASYNC);

        tcgetattr(fd, &oldtio); // save current port settings


        // set new port settings for raw port access

        newtio.c_cflag = BaudRate | CS8 | CREAD | CLOCAL;

        newtio.c_iflag = IGNPAR;

        newtio.c_oflag = 0;

        newtio.c_lflag = 0; //ICANON does canonical input processing

        newtio.c_cc[VMIN] = 0; // Wait until x bytes read (blocks!)

        newtio.c_cc[VTIME] = 0; // Wait x * 0.1s for input (unblocks!)

        tcflush(fd, TCIFLUSH);

        tcsetattr(fd, TCSANOW, &newtio);

        return fd;

}
