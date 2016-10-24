#ifndef PWMCONFIG_H
#define	PWMCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    void t2config() {
        T2CONbits.TMR2ON = 0;
        T2CONbits.T2CKPS = 0b00; //1:1 Pre
        T2CONbits.T2OUTPS = 0b1111; //1:16 Post
//        PR2 = 199; //50 us OF ~ 20kHz
        PIR1bits.TMR2IF = 0;
        IPR1bits.TMR2IP = 1;
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
    
    void T2int() {
        if(FC1 || FC2)
            setPWM2duty(0);
    }
    
    void PWM2Config() {
        TRISCbits.TRISC0 = 1;
        TRISCbits.TRISC1 = 1;
        PSTR2CONbits.STR2A = 1;
        PSTR2CONbits.STR2B = 1;
        PSTR2CONbits.STR2C = 0;
        PSTR2CONbits.STR2D = 0;
        CCPTMRS0bits.C2TSEL = 0b00;
        PR2 = 199;
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

