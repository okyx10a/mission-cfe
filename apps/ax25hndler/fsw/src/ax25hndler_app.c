/*=======================================================================================
** File Name:  ax25hndler_app.c
**
** Title:  Function Definitions for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This source file contains all necessary function definitions to run AX25HNDLER
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

#include "ax25hndler_platform_cfg.h"
#include "ax25hndler_mission_cfg.h"
#include "ax25hndler_app.h"

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
AX25HNDLER_AppData_t  g_AX25HNDLER_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: AX25HNDLER_InitEvent
**
** Purpose: To initialize and register event table for AX25HNDLER application
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
**    AX25HNDLER_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_AX25HNDLER_AppData.EventTbl
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
int32 AX25HNDLER_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_AX25HNDLER_AppData.EventTbl, 0x00, sizeof(g_AX25HNDLER_AppData.EventTbl));

    g_AX25HNDLER_AppData.EventTbl[0].EventID = AX25HNDLER_RESERVED_EID;
    g_AX25HNDLER_AppData.EventTbl[1].EventID = AX25HNDLER_INF_EID;
    g_AX25HNDLER_AppData.EventTbl[2].EventID = AX25HNDLER_INIT_INF_EID;
    g_AX25HNDLER_AppData.EventTbl[3].EventID = AX25HNDLER_ILOAD_INF_EID;
    g_AX25HNDLER_AppData.EventTbl[4].EventID = AX25HNDLER_CDS_INF_EID;
    g_AX25HNDLER_AppData.EventTbl[5].EventID = AX25HNDLER_CMD_INF_EID;

    g_AX25HNDLER_AppData.EventTbl[ 6].EventID = AX25HNDLER_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[ 7].EventID = AX25HNDLER_INIT_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[ 8].EventID = AX25HNDLER_ILOAD_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[ 9].EventID = AX25HNDLER_CDS_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[10].EventID = AX25HNDLER_CMD_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[11].EventID = AX25HNDLER_PIPE_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[12].EventID = AX25HNDLER_MSGID_ERR_EID;
    g_AX25HNDLER_AppData.EventTbl[13].EventID = AX25HNDLER_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_AX25HNDLER_AppData.EventTbl,
                               AX25HNDLER_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for AX25HNDLER application
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
**    AX25HNDLER_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_AX25HNDLER_AppData.usCmdPipeDepth
**    g_AX25HNDLER_AppData.cCmdPipeName
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
** History:  Date Written  AX25HNDLER
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 AX25HNDLER_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init command pipe */
    g_AX25HNDLER_AppData.usCmdPipeDepth = AX25HNDLER_CMD_PIPE_DEPTH ;
    memset((void*)g_AX25HNDLER_AppData.cCmdPipeName, '\0', sizeof(g_AX25HNDLER_AppData.cCmdPipeName));
    strncpy(g_AX25HNDLER_AppData.cCmdPipeName, "AX25HNDLER_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_AX25HNDLER_AppData.CmdPipeId,
                                 g_AX25HNDLER_AppData.usCmdPipeDepth,
                                 g_AX25HNDLER_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        CFE_SB_Subscribe(AX25HNDLER_CMD_MID, g_AX25HNDLER_AppData.CmdPipeId);
        CFE_SB_Subscribe(AX25HNDLER_SEND_HK_MID, g_AX25HNDLER_AppData.CmdPipeId);
    }
    else
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitPipe_Exit_Tag;
    }

AX25HNDLER_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_InitData
**
** Purpose: To initialize global variables used by AX25HNDLER application
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
**    AX25HNDLER_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_AX25HNDLER_AppData.HkTlm
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
int32 AX25HNDLER_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init housekeeping packet */
    memset((void*)&g_AX25HNDLER_AppData.HkTlm, 0x00, sizeof(g_AX25HNDLER_AppData.HkTlm));
    CFE_SB_InitMsg(&g_AX25HNDLER_AppData.HkTlm,
                   AX25HNDLER_HK_TLM_MID, sizeof(g_AX25HNDLER_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_InitApp
**
** Purpose: To initialize all data local to and used by AX25HNDLER application
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
**    AX25HNDLER_InitEvent
**    AX25HNDLER_InitPipe
**    AX25HNDLER_InitData
**
** Called By:
**    AX25HNDLER_AppMain
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
int32 AX25HNDLER_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_AX25HNDLER_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to register the app (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitApp_Exit_Tag;
    }

    if ((AX25HNDLER_InitEvent() != CFE_SUCCESS) || 
        (AX25HNDLER_InitPipe() != CFE_SUCCESS) || 
        (AX25HNDLER_InitData() != CFE_SUCCESS) ||
        (AX25HNDLER_InitILoadTbl() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto AX25HNDLER_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&AX25HNDLER_CleanupCallback);

AX25HNDLER_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(AX25HNDLER_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "AX25HNDLER - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_CleanupCallback
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
void AX25HNDLER_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: AX25HNDLER_RcvMsg
**
** Purpose: To receive and process messages for AX25HNDLER application
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
**    AX25HNDLER_ProcessNewCmds
**    AX25HNDLER_ReportHousekeeping
**
** Called By:
**    AX25HNDLER_Main
**
** Global Inputs/Reads:
**    g_AX25HNDLER_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_AX25HNDLER_AppData.uiRunStatus
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
int32 AX25HNDLER_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_AX25HNDLER_AppData.CmdPipeId, iBlocking);
    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case AX25HNDLER_CMD_MID:
                AX25HNDLER_ProcessNewAppCmds(MsgPtr);

                /* TODO:  Add more code here to handle other things when app wakes up */

                
                break;

            /* TODO:  Add code here to handle other commands, if needed */

            case AX25HNDLER_SEND_HK_MID:
               AX25HNDLER_ReportHousekeeping();

               break;

            default:
                CFE_EVS_SendEvent(AX25HNDLER_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "AX25HNDLER - Recvd invalid SCH msgId (0x%08X)", MsgId);
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
        CFE_EVS_SendEvent(AX25HNDLER_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "AX25HNDLER: SB pipe read error (0x%08X), app will exit", iStatus);
        g_AX25HNDLER_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_ProcessNewAppCmds
**
** Purpose: To process command messages targeting AX25HNDLER application
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
**    AX25HNDLER_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_AX25HNDLER_AppData.HkTlm.usCmdCnt
**    g_AX25HNDLER_AppData.HkTlm.usCmdErrCnt
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
void AX25HNDLER_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case AX25HNDLER_NOOP_CC:
                g_AX25HNDLER_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(AX25HNDLER_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "AX25HNDLER - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case AX25HNDLER_RESET_CC:
                g_AX25HNDLER_AppData.HkTlm.usCmdCnt = 0;
                g_AX25HNDLER_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(AX25HNDLER_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "AX25HNDLER - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the AX25HNDLER commands here */

            default:
                g_AX25HNDLER_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(AX25HNDLER_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "AX25HNDLER - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: AX25HNDLER_ReportHousekeeping
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
**    AX25HNDLER_ProcessNewCmds
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
void AX25HNDLER_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_AX25HNDLER_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_AX25HNDLER_AppData.HkTlm);
}
    
/*=====================================================================================
** Name: AX25HNDLER_VerifyCmdLength
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
**    AX25HNDLER_ProcessNewCmds
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
boolean AX25HNDLER_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            CFE_EVS_SendEvent(AX25HNDLER_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "AX25HNDLER - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_AX25HNDLER_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: AX25HNDLER_AppMain
**
** Purpose: To define AX25HNDLER application's entry point and main process loop
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
**    AX25HNDLER_InitApp
**    AX25HNDLER_RcvMsg
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
void AX25HNDLER_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(AX25HNDLER_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (AX25HNDLER_InitApp() != CFE_SUCCESS)
    {
        g_AX25HNDLER_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(AX25HNDLER_MAIN_TASK_PERF_ID);

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_AX25HNDLER_AppData.uiRunStatus) == TRUE)
    {
        AX25HNDLER_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Exit the application */
    CFE_ES_ExitApp(g_AX25HNDLER_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file ax25hndler_app.c
**=====================================================================================*/
    