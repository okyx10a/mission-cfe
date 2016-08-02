/* Includes cfe*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"
/* Includes std library*/
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

/* Macros */
#define BAUDRATE B115200
#define DEVICE "/dev/ttyS3"
#define _POSIX_SOURCE 1 /* POSIX compliant source */


#define SU_PIPE_DEPTH                     32


/*Data*/
typedef struct{
    uint32              fd;
    boolean             resp_flag;
    su_script_t         active_script;
    su_hk_tlm_t         SU_HkTelemetryPkt;
    CFE_SB_PipeId_t     SU_CommandPipe;
    CFE_SB_MsgPtr_t     SUMsgPtr;
}su_app_data;

typedef struct{
    uint8               LEN;
    uint8[4]            STARTTIME;
    uint8[2]            REPEATTIME;
    uint8               CMD_CNT;
    uint8               **CMD;
    uint8[2]            *DELAY;
}su_script_t;


 /* Prototypes */

/* Serial related functions */
int32 Open_Port(void);
int32 Set_Attribute(void);
int32 Send(uint8 *cmd);
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext);  
void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext);
void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext);

