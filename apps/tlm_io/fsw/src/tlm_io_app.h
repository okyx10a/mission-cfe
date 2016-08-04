/*=======================================================================================
** File Name:  tlm_io_app.h
**
** Title:  Header File for TLM_IO Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define TLM_IO's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _TLM_IO_APP_H_
#define _TLM_IO_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "tlm_io_platform_cfg.h"
#include "tlm_io_mission_cfg.h"
#include "tlm_io_private_ids.h"
#include "tlm_io_perfids.h"
#include "tlm_io_msgids.h"
#include "tlm_io_msg.h"

 


/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[TLM_IO_EVT_CNT];


    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    

    /* Task-related */
    uint32  uiRunStatus;
    
 
    

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in tlm_io/fsw/src/tlm_io_msg.h */
    TLM_IO_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} TLM_IO_AppData_t;

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
int32  TLM_IO_InitApp(void);
int32  TLM_IO_InitEvent(void);
int32  TLM_IO_InitPipe(void);

void  TLM_IO_AppMain(void);

void  TLM_IO_CleanupCallback(void);

int32  TLM_IO_RcvMsg(int32 iBlocking);

void  TLM_IO_ProcessNewData(void);
void  TLM_IO_ProcessNewCmds(void);
void  TLM_IO_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  TLM_IO_ReportHousekeeping(void);
void  TLM_IO_SendOutData(void);

boolean  TLM_IO_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _TLM_IO_APP_H_ */

/*=======================================================================================
** End of file tlm_io_app.h
**=====================================================================================*/
    