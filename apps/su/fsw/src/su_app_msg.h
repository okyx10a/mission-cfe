#ifndef _su_app_msg_h_
#define _su_app_msg_h_

typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];

} SU_NoArgsCmd_t;

typedef struct 
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              su_command_error_count;
    uint8              su_command_count;
    uint8              spare[2];

}   OS_PACK su_hk_tlm_t  ;

#define SU_APP_HK_TLM_LNGTH   sizeof ( su_hk_tlm_t )

#endif