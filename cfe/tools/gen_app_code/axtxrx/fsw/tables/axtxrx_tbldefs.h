/*=======================================================================================
** File Name:  axtxrx_tbldefs.h
**
** Title:  Header File for AXTXRX Application's tables
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This header file contains declarations and definitions of data structures
**           used in AXTXRX's tables.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _AXTXRX_TBLDEFS_H_
#define _AXTXRX_TBLDEFS_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "common_types.h"
#include "axtxrx_mission_cfg.h"

/*
** Local Defines
*/
#define AXTXRX_ILOAD_MAX_ENTRIES  1
#define AXTXRX_ILOAD_FILENAME     "/cf/apps/axtxrx_iloads.tbl"
#define AXTXRX_ILOAD_TABLENAME    "ILOAD_TBL"


/*
** Local Structure Declarations
*/ 
/* Definition for Iload table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for ILoad parameters here.
    **
    ** Examples:
    **    int8/char            cParam;
    **    int8/char            cParams[16];
    **    uint8/unsigned char  ucParam;
    **    uint8/unsigned char  ucParams[16];
    **
    **    int16   sParam;
    **    int16   sParams[8];
    **    uint16  usParam;
    **    uint16  usParams[8];
    **
    **    int32   iParam;
    **    int32   iParams[5];
    **    uint32  uiParam;
    **    uint32  uiParams[5];
    **
    **    float  fParam;
    **    float  fParams[3];
    **
    **    double  dParam;
    **    double  dParams[3];
    */
} AXTXRX_ILoadTblEntry_t;
    
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

#endif /* _AXTXRX_TBLDEFS_H_ */

/*=======================================================================================
** End of file axtxrx_tbldefs.h
**=====================================================================================*/
    