#include "SYSConfig.h"
#include "IOConfig.h"
#include "UARTConfig.h"
#include "../../Comunic.h"
#include "../../delay.h"
#include "T2Config.h"
#include "PWMConfig.h"
#include "sysParams.h"
#include "DisplayProtocol.h"

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
    sysParamInit();
    ioConfig();
    lcd_init();
    PWM2Config();
    UARTConfig();
    interruptConfig();
    
    while(1) {
        drawScreen();
        if(!UP && lastSttUP) {
            lastSttUP = 0;
            delay_ms(200);
        }else if(UP && !lastSttUP) {
            lastSttUP = 1;
            if(holdUPcont < 10)
                pressUP();
            delay_ms(50);
        }else if(UP == lastSttUP) {
            if(UP) {
                holdUPcont = 0;
                releaseUP();
            }
            else {
                if(!UPsecurLock)
                    holdUPcont++;
                if(holdUPcont > 9) {
                    if(holdUPcont < 26)
                        longPressUP();
                    else
                        UPsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!DOWN && lastSttDOWN) {
            lastSttDOWN = 0;
            delay_ms(200);
        }else if(DOWN && !lastSttDOWN) {
            lastSttDOWN = 1;
            if(holdDOWNcont < 10)
                pressDOWN();
            delay_ms(50);
        }else if(DOWN == lastSttDOWN) {
            if(DOWN) {
                holdDOWNcont = 0;
                releaseDOWN();
            }
            else {
                if(!DOWNsecurLock)
                    holdDOWNcont++;
                if(holdDOWNcont > 9) {
                    if(holdDOWNcont < 26)
                        longPressDOWN();
                    else
                        DOWNsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!RETRO && lastSttRETRO) {
            lastSttRETRO = 0;
            delay_ms(200);
        }else if(RETRO && !lastSttRETRO) {
            lastSttRETRO = 1;
            if(holdRETROcont < 10)
                pressRETRO();
            delay_ms(50);
        }else if(RETRO == lastSttRETRO) {
            if(RETRO) {
                holdRETROcont = 0;
                releaseRETRO();
            }
            else {
                if(!RETROsecurLock)
                    holdRETROcont++;
                if(holdRETROcont > 9) {
                    if(holdRETROcont < 26)
                        longPressRETRO();
                    else
                        RETROsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!ENTER && lastSttENTER) {
            lastSttENTER = 0;
            delay_ms(200);
        }else if(ENTER && !lastSttENTER) {
            lastSttENTER = 1;
            if(holdENTERcont < 10)
                pressENTER();
            delay_ms(50);
        }else if(ENTER == lastSttENTER) {
            if(ENTER) {
                holdENTERcont = 0;
                releaseENTER();
            }
            else {
                if(!ENTERsecurLock)
                    holdENTERcont++;
                if(holdENTERcont > 9) {
                    if(holdENTERcont < 26)
                        longPressENTER();
                    else
                        ENTERsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        execCombinations();
    }
}