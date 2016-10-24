#ifndef UARTCONFIG_H
#define	UARTCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    void putchUART(char val) {
        while(!TXSTA1bits.TRMT);
        TXREG1 = val;
    }
    
    void UARTint() {
        putch(RCREG1);
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

