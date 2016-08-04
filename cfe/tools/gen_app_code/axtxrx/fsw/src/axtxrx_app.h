/*=======================================================================================
** File Name:  axtxrx_app.h
**
** Title:  Header File for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AXTXRX's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AXTXRX_APP_H_
#define _AXTXRX_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "axtxrx_platform_cfg.h"
#include "axtxrx_mission_cfg.h"
#include "axtxrx_private_ids.h"
#include "axtxrx_perfids.h"
#include "axtxrx_msgids.h"
#include "axtxrx_msg.h"

 
#include "axtxrx_iload_utils.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[AXTXRX_EVT_CNT];


    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    

    /* Task-related */
    uint32  uiRunStatus;
    
    /* ILoad table-related */
    CFE_TBL_Handle_t  ILoadTblHdl;
    AXTXRX_ILoadTblEntry_t*  ILoadTblPtr;
    

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in axtxrx/fsw/src/axtxrx_msg.h */
    AXTXRX_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} AXTXRX_AppData_t;

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
int32  AXTXRX_InitApp(void);
int32  AXTXRX_InitEvent(void);
int32  AXTXRX_InitPipe(void);

void  AXTXRX_AppMain(void);

void  AXTXRX_CleanupCallback(void);

int32  AXTXRX_RcvMsg(int32 iBlocking);

void  AXTXRX_ProcessNewData(void);
void  AXTXRX_ProcessNewCmds(void);
void  AXTXRX_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  AXTXRX_ReportHousekeeping(void);
void  AXTXRX_SendOutData(void);

boolean  AXTXRX_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _AXTXRX_APP_H_ */

/*=======================================================================================
** End of file axtxrx_app.h
**=====================================================================================*/
    