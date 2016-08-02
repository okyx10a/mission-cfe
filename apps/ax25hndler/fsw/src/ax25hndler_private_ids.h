/*=======================================================================================
** File Name:  ax25hndler_private_ids.h
**
** Title:  ID Header File for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This header file contains declarations and definitions of AX25HNDLER's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AX25HNDLER_PRIVATE_IDS_H_
#define _AX25HNDLER_PRIVATE_IDS_H_

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
**     AX25HNDLER_CMD_MID
**     AX25HNDLER_SEND_HK_MID
**     AX25HNDLER_WAKEUP_MID
**
** These command code Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_cmd_codes.h.
** Note that the header file is auto-generated from the CDD.
**     AX25HNDLER_NOOP_CC
**     AX25HNDLER_RESET_CC
**
** These message Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_tlm_ids.h.
** Note that the header file is auto-generated from the CDD.
**     AX25HNDLER_HK_TLM_MID
**     AX25HNDLER_OUT_DATA_MID
**
** These performance Ids are defined in $(CFS_APP_SRC)/inc/YUSEND-QB50_perf_ids.h.
**     AX25HNDLER_MAIN_TASK_PERF_ID
**     AX25HNDLER_XXX_PERF_ID
*/

/* Event IDs */
#define AX25HNDLER_RESERVED_EID  0

#define AX25HNDLER_INF_EID        1
#define AX25HNDLER_INIT_INF_EID   2
#define AX25HNDLER_ILOAD_INF_EID  3
#define AX25HNDLER_CDS_INF_EID    4
#define AX25HNDLER_CMD_INF_EID    5

#define AX25HNDLER_ERR_EID         51
#define AX25HNDLER_INIT_ERR_EID    52
#define AX25HNDLER_ILOAD_ERR_EID   53
#define AX25HNDLER_CDS_ERR_EID     54
#define AX25HNDLER_CMD_ERR_EID     55
#define AX25HNDLER_PIPE_ERR_EID    56
#define AX25HNDLER_MSGID_ERR_EID   57
#define AX25HNDLER_MSGLEN_ERR_EID  58

#define AX25HNDLER_EVT_CNT  14

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

#endif /* _AX25HNDLER_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file ax25hndler_private_ids.h
**=====================================================================================*/
    