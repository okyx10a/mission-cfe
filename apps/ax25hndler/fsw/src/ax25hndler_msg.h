/*=======================================================================================
** File Name:  ax25hndler_msg.h
**
** Title:  Message Definition Header File for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AX25HNDLER's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AX25HNDLER_MSG_H_
#define _AX25HNDLER_MSG_H_

/*
** Pragmas
*/

/*
** Include Files
*/

 
#include "ax25hndler_iload_utils.h"

/*
** Local Defines
*/

/*
** AX25HNDLER command codes
*/
#define AX25HNDLER_NOOP_CC                 0
#define AX25HNDLER_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} AX25HNDLER_HkTlm_t;


#endif /* _AX25HNDLER_MSG_H_ */

/*=======================================================================================
** End of file ax25hndler_msg.h
**=====================================================================================*/
    