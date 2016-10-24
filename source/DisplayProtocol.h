#ifndef DISPLAYPROTOCOL_H
#define	DISPLAYPROTOCOL_H

#include "sysParams.h"
#include "IOConfig.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
    #define SCREEN_MENU         0
    #define SCREEN_PASSWORD     1
    #define SCREEN_ON_PROCESS   2
    #define SCREEN_OFF_PROCESS  3   
    #define SCREEN_MENU_ADV     4   
    #define SCREEN_CHAN_VAL     5   
    #define SCREEN_CALIB_VEL    6

    signed char actualScreen = SCREEN_MENU ;
    signed char menuSection = 0;
    signed char passSection = 0;
    char contra[4] = {1,2,3,4};
    char introducido[4] = {0,0,0,0};
    char advMode = 0;
    
    void pressUP() {
        if(actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            menuSection++;
            if(menuSection > 6)
                menuSection = 0;
        }
    }
    
    void longPressUP() {
//        if(!UPisLP) {
//            UPisLP = 1;
        if(actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            if(holdENTERcont > 5) {
                if(actualScreen == SCREEN_MENU) {
                    actualScreen = SCREEN_PASSWORD;
                    passSection = 0;
                }
                if(actualScreen == SCREEN_MENU_ADV)
                    actualScreen = SCREEN_MENU;
            }else
                menuSection = 0;
        }else if(actualScreen == SCREEN_PASSWORD) {
            
            introducido[passSection]++;
            if(introducido[passSection] > 6)
                introducido[passSection] = 0;
        }
        
//        }
    }
    
    void releaseUP() {
        UPisLP = 0;
        UPsecurLock = 0;
    }
    
    void pressDOWN() {
        if(actualScreen == SCREEN_MENU || actualScreen == SCREEN_MENU_ADV) {
            menuSection--;
            if(menuSection < 0)
                menuSection = 6;
        }
    }
    
    void longPressDOWN() {
//        if(!DOWNisLP) {
//            DOWNisLP = 1;
            
//        }
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
        if(!ENTERisLP) {
            ENTERisLP = 1;
            if(holdUPcont > 5) {
               if(actualScreen == SCREEN_MENU)
                   actualScreen = SCREEN_PASSWORD;
               if(actualScreen == SCREEN_MENU_ADV)
                   actualScreen = SCREEN_MENU;
           }else {
               actualScreen = SCREEN_ON_PROCESS;
           }
        }
    }
    
    void releaseENTER() {
        ENTERisLP = 0;
        ENTERsecurLock = 0;
    }
    
    void execCombinations() {
        if(ENTERisLP) {
           
        }
        if(UPisLP) {
           
        }
    }
    
    void drawMenu() {
        switch(menuSection) {
            case (0): {
                lcd_gotoxy(1,1);
                printf("Estado proceso: \n");
                if(proceso > 0) {
                    printf("    %us / %us   ", proceso, numCortes);
                }else
                    printf("     Detenido     ");
                break;
            }case (1): {
                lcd_gotoxy(1,1);
                printf("Proceso en:     \n");
                switch(tVarProceso) {
                    case (tvp_kg): {
                        printf("       kg       ");
                        break;
                    }
                    case (tvp_m3): {
                        printf("       m3       ");
                        break;
                    }
                    case (tvp_ti): {
                        printf("       sec      ");
                        break;
                    }
                }
                break;
            }case (2): {
                lcd_gotoxy(1,1);
                printf("Valor por Corte:\n");
                switch(tVarProceso) {
                    case (tvp_kg): {
                        printf("       %f kg    ",kgXcorte);
                        break;
                    }
                    case (tvp_m3): {
                        printf("       %f m3    ",kgXcorte);
                        break;
                    }
                    case (tvp_ti): {
                        printf("       %f sec   ",kgXcorte);
                        break;
                    }
                }
                break;
            }case (3): {
                lcd_gotoxy(1,1);
                printf("Cantidad Cortes:\n");
                printf("       %us       ",numCortes);
                break;
            }case (4): {
                lcd_gotoxy(1,1);
                printf("Diametro Tubo:  \n");
                printf("      %f mm     ",diamTubo);
                break;
            }case (5): {
                lcd_gotoxy(1,1);
                printf("Densidad Masa:  \n");
                printf("     %f kg/m3   ", densidadMasa);
                break;
            }case (6): {
                lcd_gotoxy(1,1);
                printf("Velocidad Masa: \n");
                printf("     %f m/s     ",velocidadMasa);
                break;
            }
        }
        
    }
    
    void drawPassWord() {
        lcd_gotoxy(1,1);
        printf("Contrasena:\n");
        printf("    %u%u%u%u    ", introducido[0], introducido[1],
                introducido[2], introducido[3]);        
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

