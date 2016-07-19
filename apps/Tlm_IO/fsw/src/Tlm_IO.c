
/* Includes */
#include "Tlm_IO.h"
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

void paramSetUp(void) {
    uint8_t getFrequency[] = {0xC0, 0x21, 0x00, 0xC0};
    uint8_t setFrequency[] = {0xC0, 0x20, 0x1A, 0x16, 0x77, 0x80, 0xC0};
    uint8_t setPower[] = {0xC0, 0x22, 0xA0, 0xC0}; /* Full Power*/
    uint8_t getPower[] = {0XC0, 0x23, 0x00, 0xC0}; 
    printf("\nSending the setFrequency Instruction\n");
    printf("\nIf Successful, the message should have 0x00 in its data component.\n");
    write(fd, setFrequency, sizeof setFrequency);
    sleep(1);
    printf("\nSending the getFrequency Instruction\n");
    write(fd, getFrequency, sizeof getFrequency);
    sleep(1);
    printf("\nSending the setPower Instruction\n");
    write(fd, setPower, sizeof setPower);
    printf("\nIf Successful, the message should have 0x00 in its data component.\n");
    sleep(1);
    printf("\nSending the getPower Instruction\n");
    write(fd, getPower, sizeof getPower);
    sleep(1);
}

int Tlm_IO_main(int argc, char**argv) {

    int i = 0;
    fd = Open_Port();
    if(fd == -1)
    {
        printf("Port not opened");
        exit(1);
    }
    Set_Attribute();
    /***************/
    /* Setting up parameters */
    paramSetUp();


    /*uint8_t sndGoofyMsg[] = {0xC0, 0x00, 0x7E, 0x01, 0x00, 0x01, 0x00, 
        0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7E, 0xC0};
    for(;i<10;i++){
        printf("\nSending the goofy message Instruction\n");
        write(fd, sndGoofyMsg, sizeof sndGoofyMsg);
        sleep(10);
        printf("\nThere will be no response to the console \n");
    }*/


    for(;;)
    {
        sleep(1);
    }
    return(0);
      
}

int32 


