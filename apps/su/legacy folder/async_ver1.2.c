#ifndef _ASYNC_C
#define _ASYNC_C
/*
* File is for testing purposes. 
*/

/* Includes */
#include "../../inc/async.h"
#include "../../inc/input.h"
#include "../../inc/memory.h"

/*
* The termios header defines the terminal control structure and the POSIX control functions.
* The two most important POSIX control functions are tcegetattr(3) & tcsetattr(3). These get and
* set a terminal device's attributes.  
*/



int Open_Port(void)
{
    printf("\nOpening Serial Port %s", DEVICE);
    if((fd = open(DEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK )) == -1)
    { 
        perror(DEVICE); 
        return -1; 
    }
    //open the device (com port) to be non-blocking (read will return immediately)
    printf("\nOpened port %s as %u\n", DEVICE, fd);
    tcflush(fd, TCIFLUSH);
    return fd;
}  

int Set_Attribute(void)
{

    static struct termios oldtio, newtio; // Old and new settings for port
    struct sigaction saio; 
    struct sigaction saseg;
    struct sigaction saint;
  
    // Install the interrupt handler
    saio.sa_sigaction = signal_handler_IO;
    sigemptyset(&saio.sa_mask); //saio.sa_mask = 0;
    saio.sa_flags = SA_SIGINFO;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio, NULL);

    /*User programs have to execute two steps to enable asynchronous notification from an input file. 
    First, they specify a process as the "owner" of the file. When a process invokes the F_SETOWN command
    using the fcntl system call, the process ID of the owner process is saved. In order to get asynchronous notification, 
    the user programs must set the FASYNC flag in the device by means of the F_SETFL fcntl command.
    http://www.makelinux.net/ldd3/chp-6-sect-4
    */
    if(fcntl(fd,F_SETOWN,getpid()) == -1) {perror(DEVICE);}
    fcntl(fd, F_SETFL, FASYNC); 
    // Set fd signals (needed for siginfo to be populated)
    if(fcntl(fd,10,SIGIO) == -1) {perror(DEVICE);} 
    tcgetattr(fd, &oldtio); // save current port settings

    saseg.sa_sigaction = signal_handler_SEG;
    sigemptyset(&saseg.sa_mask); //saio.sa_mask = 0;
    saseg.sa_flags = SA_SIGINFO;
    saseg.sa_restorer = NULL;
    sigaction(SIGSEGV, &saseg, NULL); 

    saint.sa_sigaction = signal_handler_INT;
    sigemptyset(&saseg.sa_mask); //saio.sa_mask = 0;
    saseg.sa_flags = SA_SIGINFO;
    saseg.sa_restorer = NULL;
    sigaction(SIGINT, &saint, NULL);

    // set new port settings for raw port access
    newtio.c_cflag = BAUDRATE | CS8 | CREAD | CLOCAL;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0; //ICANON does canonical input processing
    newtio.c_cc[VMIN] = 0; // Wait until x bytes read (blocks!)
    newtio.c_cc[VTIME] = 0; // Wait x * 0.1s for input (unblocks!)
    tcsetattr(fd, TCSANOW, &newtio);  
}


int Send(uint8_t *cmd){
    write(fd, cmd, sizeof cmd);
    sleep(1);
    tcflush(fd, TCIFLUSH);
    return 0; // error indicator need 
}

int main(int argc, char**argv) {

    int i = 0;
    uint8_t resp[254];
    /* FIPEX commands */
    uint8_t ping[] = {0x7E, 0x00, 0x00, 0x00}; /* Ping Command */
    uint8_t rqhk[] = {0x7E, 0x20, 0x00, 0x20};  /* Request House Keeping */
    uint8_t rlp[] = {0x7E, 0x10, 0x00, 0x10};  /* Request Last Packet */
    uint8_t init[] = {0x7E, 0x01, 0x00, 0x01};  /* Initialize */    
    uint8_t suID[] = {0x7E, 0x04, 0x00, 0x04};   /* Science unit ID */
    uint8_t SU_SM[] = {0x7E, 0x0C, 0x00, 0x0C};  /* Measurement mode */
    uint8_t SU_STDBY[] = {0x7E, 0x0A, 0x00, 0x0A}; /* standby Mode */
    uint8_t SU_SC[] = {0x7E, 0x0B, 0x00, 0x0B};    /* Health check mode */
    uint8_t SU_DP[] = {0x7E, 0x21, 0x00, 0x21};    /* Request Science Data packet */

        
    fd = Open_Port();
    if(fd == -1)
    {
        printf("Port not opend");
        exit(1);
    }
    Set_Attribute();
    /***************/
    /* Testing the commands to FIPEX */

    printf("\nSending the Ping Instruction\n");
    Send(ping);
    /*write(fd, ping, sizeof ping);
    sleep(1);
    tcflush(fd, TCIFLUSH);*/

    printf("\nSending the Init Instruction\n");
    Send(init);
    /*write(fd, init, sizeof init);
    sleep(1);
    tcflush(fd, TCIFLUSH);*/

    for(;;)
    {
        sleep(1);
    }
        
    return(0);
      
}

#endif

