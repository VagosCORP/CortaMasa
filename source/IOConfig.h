#ifndef IOCONFIG_H
#define	IOCONFIG_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

    
    #define LCD_RS  PORTBbits.RB1
    #define LCD_RW  PORTBbits.RB2
    #define LCD_EN  PORTBbits.RB3
    #define LCD_D4  PORTBbits.RB4
    #define LCD_D5  PORTBbits.RB5
    #define LCD_D6  PORTBbits.RB6
    #define LCD_D7  PORTBbits.RB7
    #define TRIS_LCD_D4 TRISBbits.TRISB4
    #define TRIS_LCD_D5 TRISBbits.TRISB5
    #define TRIS_LCD_D6 TRISBbits.TRISB6
    #define TRIS_LCD_D7 TRISBbits.TRISB7
    #include "../../vclib_lcd.h"

    #define FC1     PORTAbits.RA7
    #define FC2     PORTAbits.RA6
    #define MOA     PORTCbits.RC1
    #define MOB     PORTCbits.RC0
    #define M1F     PORTCbits.RC2
    #define M2F     PORTCbits.RC3
    #define S1      PORTAbits.RA2
    #define UP      PORTAbits.RA2
    #define S2      PORTAbits.RA3
    #define DOWN    PORTAbits.RA3
    #define S3      PORTAbits.RA4
    #define RETRO   PORTAbits.RA4
    #define S4      PORTAbits.RA5
    #define ENTER   PORTAbits.RA5
    #define LED_STT LATBbits.LATB0
    #define LED_ERR LATCbits.LATC5
    #define REL     LATCbits.LATC4

    char lastSttUP = 1;
    char lastSttDOWN = 1;
    char lastSttRETRO = 1;
    char lastSttENTER = 1;
    char holdUPcont = 0;
    char holdDOWNcont = 0;
    char holdRETROcont = 0;
    char holdENTERcont = 0;
    char UPisLP = 0;
    char DOWNisLP = 0;
    char RETROisLP = 0;
    char ENTERisLP = 0;
    char UPsecurLock = 0;
    char DOWNsecurLock = 0;
    char RETROsecurLock = 0;
    char ENTERsecurLock = 0;
    
    void putchUART(char val) {
        while(!TXSTA1bits.TRMT);
        TXREG1 = val;
    }
    
    void putch(char val) {
        lcd_putc(val);
        putchUART(val);
    }
    
    void ioConfig() {
        TRISBbits.TRISB1 = 0;
        TRISBbits.TRISB2 = 0;
        TRISBbits.TRISB3 = 0;
        TRISBbits.TRISB0 = 0;
        TRISCbits.TRISC5 = 0;
        TRISAbits.TRISA7 = 1;
        TRISAbits.TRISA6 = 1;
        TRISCbits.TRISC2 = 1;   ANSELCbits.ANSC2 = 0;
        TRISCbits.TRISC3 = 1;   ANSELCbits.ANSC3 = 0;
        TRISAbits.TRISA2 = 1;   ANSELAbits.ANSA2 = 0;
        TRISAbits.TRISA3 = 1;   ANSELAbits.ANSA3 = 0;
        TRISAbits.TRISA4 = 1;   
        TRISAbits.TRISA5 = 1;   ANSELAbits.ANSA5 = 0;
        TRISCbits.TRISC4 = 0; 
    }
    
    void ioInitStt() {
        REL = 0;
        LED_STT = 0;
        LED_ERR = 0;
    }


#ifdef	__cplusplus
}
#endif

#endif	/* IOCONFIG_H */

