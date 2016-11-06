#ifndef T4CONFIG_H
#define	T4CONFIG_H

#include "sysParams.h"
#include "UARTConfig.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
    void T4int() {
        CLRWDT();//si no se llama, en 128ms reset!
        processTimer++;
        if(bladeIsUP) {
            if(processTimer >= timsXcorte && ProcessStarted && processState < numCortes) {
                setPWM2duty(400);
                REL = 1;
//                putchUART('R');
//                putchUART('=');
//                putchUART('1');
//                putchUART(10);
            }
        }else {
            if(processTimer >= timeDOWN && ProcessStarted) {
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

