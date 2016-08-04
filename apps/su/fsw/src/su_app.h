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
/*Includes local headers*/
#include "su_app_msg.h"
#include "su_app_msgids.h"
#include "su_app_perfids.h"
#include "su_app_events.h"
#include "su_app_version.h"

/* Macros */
#define BAUDRATE B115200
#define DEVICE "/dev/ttyS3"
#define _POSIX_SOURCE 1 /* POSIX compliant source */


#define SU_PIPE_DEPTH                     32


/*Data*/
typedef struct{
    uint8               LEN;
    uint8               STARTTIME[4];
    uint8               REPEATTIME[2];
    uint8               CMD_CNT;
    uint8               **CMD;
    uint8               *DELAY[2];
}su_script_t;

typedef struct{
    uint32              fd;
    boolean             resp_flag;
    su_script_t         su_script;
    su_hk_tlm_t         SU_HkTelemetryPkt;
    CFE_SB_PipeId_t     SU_CommandPipe;
    CFE_SB_MsgPtr_t     SUMsgPtr;
}su_app_data_t;

su_app_data_t         app_data;

 /* Prototypes */
int32 Process_Msg(CFE_SB_MsgPtr_t *msg);
int32 script_handler(char  *scriptname,  int  access);
int32 error_handler();
int32 command_handler();
int32 response_handler();

/* Serial related functions */
int32 Open_Port(void);
int32 Set_Attribute(void);
int32 Send(uint8 *cmd);
void signal_handler_IO (int signo, siginfo_t *siginfo, void *ucontext);  
void signal_handler_SEG (int signo, siginfo_t *siginfo, void *ucontext);
void signal_handler_INT (int signo, siginfo_t *siginfo, void *ucontext);

