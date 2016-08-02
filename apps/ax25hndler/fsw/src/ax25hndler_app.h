/*=======================================================================================
** File Name:  ax25hndler_app.h
**
** Title:  Header File for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AX25HNDLER's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AX25HNDLER_APP_H_
#define _AX25HNDLER_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ax25hndler_platform_cfg.h"
#include "ax25hndler_mission_cfg.h"
#include "ax25hndler_private_ids.h"
#include "ax25hndler_perfids.h"
#include "ax25hndler_msgids.h"
#include "ax25hndler_msg.h"

 
#include "ax25hndler_iload_utils.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[AX25HNDLER_EVT_CNT];


    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    

    /* Task-related */
    uint32  uiRunStatus;
    
    /* ILoad table-related */
    CFE_TBL_Handle_t  ILoadTblHdl;
    AX25HNDLER_ILoadTblEntry_t*  ILoadTblPtr;
    

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in ax25hndler/fsw/src/ax25hndler_msg.h */
    AX25HNDLER_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} AX25HNDLER_AppData_t;

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/
int32  AX25HNDLER_InitApp(void);
int32  AX25HNDLER_InitEvent(void);
int32  AX25HNDLER_InitPipe(void);

void  AX25HNDLER_AppMain(void);

void  AX25HNDLER_CleanupCallback(void);

int32  AX25HNDLER_RcvMsg(int32 iBlocking);

void  AX25HNDLER_ProcessNewData(void);
void  AX25HNDLER_ProcessNewCmds(void);
void  AX25HNDLER_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  AX25HNDLER_ReportHousekeeping(void);
void  AX25HNDLER_SendOutData(void);

boolean  AX25HNDLER_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _AX25HNDLER_APP_H_ */

/*=======================================================================================
** End of file ax25hndler_app.h
**=====================================================================================*/
    