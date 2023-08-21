#include "openSpi.h"
#include "macrosAndGlobalVar.h"

void Open_SPI()
{
    /// Configuracion de los registros SSPSTAT y SSPCON1:
        SSPSTATbits.SMP = 0;        //  bit 7 del SSPSTAT
        SSPSTATbits.CKE = 0;        //  bit 6 del SSPSTAT
        SSPCON1bits.SSPEN = 1;      //  MSSP habilitado
        SSPCON1bits.CKP = 1;        //  CLK Highlvl
    /// Modo esclavo o maestro    
        SSPCON1bits.SSPM3 = 0;      //  
        SSPCON1bits.SSPM2 = 0;      //  Master mode,
        SSPCON1bits.SSPM1 = 1;      //  clock = FOSC/64 (low-speed)
        SSPCON1bits.SSPM0 = 0;      //
    /// Configuracion de los pines del modulo SSP  
        TRISDbits.TRISD3 = 0;       //  activar pin CS como salida para tarjeta mmcSD
        TRISCbits.TRISC3 = 0;       //  pin SCL como salida
        TRISCbits.TRISC4 = 1;       //  pin SDI como entrada
        TRISCbits.TRISC5 = 0;       //  pin SDO como salida

        ChipSelect = 1;
}

char WriteChar_SPI(char data)
{
    SSPBUF = data;
    while(!BF) {}
    return SSPBUF;
}
