#ifndef _tester_app_msg_h_
#define _tester_app_msg_h_

typedef struct 
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              tester_command_error_count;
    uint8              tester_command_count;
    uint8              spare[2];

}   OS_PACK tester_hk_tlm_t  ;

#define TESTER_APP_HK_TLM_LNGTH   sizeof ( tester_hk_tlm_t )

#endif