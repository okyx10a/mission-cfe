
/* Includes cfe*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

/* Includes */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdio.h>
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h>  /* File control definitions */
#include <sys/signal.h>
#include <sys/types.h>
#include <stdlib.h>



/* Macros */
 #define BAUDRATE B115200
 #define DEVICE "/dev/ttyS2"
 #define _POSIX_SOURCE 1 /* POSIX compliant source */
 #define FALSE 0
 #define TRUE 1
 #define BUF_SIZE 1024 /* MTU of a KISS packet */

/*Data*/
int fd;

/* Prototypes */
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext);   /* definition of a signal handler for SIGIO */
void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext); /* definition  of a signal handler for SIGSEG */  
void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext); /* definition of signal handler */
