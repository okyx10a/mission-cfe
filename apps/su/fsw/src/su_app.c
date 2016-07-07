/*Includes*/
#include "su_app.h"
#include "su_app_msgids.h"
#include "su_app_perfids.h"
#include "su_app_events.h"
#include "su_app_msg.h"
#include "su_app_versions.h"

su_hk_tlm_t    SU_HkTelemetryPkt;
CFE_SB_PipeId_t    SU_CommandPipe;
CFE_SB_MsgPtr_t    SUMsgPtr;

static CFE_EVS_BinFilter_t  SU_EventFilters[] =
    {  /* Event ID    mask */
        {SU_STARTUP_INF_EID,        0x0000}
    }

int SU_AppMain(void) {

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

    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(SU_APP_PERF_ID);

    SU_AppInit();

    /*
    ** SU Runloop
    */
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
    sleep(100);
        
    CFE_ES_ExitApp(RunStatus);
      
}

int SU_AppInit(void){


    CFE_ES_RegisterApp();

    /*
    ** Register the events
    */ 

    CFE_EVS_Register(SU_EventFilters,
                     sizeof(SU_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    CFE_SB_CreatePipe(&SU_CommandPipe, SU_PIPE_DEPTH,"SU_CMD_PIPE");
    CFE_SB_Subscribe(SU_APP_CMD_MID, SU_CommandPipe);     //su_app_msgids.h
    CFE_SB_Subscribe(SU_APP_SEND_HK_MID, SU_CommandPipe); //su_app_msgids.h

    //SU_ResetCounters();

    CFE_SB_InitMsg(&SU_HkTelemetryPkt,        //su_app_msg.h
                   SU_APP_HK_TLM_MID,         //su_app_msgids.h
                   SU_APP_HK_TLM_LNGTH, TRUE);//su_app_msg.h

    CFE_EVS_SendEvent (SU_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "SU App Initialized. Version %d.%d.%d.%d",
                SU_APP_MAJOR_VERSION,
                SU_APP_MINOR_VERSION, 
                SU_APP_REVISION, 
                SU_APP_MISSION_REV);
                

}