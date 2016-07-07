/* Includes */
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"
/* Includes */
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

/* Macros */
#define BAUDRATE B115200
#define DEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

#define SU_PIPE_DEPTH                     32

/*Data*/
int fd;
int resp_flag;

 /* Prototypes */

/* Serial related functions */
int Open_Port(void);
int Set_Attribute(void);
int Send(uint8_t *cmd);
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext);   /* definition of signal handler */
void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext);
void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext);

