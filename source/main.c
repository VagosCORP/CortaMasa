#include "SYSConfig.h"
#include "../../delay.h"
#include "IOConfig.h"
#include "UARTConfig.h"
#include "../../Comunic.h"
#include "T2Config.h"
#include "PWMConfig.h"
#include "sysParams.h"
#include "screenDrawers.h"
#include "DisplayProtocol.h"
#include "ButtonController.h"

void interrupt hp_isr(void) {
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF) {
        T2int();
        PIR1bits.TMR2IF = 0;
    }
}

void interrupt low_priority isr(void) {
    if(PIE1bits.RC1IE && PIR1bits.RC1IF) {
        UARTint();
        PIR1bits.RC1IF = 0;
    }
}

void main(void) {
    
    clockConfig();
    ioInitStt();
    EEPROMConfig();
//    saveSysParams();
//    sysParamInit();
    ioConfig();
    lcd_init();
    PWM2Config();
    UARTConfig();
    interruptConfig();
    
    while(1) {
        CLRWDT();
        drawScreen();
        buttonChecking();
    }
}