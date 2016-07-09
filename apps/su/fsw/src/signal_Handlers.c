

/* Includes */
#include "su_app.h"

/*This handler was modified for FIPEX*/
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext) { // should be signal_handler_IO
    uint16 i = 0;
    uint8 resp[254];
    if(siginfo-> si_code == POLL_IN){
        printf("Caught the signal.\n");
        printf("The signal is %d\n", signo);
        if (signo == 29) {
            printf("The signal that was caught was a SIGIO signal.\n");
        } else {
            perror("Bad signal");
        }
        printf("The ID of the sending process is %d\n", siginfo->si_pid);
        sleep(1);       
        read(fd, resp, sizeof resp);
        for(i = 0; i < sizeof resp; i++){
           printf("%02x ", resp[i]);
        }
        printf("\n");
        /*
        * Read the first 5 bytes of what FIPEX returns and do something about it. 
        */
        resp_flag = TRUE;
    }
     else
    {
        tcflush(fd, TCIFLUSH);
        sleep(1);
    }
    
       
}

void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext) {
    printf("\nCaught a segmentation fault and overriding default action.\n");
    exit(1);
} 

void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext) { 
    printf("\nCaught a interrupt signal and overiding default action.\n");
    close(fd);
    printf("Port closed\n");
    exit(2);
}
