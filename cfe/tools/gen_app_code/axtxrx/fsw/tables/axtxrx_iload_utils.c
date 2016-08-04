/*=======================================================================================
** File Name:  axtxrx_iload_utils.c
**
** Title:  Iload Tables' Utilities for AXTXRX Application
**
** $Author:    YUsend Lab
** $Revision: 1.1 $
** $Date:      2016-08-02
**
** Purpose:  This source file contains definitions of ILoad table-related utility
**           function for AXTXRX application.
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
#include "axtxrx_iload_utils.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/
extern AXTXRX_AppData_t  g_AXTXRX_AppData;

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
** Name: AXTXRX_InitILoadTbl
**
** Purpose: To initialize the AXTXRX's ILoad tables
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
**    AXTXRX_ValidateILoadTbl
**    AXTXRX_ProcessNewILoadTbl
**
** Called By:
**    AXTXRX_InitApp
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
int32 AXTXRX_InitILoadTbl()
{
    int32  iStatus=0;

    /* Register ILoad table */
    iStatus = CFE_TBL_Register(&g_AXTXRX_AppData.ILoadTblHdl,
                               AXTXRX_ILOAD_TABLENAME,
                               (sizeof(AXTXRX_ILoadTblEntry_t) * AXTXRX_ILOAD_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               AXTXRX_ValidateILoadTbl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to register ILoad table (0x%08X)\n", iStatus);
        goto AXTXRX_InitILoadTbl_Exit_Tag;
    }

    /* Load ILoad table file */
    iStatus = CFE_TBL_Load(g_AXTXRX_AppData.ILoadTblHdl,
                           CFE_TBL_SRC_FILE,
                           AXTXRX_ILOAD_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to load ILoad Table (0x%08X)\n", iStatus);
        goto AXTXRX_InitILoadTbl_Exit_Tag;
    }

    /* Manage ILoad table */
    iStatus = CFE_TBL_Manage(g_AXTXRX_AppData.ILoadTblHdl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to manage ILoad table (0x%08X)\n", iStatus);
        goto AXTXRX_InitILoadTbl_Exit_Tag;
    }

    /* Make sure ILoad table is accessible by getting referencing it */
    iStatus = CFE_TBL_GetAddress((void*)&g_AXTXRX_AppData.ILoadTblPtr,
                                 g_AXTXRX_AppData.ILoadTblHdl);
    if (iStatus != CFE_TBL_INFO_UPDATED)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to get ILoad table's address (0x%08X)\n", iStatus);
        goto AXTXRX_InitILoadTbl_Exit_Tag;
    }

    /* Validate ILoad table */
    iStatus = AXTXRX_ValidateILoadTbl(g_AXTXRX_AppData.ILoadTblPtr);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("AXTXRX - Failed to validate ILoad table (0x%08X)\n", iStatus);
        goto AXTXRX_InitILoadTbl_Exit_Tag;
    }

    /* Set new parameter values */
    AXTXRX_ProcessNewILoadTbl();

AXTXRX_InitILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: axtxrx_ValidateILoadTbl
**
** Purpose: To validate the AXTXRX's ILoad tables
**
** Arguments:
**    AXTXRX_ILoadTblEntry_t*  iLoadTblPtr - pointer to the ILoad table
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
int32 AXTXRX_ValidateILoadTbl(AXTXRX_ILoadTblEntry_t* iLoadTblPtr)
{
    int32  iStatus=0;

    if (iLoadTblPtr == NULL)
    {
        iStatus = -1;
        goto AXTXRX_ValidateILoadTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    **    if (iLoadTblPtr->sParam <= 16)
    **    {
    **        CFE_ES_WriteToSysLog("AXTXRX - Invalid value for ILoad parameter sParam (%d)\n",
    **                             iLoadTblPtr->sParam);
    */

AXTXRX_ValidateILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: AXTXRX_ProcessNewILoadTbl
**
** Purpose: To process AXTXRX's new ILoad tables and set ILoad parameters with new values
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
void AXTXRX_ProcessNewILoadTbl()
{
    /* TODO:  Add code to set new ILoad parameters with new values here.
    **
    ** Examples:
    **
    **    g_AXTXRX_AppData.latest_sParam = g_AXTXRX_AppData.ILoadTblPtr->sParam;
    **    g_AXTXRX_AppData.latest_fParam = g_AXTXRX.AppData.ILoadTblPtr->fParam;
    */
}
    
/*=======================================================================================
** End of file axtxrx_iload_utils.c
**=====================================================================================*/
    