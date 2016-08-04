/*=======================================================================================
** File Name:  axtxrx_iload_utils.h
**
** Title:  ILoad Tables' Utility Header File for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AXTXRX's ILoad table-related utility functions
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AXTXRX_ILOAD_UTILS_H_
#define _AXTXRX_ILOAD_UTILS_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "axtxrx_app.h"

/*
** Local Defines
*/

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
int32  AXTXRX_InitILoadTbl(void);
int32  AXTXRX_ValidateILoadTbl(AXTXRX_ILoadTblEntry_t*);
void   AXTXRX_ProcessNewILoadTbl(void);

#endif /* _AXTXRX_ILOAD_UTILS_H_ */

/*=======================================================================================
** End of file axtxrx_iload_utils.h
**=====================================================================================*/
    