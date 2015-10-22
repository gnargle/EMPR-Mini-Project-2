#include "lpc_types.h"

I2C_M_SETUP_Type setup_TransferCfg(I2C_M_SETUP_Type TransferCfg, int addr, unsigned long *wrtptr, int wrtlength,
    unsigned long *rdptr, int rdlength){
    TransferCfg.sl_addr7bit = addr;
    TransferCfg.tx_data = wrtptr;
    TransferCfg.tx_length = wrtlength;
    TransferCfg.rx_data = rdptr;
    TransferCfg.rx_length = rdlength;
    return TransferCfg;
}

I2C_M_SETUP_Type change_write_data(I2C_M_SETUP_Type TransferCfg, 
    unsigned long *ptr, int data){
    ptr[1] = data;
    TransferCfg.tx_data = ptr;
    return TransferCfg;
}
