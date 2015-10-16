#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_uart.h" 
#include "lpc_types.h"

#define usedi2c LPC_I2C1
#define i2cfunc 3
#define i2cport 0
#define i2cpin1 0
#define i2cpin2 1

char charbuffer[1] = "a";

void pin_settings (PINSEL_CFG_Type PinCfg, int funcnumber, int drain, int mode,
    int port, int pin);

void serial_init();

void init_display(int i2c_port);

void clear_display(int i2c_port);

void write_display(int i2c_port, char char_to_write);

int read_busy_flag_display(int i2c_port);

I2C_M_SETUP_Type setup_TransferCfg(I2C_M_SETUP_Type TransferCfg, int addr, unsigned long *wrtptr, int wrtlength,
    unsigned long *rdptr, int rdlength);

I2C_M_SETUP_Type change_write_data(I2C_M_SETUP_Type TransferCfg, 
    unsigned long *ptr, int data);

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
    }
    
    init_display(59);
    write_usb_serial_blocking("3\n\r", 3);
    write_display(59, 'a');
    write_usb_serial_blocking("4\n\r", 3);
    return 0;
}

void pin_settings (PINSEL_CFG_Type PinCfg, int funcnumber, int drain, int mode,
    int port, int pin){
    PinCfg.Funcnum = funcnumber;
    PinCfg.OpenDrain = drain;
    PinCfg.Pinmode = mode;
    PinCfg.Portnum = port;
    PinCfg.Pinnum = pin;
    PINSEL_ConfigPin(&PinCfg);
}

int read_usb_serial_none_blocking(char *buf,int length)
{
    return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

// Write options
int write_usb_serial_blocking(char *buf,int length)
{
    return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}

// init code for the USB serial line
void serial_init(void){
    UART_CFG_Type UARTConfigStruct;         // UART Configuration structure variable
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;    // UART FIFO configuration Struct variable
    PINSEL_CFG_Type PinCfg;             // Pin configuration for UART

    pin_settings(PinCfg, 1, 0, 0, 0, 2);
    pin_settings(PinCfg, 1, 0, 0, 0, 3);

    UART_ConfigStructInit(&UARTConfigStruct);
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
    UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);
    UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);
    UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
    
}

void init_display(int i2c_port){
    int write[1];
    write[1] = 0x00;
    char receive[1];
    I2C_M_SETUP_Type TransferCfg;
    TransferCfg = setup_TransferCfg(TransferCfg, i2c_port, write, 1, receive, 0);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x34);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x0c);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x06);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x35);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x04);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x10);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x42);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x9f);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x34);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x02);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    clear_display(i2c_port);
}

void clear_display(int i2c_port){
    int write[1];
    write[1] = 0x00;
    char receive[1];
    I2C_M_SETUP_Type TransferCfg;
    TransferCfg = setup_TransferCfg(TransferCfg, i2c_port, write, 1, receive, 0);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x01);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
}

void write_display(int i2c_port, char char_to_write){
    while (read_busy_flag_display(i2c_port) == 1){
        // empty while just to check the flag
    }
    int write[1];
    write[1] = 0x40;
    char receive[1];
    I2C_M_SETUP_Type TransferCfg;
    TransferCfg = setup_TransferCfg(TransferCfg, i2c_port, write, 1, receive, 0);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    TransferCfg = change_write_data(TransferCfg, write, 0x64);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
}

int read_busy_flag_display(int i2c_port){

    int write[1];
    write[1] = 0x80;
    int receive[1];
    I2C_M_SETUP_Type TransferCfg;
    TransferCfg = setup_TransferCfg(TransferCfg, i2c_port, write, 1, receive, 1);
    I2C_MasterTransferData(usedi2c, &TransferCfg, I2C_TRANSFER_POLLING);
    receive[1] &= 0x80;
    if (receive[1] == 0x80){
        return 1; // busy is true
    }
    else{
        return 0;
    }
}

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
