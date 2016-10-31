#ifndef UARTCONFIG_H
#define	UARTCONFIG_H

#include "sysParams.h"
#include "DisplayProtocol.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    void putchUART(char val) {
        while(!TXSTA1bits.TRMT);
        TXREG1 = val;
    }
    
    void UARTint() {
        char sas = RCREG1;
        if(sas == 'A') {
            putchUART(actualScreen);
            putchUART(menuSection);
            putchUART(passSection);
        }else if(sas == 'B') {
            saveSysParams();
        }else if(sas == 'C') {
            sysParamInit();
        }
//            putchUART(readEEPROM(1));
//            putchUART(readEEPROM(2));
//            putchUART(readEEPROM(3));
//            putchUART(readEEPROM(4));
//            putchUART(readEEPROM(5));
//            putchUART(readEEPROM(6));
//            putchUART(readEEPROM(7));
//            putchUART(readEEPROM(8));
//            putchUART(readEEPROM(9));
//            putchUART(readEEPROM(10));
//            putchUART(readEEPROM(11));
//            putchUART(readEEPROM(12));
//            putchUART(readEEPROM(13));
//            putchUART(readEEPROM(14));
//            putchUART(readEEPROM(15));
//            putchUART(readEEPROM(16));
//            putchUART(readEEPROM(17));
//            putchUART(readEEPROM(18));
//            putchUART(readEEPROM(19));
//        char sas = RCREG1;
//        EECON1bits.WREN = 1;
//        ie = INTCONbits.GIE;
//        INTCONbits.GIE = 0;
//        writeEEPROM(1, sas);
//        delay_ms(100);
//        sas += 20;
//        writeEEPROM(2, sas);
//        putchUART(readEEPROM(1));
//        putchUART(readEEPROM(2));
//        EECON1bits.WREN = 0;
//        INTCONbits.GIE = ie;
    }
    
    void UARTConfig() {
        RCSTA1bits.SPEN = 0;
        SPBRGH1 = 0;
        SPBRG1 = 34; //115200
        ANSELCbits.ANSC6 = 0;
        ANSELCbits.ANSC7 = 0;
        TRISCbits.TRISC6 = 1;
        TRISCbits.TRISC7 = 1;
        TXSTA1bits.TX9 = 0;
        TXSTA1bits.SYNC = 0;
        TXSTA1bits.SENDB = 0;
        TXSTA1bits.BRGH = 1;
        RCSTA1bits.RX9 = 0;
        BAUDCON1bits.DTRXP = 0;
        BAUDCON1bits.CKTXP = 0;
        BAUDCON1bits.BRG16 = 1;
        BAUDCON1bits.WUE = 0;
        BAUDCON1bits.ABDEN = 0;
        RCSTA1bits.CREN = 1;
        TXSTA1bits.TXEN = 1;
        IPR1bits.RC1IP = 0;
        PIR1bits.RC1IF = 0;
        PIE1bits.RC1IE = 1;
        RCSTA1bits.SPEN = 1;
    }


#ifdef	__cplusplus
}
#endif

#endif	/* UARTCONFIG_H */

