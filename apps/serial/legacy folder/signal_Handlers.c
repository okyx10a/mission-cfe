#ifndef _SIGNAL_HANDLERS_C
#define SIGNAL_HANDELRS_C 

/* Includes */
#include "../../inc/async.h"

const char* get_process_name_by_pid(const int pid)
{
    char* name = (char*)calloc(1024,sizeof(char));
    if(name){
        sprintf(name, "/proc/%d/cmdline",pid);
        FILE* f = fopen(name,"r");
        if(f){
            size_t size;
            size = fread(name, sizeof(char), 1024, f);
            if(size>0){
                if('\n'==name[size-1])
                    name[size-1]='\0';
            }
            fclose(f);
        }
    }
    return name;
}

/*This handler was modified for FIPEX*/
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext) { // should be signal_handler_IO
    int size = 0;
    int i = 0;
    uint8_t resp[254];
    if(siginfo-> si_code == POLL_IN){
      //FILE* fp = fdopen(fd, "a+");
      printf("Caught the signal.\n");
      printf("The signal is %d\n", signo);
      if (signo == 29) {
          printf("The signal that was caught was a SIGIO signal.\n");
      } else {
          perror("Bad signal");
      }
      //printf("The ID of the sending process is %s\n", get_process_name_by_pid(siginfo->si_pid));
      //sleep(1);       
      read(fd, resp, sizeof resp);
      for(i = 0; i < 5; i++){
         //resp[i] = fgetc(fp);
         printf("%02x ", resp[i]);
      }
      printf("\n");
      //fclose(fp);
      //close(fd);
      /*
      * Read the first 5 bytes of what FIPEX returns and do something about it. 
      */
      }
	  //else
	  /*{
	      tcflush(fd, TCIFLUSH);
	      sleep(1);
	  }*/
    
       
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
#endif   
