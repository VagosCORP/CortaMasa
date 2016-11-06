#include "SYSConfig.h"
#include "../../delay.h"
#include "IOConfig.h"
#include "UARTConfig.h"
#include "../../Comunic.h"
#include "sysParams.h"
#include "PWMConfig.h"
#include "T4Config.h"
#include "screenDrawers.h"
#include "DisplayProtocol.h"
#include "ButtonController.h"


void interrupt hp_isr(void) {
    if(PIE5bits.TMR4IE && PIR5bits.TMR4IF) {
        T4int(); //counter para los cortes
        PIR5bits.TMR4IF = 0;
    }
}

void interrupt low_priority isr(void) {
    if(PIE1bits.RC1IE && PIR1bits.RC1IF) {
        UARTint();
        PIR1bits.RC1IF = 0;
    }
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF) {
        T2int();
        PIR1bits.TMR2IF = 0;
    }
}

void main(void) {
    
    clockConfig();
    t4config();
    ioInitStt();
    EEPROMConfig();
    saveSysParams();
//    sysParamInit();
    ioConfig();
    lcd_init();
    PWM2Config();
    UARTConfig();
    interruptConfig();
    CLRWDT();
    WDTCONbits.SWDTEN = 1;
    setPWM2duty(-400);
    setPWM2on(1);
    
    while(1) {
        drawScreen();
        buttonChecking();
    }
}