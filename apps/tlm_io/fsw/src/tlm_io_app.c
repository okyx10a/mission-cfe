/*=======================================================================================
** File Name:  tlm_io_app.c
**
** Title:  Function Definitions for TLM_IO Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This source file contains all necessary function definitions to run TLM_IO
**           application.
**
** Functions Defined:
**    Function X - Brief purpose of function X
**    Function Y - Brief purpose of function Y
**    Function Z - Brief purpose of function Z
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include <string.h>

#include "cfe.h"

#include "tlm_io_platform_cfg.h"
#include "tlm_io_mission_cfg.h"
#include "tlm_io_app.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/
TLM_IO_AppData_t  g_TLM_IO_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: TLM_IO_InitEvent
**
** Purpose: To initialize and register event table for TLM_IO application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_EVS_Register
**    CFE_ES_WriteToSysLog
**
** Called By:
**    TLM_IO_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_TLM_IO_AppData.EventTbl
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 TLM_IO_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_TLM_IO_AppData.EventTbl, 0x00, sizeof(g_TLM_IO_AppData.EventTbl));

    g_TLM_IO_AppData.EventTbl[0].EventID = TLM_IO_RESERVED_EID;
    g_TLM_IO_AppData.EventTbl[1].EventID = TLM_IO_INF_EID;
    g_TLM_IO_AppData.EventTbl[2].EventID = TLM_IO_INIT_INF_EID;
    g_TLM_IO_AppData.EventTbl[3].EventID = TLM_IO_ILOAD_INF_EID;
    g_TLM_IO_AppData.EventTbl[4].EventID = TLM_IO_CDS_INF_EID;
    g_TLM_IO_AppData.EventTbl[5].EventID = TLM_IO_CMD_INF_EID;

    g_TLM_IO_AppData.EventTbl[ 6].EventID = TLM_IO_ERR_EID;
    g_TLM_IO_AppData.EventTbl[ 7].EventID = TLM_IO_INIT_ERR_EID;
    g_TLM_IO_AppData.EventTbl[ 8].EventID = TLM_IO_ILOAD_ERR_EID;
    g_TLM_IO_AppData.EventTbl[ 9].EventID = TLM_IO_CDS_ERR_EID;
    g_TLM_IO_AppData.EventTbl[10].EventID = TLM_IO_CMD_ERR_EID;
    g_TLM_IO_AppData.EventTbl[11].EventID = TLM_IO_PIPE_ERR_EID;
    g_TLM_IO_AppData.EventTbl[12].EventID = TLM_IO_MSGID_ERR_EID;
    g_TLM_IO_AppData.EventTbl[13].EventID = TLM_IO_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_TLM_IO_AppData.EventTbl,
                               TLM_IO_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("TLM_IO - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: TLM_IO_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for TLM_IO application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_CreatePipe
**    CFE_SB_Subscribe
**    CFE_ES_WriteToSysLog
**
** Called By:
**    TLM_IO_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_TLM_IO_AppData.usCmdPipeDepth
**    g_TLM_IO_AppData.cCmdPipeName
**    g_YUsend Lab_AppData.CmdPipeId
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  2016-08-02 
**
** History:  Date Written  TLM_IO
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 TLM_IO_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init command pipe */
    g_TLM_IO_AppData.usCmdPipeDepth = TLM_IO_CMD_PIPE_DEPTH ;
    memset((void*)g_TLM_IO_AppData.cCmdPipeName, '\0', sizeof(g_TLM_IO_AppData.cCmdPipeName));
    strncpy(g_TLM_IO_AppData.cCmdPipeName, "TLM_IO_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_TLM_IO_AppData.CmdPipeId,
                                 g_TLM_IO_AppData.usCmdPipeDepth,
                                 g_TLM_IO_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        CFE_SB_Subscribe(TLM_IO_CMD_MID, g_TLM_IO_AppData.CmdPipeId);
        CFE_SB_Subscribe(TLM_IO_SEND_HK_MID, g_TLM_IO_AppData.CmdPipeId);
    }
    else
    {
        CFE_ES_WriteToSysLog("TLM_IO - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto TLM_IO_InitPipe_Exit_Tag;
    }

TLM_IO_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: TLM_IO_InitData
**
** Purpose: To initialize global variables used by TLM_IO application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_InitMsg
**
** Called By:
**    TLM_IO_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_TLM_IO_AppData.HkTlm
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 TLM_IO_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init housekeeping packet */
    memset((void*)&g_TLM_IO_AppData.HkTlm, 0x00, sizeof(g_TLM_IO_AppData.HkTlm));
    CFE_SB_InitMsg(&g_TLM_IO_AppData.HkTlm,
                   TLM_IO_HK_TLM_MID, sizeof(g_TLM_IO_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: TLM_IO_InitApp
**
** Purpose: To initialize all data local to and used by TLM_IO application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_WriteToSysLog
**    CFE_EVS_SendEvent
**    OS_TaskInstallDeleteHandler
**    TLM_IO_InitEvent
**    TLM_IO_InitPipe
**    TLM_IO_InitData
**
** Called By:
**    TLM_IO_AppMain
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 TLM_IO_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_TLM_IO_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("TLM_IO - Failed to register the app (0x%08X)\n", iStatus);
        goto TLM_IO_InitApp_Exit_Tag;
    }

    if ((TLM_IO_InitEvent() != CFE_SUCCESS) || 
        (TLM_IO_InitPipe() != CFE_SUCCESS) || 
        (TLM_IO_InitData() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto TLM_IO_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&TLM_IO_CleanupCallback);

TLM_IO_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(TLM_IO_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "TLM_IO - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("TLM_IO - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: TLM_IO_CleanupCallback
**
** Purpose: To handle any neccesary cleanup prior to application exit
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void TLM_IO_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: TLM_IO_RcvMsg
**
** Purpose: To receive and process messages for TLM_IO application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization 
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    TLM_IO_ProcessNewCmds
**    TLM_IO_ReportHousekeeping
**
** Called By:
**    TLM_IO_Main
**
** Global Inputs/Reads:
**    g_TLM_IO_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_TLM_IO_AppData.uiRunStatus
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 TLM_IO_RcvMsg(int32 iBlocking)
{
    int32           iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr = NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_TLM_IO_AppData.CmdPipeId, iBlocking);
    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case TLM_IO_CMD_MID:
                TLM_IO_ProcessNewAppCmds(MsgPtr);
                printf("The message has arrived.\n"); 
                printf("Meow~\n");
                printf("The message ID was %x", MsgId);
                break;

            /* TODO:  Add code here to handle other commands, if needed */

            case TLM_IO_SEND_HK_MID:
               TLM_IO_ReportHousekeeping();

               break;

            default:
                CFE_EVS_SendEvent(TLM_IO_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "TLM_IO - Recvd invalid SCH msgId (0x%08X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, you can do something here, or nothing */
    }
    else
    {
        /* This is an example of exiting on an error.
        ** Note that a SB read error is not always going to result in an app quitting.
        */
        CFE_EVS_SendEvent(TLM_IO_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "TLM_IO: SB pipe read error (0x%08X), app will exit", iStatus);
        g_TLM_IO_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: TLM_IO_ProcessNewAppCmds
**
** Purpose: To process command messages targeting TLM_IO application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    TLM_IO_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_TLM_IO_AppData.HkTlm.usCmdCnt
**    g_TLM_IO_AppData.HkTlm.usCmdErrCnt
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void TLM_IO_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case TLM_IO_NOOP_CC:
                g_TLM_IO_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(TLM_IO_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "TLM_IO - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case TLM_IO_RESET_CC:
                g_TLM_IO_AppData.HkTlm.usCmdCnt = 0;
                g_TLM_IO_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(TLM_IO_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "TLM_IO - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the TLM_IO commands here */

            default:
                g_TLM_IO_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(TLM_IO_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "TLM_IO - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: TLM_IO_ReportHousekeeping
**
** Purpose: To send housekeeping message
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TLM_IO_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  GSFC, YUsend Lab
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void TLM_IO_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_TLM_IO_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_TLM_IO_AppData.HkTlm);
}
    
/*=====================================================================================
** Name: TLM_IO_VerifyCmdLength
**
** Purpose: To verify command length for a particular command message
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr      - command message pointer
**    uint16         usExpLength - expected command length
**
** Returns:
**    boolean bResult - result of verification
**
** Routines Called:
**    TBD
**
** Called By:
**    TLM_IO_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean TLM_IO_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult=FALSE;
    uint16  usMsgLen=0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            CFE_EVS_SendEvent(TLM_IO_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "TLM_IO - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_TLM_IO_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: TLM_IO_AppMain
**
** Purpose: To define TLM_IO application's entry point and main process loop
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_RunLoop
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CFE_ES_ExitApp
**    TLM_IO_InitApp
**    TLM_IO_RcvMsg
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void TLM_IO_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(TLM_IO_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (TLM_IO_InitApp() != CFE_SUCCESS)
    {
        g_TLM_IO_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(TLM_IO_MAIN_TASK_PERF_ID);

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_TLM_IO_AppData.uiRunStatus) == TRUE)
    {
        TLM_IO_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Exit the application */
    CFE_ES_ExitApp(g_TLM_IO_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file tlm_io_app.c
**=====================================================================================*/
    