#ifndef DISPLAYPROTOCOL_H
#define	DISPLAYPROTOCOL_H

#include "sysParams.h"
#include "IOConfig.h"
#include "screenDrawers.h"
#include "PWMConfig.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

    char checkPass() {
        int i;
        char passOK = 0;
        for (i = 0; i < 4; i++) {
            if (introducido[i] == contra[i])
                passOK = 1;
            else {
                passOK = 0;
                break;
            }
        }
        return passOK;
    }
    
    void chanValDigUP() {
        chanValdig[chanValSection]++;
        if(chanValdig[chanValSection] > 9) {
            chanValdig[chanValSection] = 0;
            if(chanValSection > 1 && chanValdig[chanValSection - 1] < 9)
                chanValdig[chanValSection - 1]++;
        }
    }
    
    void chanValDigDOWN() {
        chanValdig[chanValSection]--;
        if(chanValdig[chanValSection] < 0) {
            chanValdig[chanValSection] = 9;
            if(chanValSection > 1 && chanValdig[chanValSection - 1] > 0)
                chanValdig[chanValSection - 1]--;
        }
    }
    
    void desintegrator() {
        chanValSection = 5;
        float temp = (float)chanValf*1000;
        long tempL = (long)temp;
        long temp2 = 0;
        long temp3 = 0;
        int i;
        for(i = 0; i < 6; i++) {
            temp2 = tempL/exp10[i];
            temp3 = temp2*exp10[i];
            chanValdig[i] = temp2;
            tempL -= temp3;
        }
    }
    
    void integrator() {
        long acum = 0;
        long temp = 0;
        int i;
        for(i = 0; i < 6; i++) {
            temp = (long)chanValdig[i]*exp10[i];
            acum += temp;
        }
        chanValf = (float)acum / 1000;
    }
    
    void confirmEdition(char yes) {
        switch (menuSection) {
            case (MENU_ESTADO): {
                break;
            }case (MENU_VALP_CUT): {
                if(yes) {
                    kgXcorte = chanValf;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    selSN = NO;
                    actualScreen = SCREEN_SAVE_ALL;
                }
                break;
            }case (MENU_CANT_CUT): {
                if(yes) {
                    numCortes = chanVals;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    selSN = NO;
                    actualScreen = SCREEN_SAVE_ALL;
                }
                break;
            }case (MENU_DIAM_TUB): {
                if(yes) {
                    diamTubo = chanValf;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    selSN = NO;
                    actualScreen = SCREEN_SAVE_ALL;
                }
                break;
            }case (MENU_VEL_MAS): {
                if(yes) {
                    velocidadMasa = chanValf;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    selSN = NO;
                    actualScreen = SCREEN_SAVE_ALL;
                }
                break;
            }
        }
    }

    void pressUP() {
        if (actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            menuSection++;
            if (menuSection > 4)
                menuSection = 0;
        } else if (actualScreen == SCREEN_PASSWORD) {
            introducido[passSection]++;
            if (introducido[passSection] > 9)
                introducido[passSection] = 0;
        } else if (actualScreen == SCREEN_ON_PROCESS || actualScreen == SCREEN_OFF_PROCESS
                || actualScreen == SCREEN_SAVE_ALL || actualScreen == SCREEN_CALIB_INIT) {
            selSN = !selSN;
            if(selSN > 1)
                selSN = 0;
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            switch (menuSection) {
                case (MENU_ESTADO): {
                    break;
                }case (MENU_VALP_CUT): {
                    chanValDigUP();
                    break;
                }case (MENU_CANT_CUT): {
                    chanVals++;
                    break;
                }case (MENU_DIAM_TUB): {
                    chanValDigUP();
                    break;
                }
            }
        }else if(actualScreen == SCREEN_CALIB_RMAS)
            chanValDigUP();
    }

    void longPressUP() {
        if (!UPisLP) {
            UPisLP = 1;
            if (actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
                if (holdENTERcont > 5) {
                    if (actualScreen == SCREEN_MENU) {
                        actualScreen = SCREEN_PASSWORD;
                        fd = 0;
                    } else if (actualScreen == SCREEN_MENU_ADV)
                        actualScreen = SCREEN_ADVMODE_OFF;
                } else
                    menuSection = 0;
            }else if(actualScreen == SCREEN_CHAN_VAL) {
                if(menuSection == MENU_CANT_CUT)
                    chanVals += 10;
            }
        }
    }

    void releaseUP() {
        UPisLP = 0;
        UPsecurLock = 0;
    }

    void pressDOWN() {
        if (actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            menuSection--;
            if (menuSection < 0)
                menuSection = 4;
        } else if (actualScreen == SCREEN_PASSWORD) {
            introducido[passSection]--;
            if (introducido[passSection] < 0)
                introducido[passSection] = 9;
        } else if (actualScreen == SCREEN_ON_PROCESS || actualScreen == SCREEN_OFF_PROCESS
                || actualScreen == SCREEN_SAVE_ALL || actualScreen == SCREEN_CALIB_INIT) {
            selSN = !selSN;
            if(selSN > 1)
                selSN = 0;
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            switch (menuSection) {
                case (MENU_ESTADO): {
                    break;
                }case (MENU_VALP_CUT): {
                    chanValDigDOWN();
                    break;
                }case (MENU_CANT_CUT): {
                    chanVals--;
                    break;
                }case (MENU_DIAM_TUB): {
                    chanValDigDOWN();
                    break;
                }
            }
        }else if(actualScreen == SCREEN_CALIB_RMAS)
            chanValDigDOWN();
    }

    void longPressDOWN() {
        if (!DOWNisLP) {
            DOWNisLP = 1;
            if(actualScreen == SCREEN_CHAN_VAL) {
                if(menuSection == MENU_CANT_CUT)
                    chanVals -= 10;
            }
        }
    }

    void releaseDOWN() {
        DOWNisLP = 0;
        DOWNsecurLock = 0;
    }

    void pressRETRO() {
        if (actualScreen == SCREEN_PASSWORD) {
            actualScreen = SCREEN_MENU;
        }else if (actualScreen == SCREEN_ON_PROCESS || actualScreen == SCREEN_OFF_PROCESS
                || actualScreen == SCREEN_SAVE_ALL) {
            actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            if(menuSection != MENU_CANT_CUT) {
                chanValSection++;
                if(chanValSection > 5)
                    chanValSection = 0;
            }else
                actualScreen = SCREEN_MENU_ADV;
        }else if(actualScreen == SCREEN_CALIB_INIT)
            actualScreen = SCREEN_MENU_ADV;
        else if(actualScreen == SCREEN_CALIB_RMAS) {
            chanValSection++;
            if(chanValSection > 5)
                chanValSection = 0;
        }
        
    }

    void longPressRETRO() {
        if (!RETROisLP) {
            RETROisLP = 1;
            if(actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
                if(ProcessStarted) {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_OFF_PROCESS;
                    selSN = SI;
                }
            }else if(actualScreen == SCREEN_CHAN_VAL)
                actualScreen = SCREEN_MENU_ADV;
            else if(actualScreen == SCREEN_CALIB_RMAS)
                actualScreen = SCREEN_MENU_ADV;
        }
    }

    void releaseRETRO() {
        RETROisLP = 0;
        RETROsecurLock = 0;
    }

    void pressENTER() {
        if (actualScreen == SCREEN_PASSWORD) {
            passSection++;
            if (passSection > 3) {
                passSection = 0;
                if (checkPass())
                    actualScreen = SCREEN_ADVMODE_ON;
                else
                    actualScreen = SCREEN_BAD_PASS;
            }
        }else if(actualScreen == SCREEN_MENU_ADV) {
            switch (menuSection) {
                case (MENU_ESTADO): {
                    tempLastScreen = actualScreen;
                    if(ProcessStarted) {
                        actualScreen = SCREEN_OFF_PROCESS;
                        selSN = SI;
                    }else {
                        actualScreen = SCREEN_ON_PROCESS;
                        selSN = NO;
                    }
                    break;
                }case (MENU_VALP_CUT): {
                    chanValf = kgXcorte;
                    desintegrator();
                    actualScreen = SCREEN_CHAN_VAL;
                    break;
                }case (MENU_CANT_CUT): {
                    tempLastScreen = actualScreen;
                    chanVals = numCortes;
                    actualScreen = SCREEN_CHAN_VAL;
                    break;
                }case (MENU_DIAM_TUB): {
                    chanValf = diamTubo;
                    desintegrator();
                    actualScreen = SCREEN_CHAN_VAL;
                    break;
                }case (MENU_VEL_MAS): {
                    if(!ProcessStarted) {
                        tempLastScreen = actualScreen;
                        selSN = NO;
                        actualScreen = SCREEN_CALIB_INIT;
                    }
                    break;
                }
            }
        }else if(actualScreen == SCREEN_BAD_PASS)
            actualScreen = SCREEN_PASSWORD;
        else if(actualScreen == SCREEN_CALIB_PROCESS) {
            
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            if(menuSection != MENU_CANT_CUT) {
                chanValSection--;
                if(chanValSection < 0)
                    chanValSection = 5;
            }else
                confirmEdition(!ProcessStarted);
        }else if(actualScreen == SCREEN_ON_PROCESS) {
            ProcessStarted = !selSN; //SI = 0
            if(!FC1)
                bladeIsUP = 2;
            if(ProcessStarted) {
                processState = 0;
                if(bladeIsUP != 1)
                    setPWM2duty(-400);
            }
            actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_OFF_PROCESS) {
            ProcessStarted = selSN; //SI = 0
            actualScreen = tempLastScreen;
            REL = 0;
            if(bladeIsUP != 1)
                setPWM2duty(-400);
        }else if(actualScreen == SCREEN_SAVE_ALL) {
            if(!selSN)
                confirmEdition(1);
            else
                actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_ADVMODE_ON)
            actualScreen = SCREEN_MENU_ADV;
        else if(actualScreen == SCREEN_ADVMODE_OFF)
            actualScreen = SCREEN_MENU;
        else if(actualScreen == SCREEN_CALIB_INIT) {
            if(!selSN) {
                chanValf = 0;
                desintegrator();
                temptiXcorte = tiXcorte;
                tiXcorte = 5.0f;
                timsXcorte = 5000.0f;
                tempNumCortes = numCortes;
                numCortes = 1;
                processState = 0;
                processTimer = 0;
                if(!FC1)
                    bladeIsUP = 2;
                ProcessStarted = 1;
                if(ProcessStarted && bladeIsUP != 1) {
                    processState = 0;
                    setPWM2duty(-400);
                }
                calibLevel = 0;
                actualScreen = SCREEN_CALIB_PROCESS;
            }else
                actualScreen = SCREEN_MENU_ADV;
        }else if(actualScreen == SCREEN_CALIB_RMAS) {
            chanValSection--;
            if(chanValSection < 0)
                chanValSection = 5;
        }
        
    }

    void longPressENTER() {
        if (!ENTERisLP) {
            ENTERisLP = 1;
            if(actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
                if (holdUPcont > 5) {
                    if (actualScreen == SCREEN_MENU) {
                        actualScreen = SCREEN_PASSWORD;
                        fd = 0;
                    } else if (actualScreen == SCREEN_MENU_ADV)
                        actualScreen = SCREEN_ADVMODE_OFF;
                } else if(!ProcessStarted) {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_ON_PROCESS;
                    selSN = NO;
                }
            }else if(actualScreen == SCREEN_CHAN_VAL) {
                if(menuSection != MENU_CANT_CUT)
                    integrator();
                confirmEdition(!ProcessStarted);
            }else if(actualScreen == SCREEN_CALIB_RMAS) {
                integrator();
                if(calibLevel == 0) {
                    tempVelocidadMasa1 = (float)chanValf / tiXcorte;
                    tiXcorte = (float)0.5 / tempVelocidadMasa1;
                    calibLevel = 1;
                    numCortes = 1;
                    processState = 0;
                    processTimer = 0;
                    if(!FC1)
                        bladeIsUP = 2;
                    ProcessStarted = 1;
                    if(ProcessStarted && bladeIsUP != 1) {
                        processState = 0;
                        setPWM2duty(-400);
                    }
                    actualScreen = SCREEN_CALIB_PROCESS;
                }else if(calibLevel == 1) {
                    tempVelocidadMasa2 = (float)chanValf / tiXcorte;
                    tiXcorte = (float)0.25 / tempVelocidadMasa2;
                    calibLevel = 2;
                    numCortes = 1;
                    processState = 0;
                    processTimer = 0;
                    if(!FC1)
                        bladeIsUP = 2;
                    ProcessStarted = 1;
                    if(ProcessStarted && bladeIsUP != 1) {
                        processState = 0;
                        setPWM2duty(-400);
                    }
                    actualScreen = SCREEN_CALIB_PROCESS;
                }else if(calibLevel == 2) {
                    tempVelocidadMasa3 = (float)chanValf / tiXcorte;
                    float temp = (float)tempVelocidadMasa1 + tempVelocidadMasa2+ tempVelocidadMasa3;
                    chanValf = (float)temp / 3.0f;
                    numCortes = tempNumCortes;
                    calcVars2ti();
                    confirmEdition(!ProcessStarted);
                }
            }
        }
    }

    void releaseENTER() {
        ENTERisLP = 0;
        ENTERsecurLock = 0;
    }


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAYPROTOCOL_H */

