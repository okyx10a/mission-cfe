/*=======================================================================================
** File Name:  axtxrx_private_ids.h
**
** Title:  ID Header File for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This header file contains declarations and definitions of AXTXRX's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AXTXRX_PRIVATE_IDS_H_
#define _AXTXRX_PRIVATE_IDS_H_

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
**     AXTXRX_CMD_MID
**     AXTXRX_SEND_HK_MID
**     AXTXRX_WAKEUP_MID
**
** These command code Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_cmd_codes.h.
** Note that the header file is auto-generated from the CDD.
**     AXTXRX_NOOP_CC
**     AXTXRX_RESET_CC
**
** These message Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_tlm_ids.h.
** Note that the header file is auto-generated from the CDD.
**     AXTXRX_HK_TLM_MID
**     AXTXRX_OUT_DATA_MID
**
** These performance Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_perf_ids.h.
**     AXTXRX_MAIN_TASK_PERF_ID
**     AXTXRX_XXX_PERF_ID
*/

/* Event IDs */
#define AXTXRX_RESERVED_EID  0

#define AXTXRX_INF_EID        1
#define AXTXRX_INIT_INF_EID   2
#define AXTXRX_ILOAD_INF_EID  3
#define AXTXRX_CDS_INF_EID    4
#define AXTXRX_CMD_INF_EID    5

#define AXTXRX_ERR_EID         51
#define AXTXRX_INIT_ERR_EID    52
#define AXTXRX_ILOAD_ERR_EID   53
#define AXTXRX_CDS_ERR_EID     54
#define AXTXRX_CMD_ERR_EID     55
#define AXTXRX_PIPE_ERR_EID    56
#define AXTXRX_MSGID_ERR_EID   57
#define AXTXRX_MSGLEN_ERR_EID  58

#define AXTXRX_EVT_CNT  14

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

#endif /* _AXTXRX_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file axtxrx_private_ids.h
**=====================================================================================*/
    