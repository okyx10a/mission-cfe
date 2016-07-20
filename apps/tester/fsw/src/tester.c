/*This module takes commands from keyborad and send them to software bus*/
/*
**   Include Files:
*/

#include "tester.h"
#include "tester_perfids.h"
#include "tester_msgids.h"
#include "tester_msg.h"
#include "tester_events.h"
#include "tester_version.h"

/*
** global data
*/

tester_hk_tlm_t    TESTER_HkTelemetryPkt;
CFE_SB_PipeId_t    TESTER_CommandPipe;
CFE_SB_MsgPtr_t    TESTERMsgPtr;

static CFE_EVS_BinFilter_t  TESTER_EventFilters[] =
       {  /* Event ID    mask */
          {TESTER_STARTUP_INF_EID,       0x0000},
          {TESTER_COMMAND_ERR_EID,       0x0000},
          {TESTER_COMMANDNOP_INF_EID,    0x0000},
          {TESTER_COMMANDRST_INF_EID,    0x0000},
       };

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* TESTER_AppMain() -- Application entry point and main process loop          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/

void Tester_Main( void );

void TESTER_AppInit(void);

void TESTER_SendCommand(void);

void Tester_Main( void )
{
    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(TESTER_APP_PERF_ID);

    TESTER_AppInit();

    /*
    ** TESTER Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(TESTER_APP_PERF_ID);

        /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        status = CFE_SB_RcvMsg(&TESTERMsgPtr, TESTER_CommandPipe, 500);
        
        CFE_ES_PerfLogEntry(TESTER_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            TESTER_SendCommand(SU_APP_CMD_MID);
        }

    }

    CFE_ES_ExitApp(RunStatus);

} /* End of TESTER_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* TESTER_AppInit() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void TESTER_AppInit(void)
{
    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp() ;

    /*
    ** Register the events
    */ 
    CFE_EVS_Register(TESTER_EventFilters,
                     sizeof(TESTER_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    CFE_SB_CreatePipe(&TESTER_CommandPipe, TESTER_PIPE_DEPTH,"TESTER_CMD_PIPE");
    CFE_SB_Subscribe(TESTER_APP_CMD_MID, TESTER_CommandPipe);
    CFE_SB_Subscribe(TESTER_APP_SEND_HK_MID, TESTER_CommandPipe);

    TESTER_ResetCounters();

    CFE_SB_InitMsg(&TESTER_HkTelemetryPkt,
                   TESTER_APP_HK_TLM_MID,
                   TESTER_APP_HK_TLM_LNGTH, TRUE);

    CFE_EVS_SendEvent (TESTER_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "TESTER App Initialized. Version %d.%d.%d.%d",
                TESTER_APP_MAJOR_VERSION,
                TESTER_APP_MINOR_VERSION, 
                TESTER_APP_REVISION, 
                TESTER_APP_MISSION_REV);
        
} /* End of TESTER_AppInit() */

void TESTER_SendCommand(CFE_SB_MsgPtr_t  MsgPtr)
{
    CFE_SB_MsgId_t msgid;
    uint16 cmd_code;



    printf("Pls input msg id:");
    scanf("%x",msgid);
    CFE_SB_InitMsg(MsgPtr, msgid, (uint16)(sizeof MsgPtr), TRUE);
    //CFE_SB_SetMsgId(MsgPtr,msgid);

    printf("Pls input cmd code:");
    scanf("%x",cmd_code);

    CFE_SB_SetCmdCode(MsgPtr,cmd_code);




}

