/*
 * serial_send.c
 *
 *  Created on: Jun 2, 2016
 *      Author: vagrant
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int set_interface_attribs(int fd, int speed, int parity);
void serial_send(char *portname,int *buffer);
void set_blocking (int fd, int should_block);

void main()
{
    char *portname = "/dev/ttyS2";
    system("chmod 666 /dev/ttyS2"); //Change permission
    unsigned int buffer[] = {0x7E,0x00,0x00,0x00};
    serial_send(portname, buffer);
}

void serial_send(char *portname,int *buffer)
{
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC, S_IWRITE | S_IREAD);
    int i;
    
    if (fd < 0)
    {
            printf ("error %d opening %s: %s \n", errno, portname, strerror (errno));
            return;
    }

    set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    
    write(fd,buffer,sizeof buffer);
    usleep(4*100); 
               
    unsigned char buf [5];
    int n = read (fd, buf, sizeof buf);  
    for(i = 0;i<5;i++){
        printf("%x ",buf[i]);
    }
    //printf("meow");
    printf("\n");
    close(fd);
}

int set_interface_attribs(int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr\n", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr\n", errno);
                return -1;
        }
        return 0;
}


void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr\n", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes\n", errno);
}

