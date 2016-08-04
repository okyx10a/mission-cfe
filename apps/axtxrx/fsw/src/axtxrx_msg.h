/*=======================================================================================
** File Name:  axtxrx_msg.h
**
** Title:  Message Definition Header File for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AXTXRX's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AXTXRX_MSG_H_
#define _AXTXRX_MSG_H_

/*
** Pragmas
*/

/*
** Include Files
*/

 


/*
** Local Defines
*/

/*
** AXTXRX command codes
*/
#define AXTXRX_NOOP_CC                 0
#define AXTXRX_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} AXTXRX_HkTlm_t;


#endif /* _AXTXRX_MSG_H_ */

/*=======================================================================================
** End of file axtxrx_msg.h
**=====================================================================================*/
    