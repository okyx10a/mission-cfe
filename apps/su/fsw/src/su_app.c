
/*Includes*/
#include "su_app.h"




const uint8         SCRIPT_END[4] = {0x7E, 0xFF, 0x01, 0xFE};

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

int32 Process_Cmd(CFE_SB_MsgPtr_t *msg);



void SU_AppMain(void) {

    int32 test_counter = 0;

    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;
    int s,b,t,p,n;
    s=b=t=p=n=0;
    
    CFE_ES_PerfLogEntry(SU_APP_PERF_ID);

    status = SU_AppInit();

    /*
    ** SU Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {   

        CFE_ES_PerfLogExit(SU_APP_PERF_ID);

        //software bus funtion testing
        
        status = CFE_SB_RcvMsg(&app_data.SUMsgPtr, app_data.SU_CommandPipe, 500);
        switch(status){
            case CFE_SUCCESS:
            b=t=p=n=0;
            if(!s){   
                Process_Msg(app_data.SUMsgPtr);
                s = 1;
            }
            break;
            case CFE_SB_BAD_ARGUMENT:
            s=t=p=n=0;
            if(!b){
                printf("SU: CFE_SB_BAD_ARGUMENT \n");
                b = 1;
            }
            break;
            case CFE_SB_TIME_OUT:
            s=b=p=n=0;
            if(!t){
                printf("SU: CFE_SB_TIME_OUT \n");
                t = 1;
            }
            break;
            case CFE_SB_PIPE_RD_ERR:
            s=b=t=n=0;
            if(!p){
                printf("SU: CFE_SB_PIPE_RD_ERR \n");
                p = 1;
            }
            break;
            case CFE_SB_NO_MESSAGE:
            s=b=t=p=0;
            if(!n){
                printf("SU: CFE_SB_NO_MESSAGE \n");
                n = 1;
            }
            break;
            default:
            printf("SU: Unknown error \n");
            break;
        } 

        
        
        
        CFE_ES_PerfLogEntry(SU_APP_PERF_ID);
          
    }


    close(app_data.fd);
    printf("\nPort closed\n");

    RunStatus = CFE_ES_APP_EXIT;
    CFE_ES_ExitApp(RunStatus);
    
}

int32 SU_AppInit(void){

    int32 status = 0;

    app_data.resp_flag = FALSE;
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
    CFE_SB_CreatePipe(&app_data.SU_CommandPipe, SU_PIPE_DEPTH,"SU_CMD_PIPE");
    CFE_SB_Subscribe(SU_APP_CMD_MID, app_data.SU_CommandPipe);     
    CFE_SB_Subscribe(SU_APP_SEND_HK_MID, app_data.SU_CommandPipe); 

    //SU_ResetCounters();

    CFE_SB_InitMsg(&app_data.SU_HkTelemetryPkt,       
                   SU_APP_HK_TLM_MID,         
                   SU_APP_HK_TLM_LNGTH, TRUE);

    app_data.fd = Open_Port();
    Set_Attribute();

    CFE_EVS_SendEvent (SU_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "SU App Initialized. Version %d.%d.%d.%d",
                SU_APP_MAJOR_VERSION,
                SU_APP_MINOR_VERSION, 
                SU_APP_REVISION, 
                SU_APP_MISSION_REV);

    return status; //error indicator further edit needed
}


int32 Process_Msg(CFE_SB_MsgPtr_t *msg){
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
            
            /*switch (CommandCode)
            {
                case PING:
                    printf("executing ping\n");
                    Send(ping);
                    
                    break;

                case INIT:
                    printf("executing init\n");
                    Send(init);

                    break; 

                case OINK:
                    printf("executing oink\n");
                    Send(ping);

                    while(app_data.resp_flag != TRUE){
                        sleep(1);
                    }

                    Send(init);
                    break;

                default:
                    CFE_EVS_SendEvent(SU_COMMAND_ERR_EID , CFE_EVS_ERROR,
                     "Invalid ground command code: ID = 0x%X, CC = %d",
                                      MessageID, CommandCode);
                    break;
            }*/

            switch (CommandCode)
            {
                case SET_ACTIVE:
                    printf("executing SET_ACTIVE\n");

                    script_handler("../scripts/script1",SET_ACTIVE);

                    break;

                case UPDATE:
                    printf("executing UPDATE\n");
                    break; 


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

    return CFE_SUCCESS;

}

/*Write, execute a given script*/

int32 script_handler(char  *scriptname,  int  access){
    int32       script_fd,status;
    uint8       *buffer,*release;
    uint8       cmd_len;
    uint8       i;
    if(access == SET_ACTIVE)
    {
	    script_fd = open(scriptname, O_RDONLY);

        //Load in the whole script
        if(read(script_fd,&app_data.su_script.LEN,sizeof(app_data.su_script.LEN))==0){
            release = malloc((app_data.su_script.LEN+1)*sizeof(uint8));
            buffer = release;
            read(script_fd,buffer,(app_data.su_script.LEN+1)*sizeof(uint8));
        }


        //Fill in local data fields

        buffer++;

        //STARTTIME
        memcpy(&app_data.su_script.STARTTIME,buffer,sizeof(app_data.su_script.STARTTIME));

        buffer = buffer + sizeof(app_data.su_script.STARTTIME)/sizeof(uint8);

        //REPEATTIME
        memcpy(&app_data.su_script.REPEATTIME,buffer,sizeof(app_data.su_script.REPEATTIME));

        buffer = buffer + sizeof(app_data.su_script.REPEATTIME)/sizeof(uint8);

        //CMD_CNT
        memcpy(&app_data.su_script.CMD_CNT,buffer,sizeof(app_data.su_script.CMD_CNT));

        buffer = buffer + sizeof(app_data.su_script.CMD_CNT)/sizeof(uint8);

        //Cmds and delays
        for(i = 0; i<app_data.su_script.CMD_CNT; i++){

            if(buffer[0]!=0x7E){
                CFE_EVS_SendEvent(SU_SCRIPT_ERR_EID, CFE_EVS_ERROR,
                                    "Invalid script encoding.\n"); 
            }
            else if(memcmp(buffer,&SCRIPT_END,sizeof(SCRIPT_END))){
                memcpy(app_data.su_script.CMD[i],buffer,sizeof(SCRIPT_END));
            }
            else{
                cmd_len = buffer[2];

                memcpy(app_data.su_script.CMD[i],buffer,(cmd_len+4)*sizeof(uint8));

                buffer = buffer + (cmd_len+4);


                memcpy(app_data.su_script.DELAY[i], buffer, sizeof app_data.su_script.DELAY);

                buffer = buffer + sizeof app_data.su_script.DELAY/sizeof(uint8);  
            }
        }

        status = command_handler();






    }
    else if(access == UPDATE)
    {
        script_fd = open(scriptname,O_WRONLY);
    }
    return CFE_SUCCESS;
}

int32 error_handler(){

}

int32 command_handler(){
    int i = 0;
    do{
        send(app_data.su_script.CMD[i]);
        i++;
    }while(app_data.su_script.CMD[i] != SCRIPT_END);
    return CFE_SUCCESS;
}

int32 response_handler(){

}

