/*=======================================================================================
** File Name:  ax25hndler_iload_utils.c
**
** Title:  Iload Tables' Utilities for AX25HNDLER Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This source file contains definitions of ILoad table-related utility
**           function for AX25HNDLER application.
**
** Functions Defined:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. One source file per CFS table!
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-08-02 | YUsend Lab | Build #: Code Started
**
**=====================================================================================*/

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
** Local Structure Declarations
*/

/*
** External Global Variables
*/
extern AX25HNDLER_AppData_t  g_AX25HNDLER_AppData;

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/
    
/*=====================================================================================
** Name: AX25HNDLER_InitILoadTbl
**
** Purpose: To initialize the AX25HNDLER's ILoad tables
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_TBL_Register
**    CFE_TBL_Load
**    CFE_TBL_Manage
**    CFE_TBL_GetAddress
**    CFE_ES_WriteToSysLog
**    AX25HNDLER_ValidateILoadTbl
**    AX25HNDLER_ProcessNewILoadTbl
**
** Called By:
**    AX25HNDLER_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Programmer(s):  GSFC, YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 AX25HNDLER_InitILoadTbl()
{
    int32  iStatus=0;

    /* Register ILoad table */
    iStatus = CFE_TBL_Register(&g_AX25HNDLER_AppData.ILoadTblHdl,
                               AX25HNDLER_ILOAD_TABLENAME,
                               (sizeof(AX25HNDLER_ILoadTblEntry_t) * AX25HNDLER_ILOAD_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               AX25HNDLER_ValidateILoadTbl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to register ILoad table (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitILoadTbl_Exit_Tag;
    }

    /* Load ILoad table file */
    iStatus = CFE_TBL_Load(g_AX25HNDLER_AppData.ILoadTblHdl,
                           CFE_TBL_SRC_FILE,
                           AX25HNDLER_ILOAD_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to load ILoad Table (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitILoadTbl_Exit_Tag;
    }

    /* Manage ILoad table */
    iStatus = CFE_TBL_Manage(g_AX25HNDLER_AppData.ILoadTblHdl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to manage ILoad table (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitILoadTbl_Exit_Tag;
    }

    /* Make sure ILoad table is accessible by getting referencing it */
    iStatus = CFE_TBL_GetAddress((void*)&g_AX25HNDLER_AppData.ILoadTblPtr,
                                 g_AX25HNDLER_AppData.ILoadTblHdl);
    if (iStatus != CFE_TBL_INFO_UPDATED)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to get ILoad table's address (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitILoadTbl_Exit_Tag;
    }

    /* Validate ILoad table */
    iStatus = AX25HNDLER_ValidateILoadTbl(g_AX25HNDLER_AppData.ILoadTblPtr);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AX25HNDLER - Failed to validate ILoad table (0x%08X)\n", iStatus);
        goto AX25HNDLER_InitILoadTbl_Exit_Tag;
    }

    /* Set new parameter values */
    AX25HNDLER_ProcessNewILoadTbl();

AX25HNDLER_InitILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: ax25hndler_ValidateILoadTbl
**
** Purpose: To validate the AX25HNDLER's ILoad tables
**
** Arguments:
**    AX25HNDLER_ILoadTblEntry_t*  iLoadTblPtr - pointer to the ILoad table
**
** Returns:
**    int32 iStatus - Status of table updates
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Programmer(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 AX25HNDLER_ValidateILoadTbl(AX25HNDLER_ILoadTblEntry_t* iLoadTblPtr)
{
    int32  iStatus=0;

    if (iLoadTblPtr == NULL)
    {
        iStatus = -1;
        goto AX25HNDLER_ValidateILoadTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    **    if (iLoadTblPtr->sParam <= 16)
    **    {
    **        CFE_ES_WriteToSysLog("AX25HNDLER - Invalid value for ILoad parameter sParam (%d)\n",
    **                             iLoadTblPtr->sParam);
    */

AX25HNDLER_ValidateILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: AX25HNDLER_ProcessNewILoadTbl
**
** Purpose: To process AX25HNDLER's new ILoad tables and set ILoad parameters with new values
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Programmer(s):  YUsend Lab 
**
** History:  Date Written  2016-08-02
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void AX25HNDLER_ProcessNewILoadTbl()
{
    /* TODO:  Add code to set new ILoad parameters with new values here.
    **
    ** Examples:
    **
    **    g_AX25HNDLER_AppData.latest_sParam = g_AX25HNDLER_AppData.ILoadTblPtr->sParam;
    **    g_AX25HNDLER_AppData.latest_fParam = g_AX25HNDLER.AppData.ILoadTblPtr->fParam;
    */
}
    
/*=======================================================================================
** End of file ax25hndler_iload_utils.c
**=====================================================================================*/
    