/*=======================================================================================
** File Name:  tlm_io_msg.h
**
** Title:  Message Definition Header File for TLM_IO Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define TLM_IO's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _TLM_IO_MSG_H_
#define _TLM_IO_MSG_H_

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
** TLM_IO command codes
*/
#define TLM_IO_NOOP_CC                 0
#define TLM_IO_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} TLM_IO_HkTlm_t;


#endif /* _TLM_IO_MSG_H_ */

/*=======================================================================================
** End of file tlm_io_msg.h
**=====================================================================================*/
    