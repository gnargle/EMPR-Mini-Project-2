//ALWAYS MATCH THE SIZE WITH INT

#include "lcd_display.h"
#include "lcd_display.c"
#include "serial.h"
#include "serial.c"

#define usedi2c LPC_I2C1
#define i2cfunc 3
#define i2cport 0
#define i2cpin1 0
#define i2cpin2 1
#define emptychar 0xA0

char charbuffer[1] = "a";

int j = 0;
int success_ports[128];
int i=0;

char receive[1];

int main(void){
    PINSEL_CFG_Type PinCfg;

    serial_init();
    pin_settings(PinCfg, i2cfunc, 0, 0, i2cport, i2cpin1);
    pin_settings(PinCfg, i2cfunc, 0, 0, i2cport, i2cpin2);
    I2C_Init(usedi2c, 100000);
    I2C_Cmd(usedi2c, ENABLE);
    write_usb_serial_blocking("1\n\r", 3);
    /*
    while(i < 128){
        I2C_M_SETUP_Type TransferCfg;
        TransferCfg = setup_TransferCfg(TransferCfg,i,charbuffer,1,receive,0);
        if (I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING) 
            == SUCCESS){
            write_usb_serial_blocking("Success on port ", 16);
            char port[3] = "";
            sprintf(port, "%i", i);
            write_usb_serial_blocking(port, 3);
            write_usb_serial_blocking(" \n\r", 3);
            j++;
        }
        i++;
    }*/
    init_display(59);
    write_usb_serial_blocking("3\n\r", 3);
    char strtosend[] = "All we wanna do is have some fun";
    uint8_t addr = 0x80;
    for (i=0; i <33; i++){
        if (addr == (0x80 + 16)){
            addr = 0x80 + 40;
            write_display(59, addr, emptychar);
            addr++;
        }
        else{
            write_display(59, addr, emptychar);
            addr++;
        }
    }
    addr = 0x80;
    for(i=0; i < strlen(strtosend); i++){
        if (addr == (0x80 + 16)){
            addr = 0x80 + 40;
            write_display(59, addr, (strtosend[i]) | 0x80);
            addr++;
        }
        else{
            write_display(59, addr, (strtosend[i]) | 0x80);
            addr++;
        }
    }
    write_usb_serial_blocking("4\n\r", 3);
    return 0;
}
