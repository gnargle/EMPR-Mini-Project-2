//ALWAYS MATCH THE SIZE WITH INT

#include "lcd_display.h"
#include "lcd_display.c"
//#include "serial.h"
//#include "serial.c"
#include "keypad.c"
#include "keypad.h"

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
    /* Code to scan i2c. No longer necessary.
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
    /*  Code to print a random thing to the display.
    char strtosend[] = "01234567890123456789012345678901";
    uint8_t addr = 0x80;
    clear_display(59);
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
    }*/
    init_display(59);
    int u = 0;
    init_keypad(33);
    char write[32] = "";
    uint8_t addr;
    while(1){
        if (u == 1000000){
            char x;
            x = read_keypad(33);
            if (x == '#'){
                init_display(59);
                addr = 0x80;
                clear_display(59);
                addr = 0x80;
                for(i=0; i < strlen(write); i++){
                        if (addr == (0x80 + 16)){
                            addr = 0x80 + 40;
                            write_display(59, addr, (write[i]) | 0x80);
                            addr++;
                        }
                        else{
                            write_display(59, addr, (write[i]) | 0x80);
                            addr++;
                            }
                        }
                strcpy(write, "");
            }
            else if (isdigit(x)){
                append(write, x);
            }
        }
        else{
            u++;
        }
    }
    return 0;
}


void append(char* s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}
