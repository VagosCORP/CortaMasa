#ifndef DISPLAYPROTOCOL_H
#define	DISPLAYPROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    #define SCREEN_MENU         0
    #define SCREEN_PASSWORD     1
    #define SCREEN_ON_PROCESS   2
    #define SCREEN_OFF_PROCESS  3   
//    #define SCREEN_MENU_ADV     4   
    #define SCREEN_CHAN_VAL     4   
    #define SCREEN_CALIB_VEL    5

    signed char actualScreen = SCREEN_MENU ;
    signed char menuSection = 0;
    char introducido = 128;
    char advMode = 0;
    
    void pressUP() {
        if(actualScreen == SCREEN_MENU) {
            menuSection++;
            if(menuSection > 5)
                menuSection = 0;
        }
    }
    
    void longPressUP() {
        if(!UPisLP) {
            UPisLP = 1;
        }
    }
    
    void releaseUP() {
        UPisLP = 0;
        UPsecurLock = 0;
    }
    
    void pressDOWN() {
        if(actualScreen == SCREEN_MENU) {
            menuSection--;
            if(menuSection < 0)
                menuSection = 5;
        }
    }
    
    void longPressDOWN() {
        if(!DOWNisLP) {
            DOWNisLP = 1;
        }
    }
    
    void releaseDOWN() {
        DOWNisLP = 0;
        DOWNsecurLock = 0;
    }
    
    void pressRETRO() {
        
    }
    
    void longPressRETRO() {
        if(!RETROisLP) {
            RETROisLP = 1;
        }
    }
    
    void releaseRETRO() {
        RETROisLP = 0;
        RETROsecurLock = 0;
    }
    
    void pressENTER() {
        
    }
    
    void longPressENTER() {
        ENTERisLP = 1;
    }
    
    void releaseENTER() {
        ENTERisLP = 0;
        ENTERsecurLock = 0;
    }
    
    void execCombinations() {
        if(ENTERisLP) {
           if(UPisLP) {
               actualScreen = SCREEN_PASSWORD;
           }else {
               actualScreen = SCREEN_ON_PROCESS;
           }
        }
    }
    
    void drawMenu() {
        switch(menuSection) {
            case (0): {
                lcd_gotoxy(1,1);
                printf("Estado proceso: \n");
                printf("     Detenido     ");
                break;
            }case (1): {
                lcd_gotoxy(1,1);
                printf("Proceso en:     \n");
                printf("        kg        ");
                break;
            }case (2): {
                lcd_gotoxy(1,1);
                printf("Valor por Corte:\n");
                printf("        0.1       ");
                break;
            }case (3): {
                lcd_gotoxy(1,1);
                printf("Cantidad Cortes:\n");
                printf("        10        ");
                break;
            }case (4): {
                lcd_gotoxy(1,1);
                printf("Diámetro Tubo:  \n");
                printf("       20mm       ");
                break;
            }case (5): {
                lcd_gotoxy(1,1);
                printf("Densidad Masa:  \n");
                printf("     1.5 kg/m3    ");
                break;
            }case (6): {
                lcd_gotoxy(1,1);
                printf("Velocidad Masa: \n");
                printf("      0.5 m/s     ");
                break;
            }
        }
        
    }
    
    void drawPassWord() {
        lcd_gotoxy(1,1);
        printf("Contraseña:\n");
        printf("XXXX = %u", introducido);        
    }
    
    void drawScreen() {
        switch(actualScreen) {
            case (SCREEN_MENU): {
                drawMenu();
                break;
            }case (SCREEN_PASSWORD): {
                drawPassWord();
                break;
            }
        }
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
     * contraseña de 6 dígitos visibles
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

