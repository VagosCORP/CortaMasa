#ifndef DISPLAYPROTOCOL_H
#define	DISPLAYPROTOCOL_H

#include "sysParams.h"
#include "IOConfig.h"
#include "screenDrawers.h"

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
    
    void confirmEdition(char yes) {
        switch (menuSection) {
            case (0): {
                break;
            }case (1): {
                if(yes) {
                    tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }case (2): {
                if(yes) {
//                        tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }case (3): {
                if(yes) {
//                        tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }case (4): {
                if(yes) {
//                        tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }case (5): {
                if(yes) {
//                        tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }case (6): {
                if(yes) {
//                        tVarProceso = selKMT;
                    actualScreen = SCREEN_MENU_ADV;
                    saveSysParams();
                }else {
                    tempLastScreen = actualScreen;
                    actualScreen = SCREEN_SAVE_ALL;
                    selSN = NO;
                }
                break;
            }
        }
    }

    void pressUP() {
        if (actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            menuSection++;
            if (menuSection > 6)
                menuSection = 0;
        } else if (actualScreen == SCREEN_PASSWORD) {
            introducido[passSection]++;
            if (introducido[passSection] > 9)
                introducido[passSection] = 0;
        } else if (actualScreen == SCREEN_ON_PROCESS || actualScreen == SCREEN_OFF_PROCESS
                || actualScreen == SCREEN_SAVE_ALL) {
            selSN = !selSN;
            if(selSN > 1)
                selSN = 0;
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            switch (menuSection) {
                case (0): {
                    break;
                }case (1): {
                    selKMT++;
                    if(selKMT > 2)
                        selKMT = 0;
                    break;
                }case (2): {
                    
                    break;
                }case (3): {
                    
                    break;
                }case (4): {
                    
                    break;
                }case (5): {
                    
                    break;
                }case (6): {
                    
                    break;
                }
            }
        }
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
                menuSection = 6;
        } else if (actualScreen == SCREEN_PASSWORD) {
            introducido[passSection]--;
            if (introducido[passSection] < 0)
                introducido[passSection] = 9;
        } else if (actualScreen == SCREEN_ON_PROCESS || actualScreen == SCREEN_OFF_PROCESS
                || actualScreen == SCREEN_SAVE_ALL) {
            selSN = !selSN;
            if(selSN > 1)
                selSN = 0;
        }else if(actualScreen == SCREEN_CHAN_VAL) {
            switch (menuSection) {
                case (0): {
                    break;
                }case (1): {
                    selKMT--;
                    if(selKMT < 0)
                        selKMT = 2;
                    break;
                }case (2): {
                    
                    break;
                }case (3): {
                    
                    break;
                }case (4): {
                    
                    break;
                }case (5): {
                    
                    break;
                }case (6): {
                    
                    break;
                }
            }
        }
    }

    void longPressDOWN() {
        if (!DOWNisLP) {
            DOWNisLP = 1;

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
                || actualScreen == SCREEN_SAVE_ALL)
            actualScreen = tempLastScreen;
        else if(actualScreen == SCREEN_CHAN_VAL)
            actualScreen = SCREEN_MENU_ADV;
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
            }
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
                case (0): {
                    tempLastScreen = actualScreen;
                    if(ProcessStarted) {
                        actualScreen = SCREEN_OFF_PROCESS;
                        selSN = SI;
                    }else {
                        actualScreen = SCREEN_ON_PROCESS;
                        selSN = NO;
                    }
                    break;
                }case (1): {
                    tempLastScreen = actualScreen;
                    selKMT = tVarProceso;
                    actualScreen = SCREEN_CHAN_VAL;
                    break;
                }case (2): {
                    
                    break;
                }case (3): {
                    
                    break;
                }case (4): {
                    
                    break;
                }case (5): {
                    
                    break;
                }case (6): {
                    
                    break;
                }
            }
        }else if(actualScreen == SCREEN_BAD_PASS)
            actualScreen = SCREEN_PASSWORD;
        else if(actualScreen == SCREEN_CALIB_VEL) {
            
        }else if(actualScreen == SCREEN_CHAN_VAL)
            confirmEdition(!ProcessStarted);
        else if(actualScreen == SCREEN_ON_PROCESS) {
            ProcessStarted = !selSN; //SI = 0
            actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_OFF_PROCESS) {
            ProcessStarted = selSN; //SI = 0
            actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_SAVE_ALL) {
            if(!selSN)
                confirmEdition(1);
            else
                actualScreen = tempLastScreen;
        }else if(actualScreen == SCREEN_ADVMODE_ON)
            actualScreen = SCREEN_MENU_ADV;
        else if(actualScreen == SCREEN_ADVMODE_OFF)
            actualScreen = SCREEN_MENU;
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
            }
        }
    }

    void releaseENTER() {
        ENTERisLP = 0;
        ENTERsecurLock = 0;
    }

    /*
     * Estado del proceso: X/Y Cortes / Detenido
     * Proceso medido en: kg / m^3 / tiempo
     * Número de cortes a realizar: medido en cortes
     * Diámetro de tubo: medido en mm
     * Densidad de la Masa: Medida en kg/m^3
     * Velocidad de la masa: en m/s 
     */

    /*
     * Por favor introduzca la contraseña
     * contraseña de 4 dígitos visibles
     */

    /*
     * Iniciar Proceso
     * SI / NO (Por defecto en NO)
     */

    /*
     * Cancelar Proceso
     * X / Y, SI / NO (Por defecto en SI)
     */

    /*
     * Label Variable
     * Valor deseado cambieable con UP/DOWN, enter para aceptar
     */

    /*
     * Autocalibrar velocidad de la Masa: SI / NO (Por defecto en SI)
     * Diámetro de tubo: medido en mm
     * Densidad Masa: Medida en kg/m^3
     * 10 cortes x 100g
     */


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAYPROTOCOL_H */

