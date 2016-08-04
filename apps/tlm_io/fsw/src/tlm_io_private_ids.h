/*=======================================================================================
** File Name:  tlm_io_private_ids.h
**
** Title:  ID Header File for TLM_IO Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This header file contains declarations and definitions of TLM_IO's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _TLM_IO_PRIVATE_IDS_H_
#define _TLM_IO_PRIVATE_IDS_H_

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
** These message Ids are defined in $(CFS_APP_SRC)/inc/YUsend-QB50_cmd_ids.h.
** Note that the header file is auto-generated from the Command & Data Dictionary (CDD).
**     TLM_IO_CMD_MID
**     TLM_IO_SEND_HK_MID
**     TLM_IO_WAKEUP_MID
**
** These command code Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_cmd_codes.h.
** Note that the header file is auto-generated from the CDD.
**     TLM_IO_NOOP_CC
**     TLM_IO_RESET_CC
**
** These message Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_tlm_ids.h.
** Note that the header file is auto-generated from the CDD.
**     TLM_IO_HK_TLM_MID
**     TLM_IO_OUT_DATA_MID
**
** These performance Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_perf_ids.h.
**     TLM_IO_MAIN_TASK_PERF_ID
**     TLM_IO_XXX_PERF_ID
*/

/* Event IDs */
#define TLM_IO_RESERVED_EID  0

#define TLM_IO_INF_EID        1
#define TLM_IO_INIT_INF_EID   2
#define TLM_IO_ILOAD_INF_EID  3
#define TLM_IO_CDS_INF_EID    4
#define TLM_IO_CMD_INF_EID    5

#define TLM_IO_ERR_EID         51
#define TLM_IO_INIT_ERR_EID    52
#define TLM_IO_ILOAD_ERR_EID   53
#define TLM_IO_CDS_ERR_EID     54
#define TLM_IO_CMD_ERR_EID     55
#define TLM_IO_PIPE_ERR_EID    56
#define TLM_IO_MSGID_ERR_EID   57
#define TLM_IO_MSGLEN_ERR_EID  58

#define TLM_IO_EVT_CNT  14

/*
** Local Structure Declarations
*/

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

#endif /* _TLM_IO_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file tlm_io_private_ids.h
**=====================================================================================*/
    