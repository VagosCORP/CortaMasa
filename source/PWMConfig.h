#ifndef PWMCONFIG_H
#define	PWMCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    #include "sysParams.h"
    #include "screenDrawers.h"

    char t2Cont1 = 0;
    char t2Cont2 = 0;
    
    char lastSttFC1 = 0;
    char holdFC1cont = 0;
    char FC1securLock = 0;
    char lastSttFC2 = 0;
    char holdFC2cont = 0;
    char FC2securLock = 0;
    
    long processTimer = 0;
    long securTimer = 0;
    long timeDOWN = 50;
    
    void t2config() {
        T2CONbits.TMR2ON = 0;
        T2CONbits.T2CKPS = 0b00; //1:1 Pre
        T2CONbits.T2OUTPS = 0b1111; //1:16 Post
        PR2 = 199; //50 us OF ~ 20kHz
        PIR1bits.TMR2IF = 0;
        IPR1bits.TMR2IP = 0;
        PIE1bits.TMR2IE = 1;
        T2CONbits.TMR2ON = 1;
    }
    
    void setPWM2duty(signed short actuator) {
        short act = 400;
        if(actuator > 400)
            act = 800;
        else if(actuator < -400)
            act = 0;
        else
            act = actuator + 400;
        CCP2CONbits.DC2B = act;
        CCPR2L = act>>2;
    }
    
    void subirCuchilla(void) {
        setPWM2duty(-400);
    }
    
    void bajarCuchilla(void) {
        setPWM2duty(400);
    }
    
    void detenerCuchilla(void) {
        setPWM2duty(0);
    }
    
    void initProtocoll(char init) {
        if(init) {
            LED_ERR = 0;
            processTimer = 0;
            processState = 0;
            if(!bladeIsUP)
                subirCuchilla();
        }
        //actualScreen = tempLastScreen;
    }
    
    void stopProcess() {
        processStarted = 0;
        ready2Cut = 0;
        REL = 0;
        detenerCuchilla();
    }
    
    void T2int() {
        if(!processStarted && actualScreen != SCREEN_READY_2CUT && !ready2Cut || bladeIsUP && bladeIsDown)
            stopProcess();
        t2Cont1++;
        if(FC1 && !lastSttFC1) {//pressFC1();
            lastSttFC1 = 1;
            detenerCuchilla();
            bladeIsUP = 1;
            processTimer = 0;
            if(processStarted)
                processState++;
            securTimer = 0;
            if(processStarted && processState >= numCortes) {
                processStarted = 0;
                saveProcessState();
                if(calibMode) {
                    actualScreen = SCREEN_CALIB_RMAS;
                    tempLastScreen = SCREEN_CALIB_PROCESS;
                }
                initProtocoll(1);
            }
            t2Cont1 = 0;
        }else if(!FC1 && lastSttFC1) {
            if(t2Cont1 > 124) {
                lastSttFC1 = 0;
                bladeIsUP = 0;
            }
        }else if(FC1 == lastSttFC1) {
            if(!FC1)
                bladeIsUP = 0;
        }
        t2Cont2++;
        if(FC2 && !lastSttFC2) {//pressFC2();
            lastSttFC2 = 1;
            detenerCuchilla();
            bladeIsDown = 1;
            processTimer = 0;
            securTimer = 0;
            if(processStarted)
                processState++;
            if(ready2Cut) {
                processStarted = 1;
                ready2Cut = 0;
            }
            saveProcessState();
            if(processStarted && processState >= numCortes) {
                processStarted = 0;
                saveProcessState();
                if(calibMode) {
                    actualScreen = SCREEN_CALIB_RMAS;
                    tempLastScreen = SCREEN_CALIB_PROCESS;
                }
                initProtocoll(1);
            }
            t2Cont2 = 0;
        }else if(!FC2 && lastSttFC2) {
            if(t2Cont2 > 124) {
                lastSttFC2 = 0;
                bladeIsDown = 0;
            }
        }else if(FC2 == lastSttFC2) {
            if(!FC2)
                bladeIsDown = 0;
        }
        
    }
    
    void PWM2Config() {
        TRISCbits.TRISC0 = 1;
        TRISCbits.TRISC1 = 1;
        PSTR2CONbits.STR2A = 1;
        PSTR2CONbits.STR2B = 1;
        PSTR2CONbits.STR2C = 0;
        PSTR2CONbits.STR2D = 0;
        CCPTMRS0bits.C2TSEL = 0b00;
        PR2 = 199; //50 us OF ~ 20kHz
        ECCP2ASbits.CCP2AS = 0b000; //no auto ShutDown
        ECCP2ASbits.PSS2AC = 0b00;
        ECCP2ASbits.PSS2BD = 0b00;
        PWM2CONbits.P2RSEN = 0;
        ECCP2ASbits.CCP2AS = 1;
        CCP2CONbits.P2M = 0b10;
        CCP2CONbits.CCP2M = 0b1100;
        setPWM2duty(0);
        PWM2CONbits.P2DC = 16; //4us deadband
        t2config();
        TRISCbits.TRISC0 = 0;
        TRISCbits.TRISC1 = 0;
        ECCP2ASbits.CCP2ASE = 0; //no shutdown autorestart
    }
    
    void setPWM2on(char on) {
        if(on) {
            TRISCbits.TRISC0 = 0;
            TRISCbits.TRISC1 = 0;
        }else {
            TRISCbits.TRISC0 = 1;
            TRISCbits.TRISC1 = 1;
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* PWMCONFIG_H */

