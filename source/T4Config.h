#ifndef T4CONFIG_H
#define	T4CONFIG_H

#include "sysParams.h"
#include "UARTConfig.h"


#ifdef	__cplusplus
extern "C" {
#endif

    void cutError() {
        processStarted = 0;
        processState = 0;
        securTimer = 0;
        tempLastScreen = actualScreen;
        actualScreen = SCREEN_CUT_ERROR;
        LED_ERR = 1;
    }
    
    void T4int() {
        LED_STT = processStarted;
        CLRWDT();//si no se llama, en 128ms reset!
        //if(M1F || M2F)
            //cutError();
        processTimer++;
        if(processStarted) {
            securTimer++;
            if(bladeIsUP == 1) {
                if(securTimer > timsXcorte + maxTimePerCut)
                    cutError();
            }else {
                if(securTimer > timsXcorte + maxTimePerCut)
                    cutError();
            }
        }
        if(bladeIsUP == 1) {
            if(processTimer >= timsXcorte && processStarted && processState < numCortes) {
                setPWM2duty(400);
                REL = 1;
            }
        }else if(bladeIsUP == 0){
            if(processTimer >= timsXcorte && processStarted) {
                setPWM2duty(-400);
            }
        }
    } 
    
    void t4config() {
        T4CONbits.TMR4ON = 0;
        T4CONbits.T4CKPS = 0b01; //1:4 Pre
        T4CONbits.T4OUTPS = 0b0100; //1:5 Post
        PR4 = 199; //1000 us OF ~ 1kHz
        PIR5bits.TMR4IF = 0;
        IPR5bits.TMR4IP = 1;
        PIE5bits.TMR4IE = 1;
        T4CONbits.TMR4ON = 1;
    }


#ifdef	__cplusplus
}
#endif

#endif	/* T4CONFIG_H */

