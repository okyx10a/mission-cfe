/*=======================================================================================
** File Name:  YUSEND-QB50_axtxrx_types.h
**
** Title:  Command/Telemetry Data Structure Header File for AXTXRX application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This header file contains definitions of command & telemetry data structures
**           for AXTXRX applications built for YUSEND-QB50 mission. 
**
**=====================================================================================*/
    
#ifndef _YUSEND-QB50_AXTXRX_TYPES_H_
#define _YUSEND-QB50_AXTXRX_TYPES_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} AXTXRX_NoArgCmd_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint16  usCmdCnt;
    uint16  usCmdErrCnt;
} AXTXRX_HkTlm_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} AXTXRX_OutData_t;

#endif /* _YUSEND-QB50_AXTXRX_TYPES_H_ */

/*=======================================================================================
** End of file YUSEND-QB50_axtxrx_types.h
**=====================================================================================*/
    