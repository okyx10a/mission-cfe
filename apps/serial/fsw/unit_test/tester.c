/* Includes */
#include "async.h"
#include "input.h"
#include "memory.h"

int main(int argc, char**argv) {

    int i = 0;
    uint8_t resp[254];
    /* FIPEX commands */
    uint8_t ping[] = {0x7E, 0x00, 0x00, 0x00}; /* Ping Command */
    uint8_t rqhk[] = {0x7E, 0x20, 0x00, 0x20};  /* Request House Keeping */
    uint8_t rlp[] = {0x7E, 0x10, 0x00, 0x10};  /* Request Last Packet */
    uint8_t init[] = {0x7E, 0x01, 0x00, 0x01};  /* Initialize */    
    uint8_t suID[] = {0x7E, 0x04, 0x00, 0x04};   /* Science unit ID */
    uint8_t SU_SM[] = {0x7E, 0x0C, 0x00, 0x0C};  /* Measurement mode */
    uint8_t SU_STDBY[] = {0x7E, 0x0A, 0x00, 0x0A}; /* standby Mode */
    uint8_t SU_SC[] = {0x7E, 0x0B, 0x00, 0x0B};    /* Health check mode */
    uint8_t SU_DP[] = {0x7E, 0x21, 0x00, 0x21};    /* Request Science Data packet */

        
    fd = Open_Port();
    if(fd == -1)
    {
        printf("Port not opend");
        exit(1);
    }
    Set_Attribute();
    /***************/
    /* Testing the commands to FIPEX */

    printf("\nSending the Ping Instruction\n");
    Send(ping);
    /*write(fd, ping, sizeof ping);
    sleep(1);
    tcflush(fd, TCIFLUSH);*/

    printf("\nSending the Init Instruction\n");
    Send(init);
    /*write(fd, init, sizeof init);
    sleep(1);
    tcflush(fd, TCIFLUSH);*/

    for(;;)
    {
        sleep(1);
    }
        
    return(0);
      
}
