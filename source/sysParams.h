#ifndef SYSPARAMS_H
#define	SYSPARAMS_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    #include "../../Comunic.h"

    FLOATDATA fData;
    INT16DATA i16Data;
    
    char ProcessStarted = 0;
    
    float pi = 3.14159265358979323846;
    short processState = 0;
    float kgXcorte = 1.0;
    float tempkgXcorte = 0.1;
    float tiXcorte = 10.0f; //2-5
    float timsXcorte = 10000.0f; //2-5
    short numCortes = 5; //6-7
    short tempNumCortes = 1;
    float diamTubo = 20.000f; //8-11
//    float densidadMasa = 1.5; //12-15
    float velocidadMasa = 0.2; //16-19
    float calFactor = 0;
    
    char ie = 0;
    
    void writeEEPROM(char adr, char data) {
    EEADR = adr;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
}

char readEEPROM(char adr) {
    EEADR = adr;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    while(EECON1bits.RD);
    return EEDATA;
}
    
    void EEPROMConfig() {
        EECON1bits.WREN = 0;
        EECON1bits.FREE = 0;
    }
    
    void calcSysVars() {
        float temp = 0;
        timsXcorte = (float)tiXcorte * 1000;
//        mXcorte = velocidadMasa * tiXcorte;
//        temp = (float)diamTubo / 2000.0f;
//        temp *= temp;
//        temp *= pi;
//        m3Xcorte = (float)temp * mXcorte;
        kgXcorte = (float)velocidadMasa * tiXcorte;
    }
    
    void calcVars2ti() {
//        float temp = 0;
//        temp = (float)diamTubo / 2000.0f;
//        temp *= temp;
//        temp *= pi;
//        temp *= velocidadMasa;
//        if(tVarProceso == tvp_kg) {
//        m3Xcorte = (float)kgXcorte / densidadMasa;
        tiXcorte = (float)kgXcorte / velocidadMasa;
        timsXcorte = (float)tiXcorte * 1000;
//        mXcorte = (float)velocidadMasa * tiXcorte;
//        }else if(tVarProceso == tvp_m) {
//            tiXcorte = (float)mXcorte / velocidadMasa;
//            timsXcorte = (float)tiXcorte * 1000;
//            m3Xcorte = (float)tiXcorte * temp;
//            kgXcorte = (float)densidadMasa * m3Xcorte;
//        }else if(tVarProceso == tvp_ti) {
//            timsXcorte = (float)tiXcorte * 1000;
//            mXcorte = (float)velocidadMasa * tiXcorte;
//            m3Xcorte = (float)temp * tiXcorte;
//            kgXcorte = (float)densidadMasa * m3Xcorte; 
//        }  
    }
    
    void saveSysParams() {
        EECON1bits.WREN = 1;
        ie = INTCONbits.GIE;
        INTCONbits.GIE = 0;
//        writeEEPROM(1, tVarProceso); //1
        fData.floatdat = tiXcorte; //2-5
        writeEEPROM(2, fData.floatMB);
        writeEEPROM(3, fData.floatUB);
        writeEEPROM(4, fData.floatHB);
        writeEEPROM(5, fData.floatLB);
        i16Data.int16dat = numCortes; //6-7
        writeEEPROM(6, i16Data.int16HB);
        writeEEPROM(7, i16Data.int16LB);
        fData.floatdat = diamTubo; //8-11
        writeEEPROM(8, fData.floatMB);
        writeEEPROM(9, fData.floatUB);
        writeEEPROM(10, fData.floatHB);
        writeEEPROM(11, fData.floatLB);
//        fData.floatdat = densidadMasa; //12-15
//        writeEEPROM(12, fData.floatMB);
//        writeEEPROM(13, fData.floatUB);
//        writeEEPROM(14, fData.floatHB);
//        writeEEPROM(15, fData.floatLB);
        fData.floatdat = velocidadMasa; //16-19
        writeEEPROM(16, fData.floatMB);
        writeEEPROM(17, fData.floatUB);
        writeEEPROM(18, fData.floatHB);
        writeEEPROM(19, fData.floatLB);
        EECON1bits.WREN = 0;
        INTCONbits.GIE = ie;
        calcVars2ti();
    }
    
    void saveProcessState() {
        EECON1bits.WREN = 1;
        ie = INTCONbits.GIE;
        INTCONbits.GIE = 0;
        writeEEPROM(30, ProcessStarted); //30
        writeEEPROM(31, processState); //31
        EECON1bits.WREN = 0;
        INTCONbits.GIE = ie;
    }
    
//    void preAutoCal() {
//        float temp = 0;
//        float temp2 = 2000.0f * 2000.0f;
//        tempNumCortes = numCortes;
//        numCortes = 10;
//        tempkgXcorte = kgXcorte;
//        kgXcorte = 1.0f;
//        temp = (float)pi*densidadMasa*numCortes*diamTubo*diamTubo*tiXcorte;
//        calFactor = (float)temp2/temp;
//        velocidadMasa = (float)kgXcorte * calFactor;
//    }
//    
//    void autoCal(float pesoReal) {
//        float temp = 0;
//        velocidadMasa = (float)calFactor * pesoReal;
//        numCortes = tempNumCortes;
//        kgXcorte = tempkgXcorte;
//        temp = (float)diamTubo / 2000.0f;
//        temp *= temp;
//        temp *= pi;
//        temp *= velocidadMasa;
//        if(tVarProceso == tvp_kg) {
//            temp *= densidadMasa;
//            tiXcorte = (float)kgXcorte / temp;
//        }else if(tVarProceso == tvp_m)
//            tiXcorte = (float)m3Xcorte / temp;
//        timsXcorte = (float)tiXcorte * 1000;
//        saveSysParams();
//    }
    
    
    
    void sysParamInit() {
//        tVarProceso = readEEPROM(1);
        fData.floatMB = readEEPROM(2);
        fData.floatUB = readEEPROM(3);
        fData.floatHB = readEEPROM(4);
        fData.floatLB = readEEPROM(5);
        tiXcorte = fData.floatdat; //2-5
        i16Data.int16HB = readEEPROM(6);
        i16Data.int16LB = readEEPROM(7);
        numCortes = i16Data.int16dat; //6-7
        fData.floatMB = readEEPROM(8);
        fData.floatUB = readEEPROM(9);
        fData.floatHB = readEEPROM(10);
        fData.floatLB = readEEPROM(11);
        diamTubo = fData.floatdat; //8-11
//        fData.floatMB = readEEPROM(12);
//        fData.floatUB = readEEPROM(13);
//        fData.floatHB = readEEPROM(14);
//        fData.floatLB = readEEPROM(15);
//        densidadMasa = fData.floatdat; //12-15
        fData.floatMB = readEEPROM(16);
        fData.floatUB = readEEPROM(17);
        fData.floatHB = readEEPROM(18);
        fData.floatLB = readEEPROM(19);
        velocidadMasa = fData.floatdat; //16-19
        calcSysVars();
    }
    

#ifdef	__cplusplus
}
#endif

#endif	/* SYSPARAMS_H */

