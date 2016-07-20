/*Includes*/
#include "su_app.h"
#include "su_app_msgids.h"
#include "su_app_perfids.h"
#include "su_app_events.h"
#include "su_app_msg.h"
#include "su_app_version.h"


su_hk_tlm_t    SU_HkTelemetryPkt;
CFE_SB_PipeId_t    SU_CommandPipe;
CFE_SB_MsgPtr_t    SUMsgPtr;

static CFE_EVS_BinFilter_t  SU_EventFilters[] =
    {  /* Event ID    mask */
        {SU_STARTUP_INF_EID,        0x0000}
    };

/* FIPEX commands */
uint8 ping[] = {0x7E, 0x00, 0x00, 0x00}; /* Ping Command */
uint8 rqhk[] = {0x7E, 0x20, 0x00, 0x20};  /* Request House Keeping */
uint8 rlp[] = {0x7E, 0x10, 0x00, 0x10};  /* Request Last Packet */
uint8 init[] = {0x7E, 0x01, 0x00, 0x01};  /* Initialize */    
uint8 suID[] = {0x7E, 0x04, 0x00, 0x04};   /* Science unit ID */
uint8 SU_SM[] = {0x7E, 0x0C, 0x00, 0x0C};  /* Measurement mode */
uint8 SU_STDBY[] = {0x7E, 0x0A, 0x00, 0x0A}; /* standby Mode */
uint8 SU_SC[] = {0x7E, 0x0B, 0x00, 0x0B};    /* Health check mode */
uint8 SU_DP[] = {0x7E, 0x21, 0x00, 0x21};    /* Request Science Data packet */

int32 SU_AppInit(void);

int32 Process_Cmd(CFE_SB_MsgPtr_t msg);

void Read_temp(void);


void SU_AppMain(void) {

    int32 test_counter = 0;

    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;
    
    CFE_ES_PerfLogEntry(SU_APP_PERF_ID);

    status = SU_AppInit();

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

    

    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {   

        CFE_ES_PerfLogExit(SU_APP_PERF_ID);

        if(test_counter<5){
            printf("\nSending the Ping Instruction\n");
            resp_flag = FALSE;
            write(fd, ping, sizeof ping);
            sleep(1);
			
            while(resp_flag != TRUE){
                sleep(1);
            }
    
            printf("\nSending the Init Instruction\n");
            resp_flag = FALSE;
            write(fd, init, sizeof init);
            sleep(1); 

            test_counter++;
        }

        status = CFE_SB_RcvMsg(&SUMsgPtr, SU_CommandPipe, 500);

        //Process_Cmd(SUMsgPtr);
        
        
        CFE_ES_PerfLogEntry(SU_APP_PERF_ID);
          
    }


    close(fd);
    printf("\nPort closed\n");

    RunStatus = CFE_ES_APP_EXIT;
    CFE_ES_ExitApp(RunStatus);
    
}

int32 SU_AppInit(void){

    int32 status = 0;

    resp_flag = FALSE;
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

    return status; //error indicator further edit needed
}


int32 Process_Cmd(CFE_SB_MsgPtr_t msg){
    CFE_SB_MsgId_t MessageID;
    uint16 CommandCode;

    MessageID = CFE_SB_GetMsgId(msg);
    switch (MessageID)
    {
        /*
        ** Housekeeping telemetry request...
        */
        case SU_APP_SEND_HK_MID:
            //SU_HousekeepingCmd(msg);
            break;

        /*
        ** SU ground commands...
        */
        case SU_APP_CMD_MID:

            CommandCode = CFE_SB_GetCmdCode(msg);
            switch (CommandCode)
            {
                case PING:
                    Send(ping);
                    break;

                case INIT:
                    Send(init);
                    break; 

                case OINK:
                    Send(ping);
                    Send(init);
                default:
                    CFE_EVS_SendEvent(SU_COMMAND_ERR_EID , CFE_EVS_ERROR,
                     "Invalid ground command code: ID = 0x%X, CC = %d",
                                      MessageID, CommandCode);
                    break;
            }
            break;

        default:

            CFE_EVS_SendEvent(SU_INVALID_MSGID_ERR_EID, CFE_EVS_ERROR,
                             "Invalid command pipe message ID: 0x%X",
                              MessageID);
            break;
    }

    return 0;

}

/*Write, execute a given script*/

int32 script_handler(char  *scriptname,  int  access){
    int32 script_fd;
    if(access == SET_ACTIVE)
    {
	    script_fd = open(scriptname, O_RDONLY);

    }
    else if(access == UPDATE)
    {
        script_fd = open(scriptname,O_WRONLY);
    }

}

int32 error_handler(){

}

int32 command_handler(){

}

int32 response_handler(){

}

