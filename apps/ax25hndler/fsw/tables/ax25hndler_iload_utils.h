/*=======================================================================================
** File Name:  ax25hndler_iload_utils.h
**
** Title:  ILoad Tables' Utility Header File for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  To define AX25HNDLER's ILoad table-related utility functions
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AX25HNDLER_ILOAD_UTILS_H_
#define _AX25HNDLER_ILOAD_UTILS_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "ax25hndler_app.h"

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
int32  AX25HNDLER_InitILoadTbl(void);
int32  AX25HNDLER_ValidateILoadTbl(AX25HNDLER_ILoadTblEntry_t*);
void   AX25HNDLER_ProcessNewILoadTbl(void);

#endif /* _AX25HNDLER_ILOAD_UTILS_H_ */

/*=======================================================================================
** End of file ax25hndler_iload_utils.h
**=====================================================================================*/
    