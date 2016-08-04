/*=======================================================================================
** File Name:  axtxrx_app.c
**
** Title:  Function Definitions for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This source file contains all necessary function definitions to run AXTXRX
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

#include "axtxrx_platform_cfg.h"
#include "axtxrx_mission_cfg.h"
#include "axtxrx_app.h"

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
AXTXRX_AppData_t  g_AXTXRX_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: AXTXRX_InitEvent
**
** Purpose: To initialize and register event table for AXTXRX application
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
**    AXTXRX_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_AXTXRX_AppData.EventTbl
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
int32 AXTXRX_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_AXTXRX_AppData.EventTbl, 0x00, sizeof(g_AXTXRX_AppData.EventTbl));

    g_AXTXRX_AppData.EventTbl[0].EventID = AXTXRX_RESERVED_EID;
    g_AXTXRX_AppData.EventTbl[1].EventID = AXTXRX_INF_EID;
    g_AXTXRX_AppData.EventTbl[2].EventID = AXTXRX_INIT_INF_EID;
    g_AXTXRX_AppData.EventTbl[3].EventID = AXTXRX_ILOAD_INF_EID;
    g_AXTXRX_AppData.EventTbl[4].EventID = AXTXRX_CDS_INF_EID;
    g_AXTXRX_AppData.EventTbl[5].EventID = AXTXRX_CMD_INF_EID;

    g_AXTXRX_AppData.EventTbl[ 6].EventID = AXTXRX_ERR_EID;
    g_AXTXRX_AppData.EventTbl[ 7].EventID = AXTXRX_INIT_ERR_EID;
    g_AXTXRX_AppData.EventTbl[ 8].EventID = AXTXRX_ILOAD_ERR_EID;
    g_AXTXRX_AppData.EventTbl[ 9].EventID = AXTXRX_CDS_ERR_EID;
    g_AXTXRX_AppData.EventTbl[10].EventID = AXTXRX_CMD_ERR_EID;
    g_AXTXRX_AppData.EventTbl[11].EventID = AXTXRX_PIPE_ERR_EID;
    g_AXTXRX_AppData.EventTbl[12].EventID = AXTXRX_MSGID_ERR_EID;
    g_AXTXRX_AppData.EventTbl[13].EventID = AXTXRX_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_AXTXRX_AppData.EventTbl,
                               AXTXRX_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for AXTXRX application
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
**    AXTXRX_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_AXTXRX_AppData.usCmdPipeDepth
**    g_AXTXRX_AppData.cCmdPipeName
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
** History:  Date Written  AXTXRX
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 AXTXRX_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init command pipe */
    g_AXTXRX_AppData.usCmdPipeDepth = AXTXRX_CMD_PIPE_DEPTH ;
    memset((void*)g_AXTXRX_AppData.cCmdPipeName, '\0', sizeof(g_AXTXRX_AppData.cCmdPipeName));
    strncpy(g_AXTXRX_AppData.cCmdPipeName, "AXTXRX_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_AXTXRX_AppData.CmdPipeId,
                                 g_AXTXRX_AppData.usCmdPipeDepth,
                                 g_AXTXRX_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        CFE_SB_Subscribe(AXTXRX_CMD_MID, g_AXTXRX_AppData.CmdPipeId);
        CFE_SB_Subscribe(AXTXRX_SEND_HK_MID, g_AXTXRX_AppData.CmdPipeId);
    }
    else
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto AXTXRX_InitPipe_Exit_Tag;
    }

AXTXRX_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_InitData
**
** Purpose: To initialize global variables used by AXTXRX application
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
**    AXTXRX_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_AXTXRX_AppData.HkTlm
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
int32 AXTXRX_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init housekeeping packet */
    memset((void*)&g_AXTXRX_AppData.HkTlm, 0x00, sizeof(g_AXTXRX_AppData.HkTlm));
    CFE_SB_InitMsg(&g_AXTXRX_AppData.HkTlm,
                   AXTXRX_HK_TLM_MID, sizeof(g_AXTXRX_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_InitApp
**
** Purpose: To initialize all data local to and used by AXTXRX application
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
**    AXTXRX_InitEvent
**    AXTXRX_InitPipe
**    AXTXRX_InitData
**
** Called By:
**    AXTXRX_AppMain
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
int32 AXTXRX_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_AXTXRX_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to register the app (0x%08X)\n", iStatus);
        goto AXTXRX_InitApp_Exit_Tag;
    }

    if ((AXTXRX_InitEvent() != CFE_SUCCESS) || 
        (AXTXRX_InitPipe() != CFE_SUCCESS) || 
        (AXTXRX_InitData() != CFE_SUCCESS) ||
        (AXTXRX_InitILoadTbl() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto AXTXRX_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&AXTXRX_CleanupCallback);

AXTXRX_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(AXTXRX_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "AXTXRX - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("AXTXRX - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_CleanupCallback
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
void AXTXRX_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: AXTXRX_RcvMsg
**
** Purpose: To receive and process messages for AXTXRX application
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
**    AXTXRX_ProcessNewCmds
**    AXTXRX_ReportHousekeeping
**
** Called By:
**    AXTXRX_Main
**
** Global Inputs/Reads:
**    g_AXTXRX_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_AXTXRX_AppData.uiRunStatus
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
int32 AXTXRX_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_AXTXRX_AppData.CmdPipeId, iBlocking);
    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case AXTXRX_CMD_MID:
                AXTXRX_ProcessNewAppCmds(MsgPtr);

                /* TODO:  Add more code here to handle other things when app wakes up */

                
                break;

            /* TODO:  Add code here to handle other commands, if needed */

            case AXTXRX_SEND_HK_MID:
               AXTXRX_ReportHousekeeping();

               break;

            default:
                CFE_EVS_SendEvent(AXTXRX_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "AXTXRX - Recvd invalid SCH msgId (0x%08X)", MsgId);
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
        CFE_EVS_SendEvent(AXTXRX_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "AXTXRX: SB pipe read error (0x%08X), app will exit", iStatus);
        g_AXTXRX_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_ProcessNewAppCmds
**
** Purpose: To process command messages targeting AXTXRX application
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
**    AXTXRX_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_AXTXRX_AppData.HkTlm.usCmdCnt
**    g_AXTXRX_AppData.HkTlm.usCmdErrCnt
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
void AXTXRX_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case AXTXRX_NOOP_CC:
                g_AXTXRX_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(AXTXRX_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "AXTXRX - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case AXTXRX_RESET_CC:
                g_AXTXRX_AppData.HkTlm.usCmdCnt = 0;
                g_AXTXRX_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(AXTXRX_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "AXTXRX - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the AXTXRX commands here */

            default:
                g_AXTXRX_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(AXTXRX_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "AXTXRX - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: AXTXRX_ReportHousekeeping
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
**    AXTXRX_ProcessNewCmds
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
void AXTXRX_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_AXTXRX_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_AXTXRX_AppData.HkTlm);
}
    
/*=====================================================================================
** Name: AXTXRX_VerifyCmdLength
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
**    AXTXRX_ProcessNewCmds
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
boolean AXTXRX_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            CFE_EVS_SendEvent(AXTXRX_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "AXTXRX - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_AXTXRX_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: AXTXRX_AppMain
**
** Purpose: To define AXTXRX application's entry point and main process loop
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
**    AXTXRX_InitApp
**    AXTXRX_RcvMsg
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
void AXTXRX_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(AXTXRX_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (AXTXRX_InitApp() != CFE_SUCCESS)
    {
        g_AXTXRX_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(AXTXRX_MAIN_TASK_PERF_ID);

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_AXTXRX_AppData.uiRunStatus) == TRUE)
    {
        AXTXRX_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Exit the application */
    CFE_ES_ExitApp(g_AXTXRX_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file axtxrx_app.c
**=====================================================================================*/
    