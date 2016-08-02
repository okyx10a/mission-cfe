

/* Includes */
#include "su_app.h"

/*This handler was modified for FIPEX*/
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext) { // should be signal_handler_IO
    uint16 i,j;
    uint8 resp[254];
    if(siginfo-> si_code == POLL_IN){
		if(j == 0)//pick the first response only 
		{
			//printf("Caught the signal.\n");
			//printf("The signal is %d\n", signo);
			if (signo == 29) {
				printf("The signal that was caught was a SIGIO signal.\n");
			} else {
				perror("Bad signal");
			}
			printf("The ID of the sending process is %d\n", siginfo->si_pid);
			sleep(1);       
			read(app_data.fd, resp, 5);
			for(i = 0; i < 5; i++){
				printf("%02x ", resp[i]);
			}
			printf("\n");
			/*
			* Read the first 5 bytes of what FIPEX returns and do something about it. 
			*/
			app_data.resp_flag = TRUE;// a flag indicates a reply has been recieved, may be better ways to do it?
		}
		j++;
		
    }
    else
    {
		    j = 0;
        sleep(1);
        tcflush(app_data.fd, TCIFLUSH);  
    }
    
       
}

void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext) {
    printf("\nCaught a segmentation fault and overriding default action.\n");
    exit(1);
} 

void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext) { 
    printf("\nCaught a interrupt signal and overiding default action.\n");
    close(app_data.fd);
    printf("Port closed\n");
    exit(2);
}
