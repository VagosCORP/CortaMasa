#ifndef SCREENDRAWERS_H
#define	SCREENDRAWERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "sysParams.h"
    #include "UARTConfig.h"


    #define SCREEN_MENU         0
    #define SCREEN_PASSWORD     1
    #define SCREEN_ON_PROCESS   2
    #define SCREEN_OFF_PROCESS  3   
    #define SCREEN_MENU_ADV     4   
    #define SCREEN_CHAN_VAL     5   
    #define SCREEN_CALIB_PROCESS    6
    #define SCREEN_BAD_PASS     7   
    #define SCREEN_ADVMODE_ON   8
    #define SCREEN_ADVMODE_OFF  9
    #define SCREEN_SAVE_ALL    10
    #define SCREEN_CALIB_INIT   11
    #define SCREEN_CALIB_RMAS  12

    #define MENU_ESTADO         0
    #define MENU_VALP_CUT       1
    #define MENU_CANT_CUT       2   
    #define MENU_DIAM_TUB       3   
    #define MENU_VEL_MAS        4   
//    #define MENU_DENS_MAS       5
//    #define MENU_TIP_VAR        6

    #define SI                  0
    #define NO                  1

    signed char actualScreen = SCREEN_MENU;
    signed char menuSection = 0;
    signed char passSection = 0;
    signed char chanValSection = 5;
    char contra[4] = {0,0,0,0};//{1, 2, 3, 4};
    signed char introducido[4] = {0, 0, 0, 0};
    char passChar[4] = {0, 0, 0, 0};
    char questKMT[3] = {0, 0, 0};
    signed char selKMT = 0;
    float chanValf = 000.000f;
    short chanVals = 0;
    signed char chanValdig[6] = {0,0,0,0,0,0};
    char chanValChar[6] = {0, 0, 0, 0, 0, 0};
    long exp10[6] = {100000,10000,1000,100,10,1};
    char questSN[2] = {0, 0};
    char selSN = 0;
    char fd = 0;
    char tempLastScreen = 0;
    char screen_calibVelRes = 0;
    char flech = 0b01111110;
    char calibLevel = 0;
    
    void drawValEditor() {
        if(chanValSection == 5) {
            printf(" %u%u%u.%u%u%c%u ", chanValdig[0], chanValdig[1],
                chanValdig[2], chanValdig[3], chanValdig[4], flech, chanValdig[5]);
        }else if(chanValSection == 4) {
            printf(" %u%u%u.%u%c%u%u ", chanValdig[0], chanValdig[1],
                chanValdig[2], chanValdig[3], flech, chanValdig[4], chanValdig[5]);
        }else if(chanValSection == 3) {
            printf(" %u%u%u.%c%u%u%u ", chanValdig[0], chanValdig[1],
                chanValdig[2], flech, chanValdig[3], chanValdig[4], chanValdig[5]);
        }else if(chanValSection == 2) {
            printf(" %u%u%c%u.%u%u%u ", chanValdig[0], chanValdig[1], flech,
                chanValdig[2], chanValdig[3], chanValdig[4], chanValdig[5]);
        }else if(chanValSection == 1) {
            printf(" %u%c%u%u.%u%u%u ", chanValdig[0], flech, chanValdig[1],
                chanValdig[2], chanValdig[3], chanValdig[4], chanValdig[5]);
        }else if(chanValSection == 0) {
            printf(" %c%u%u%u.%u%u%u ", flech, chanValdig[0], chanValdig[1],
                chanValdig[2], chanValdig[3], chanValdig[4], chanValdig[5]);
        }
        lcd_gotoxy(11, 2);
    }
    
//    void drawValEditors() {
//        printf("  %u%u%u.%u%u%u ", chanValdig[0], chanValdig[1],
//                chanValdig[2], chanValdig[3], chanValdig[4], chanValdig[5]);
//        lcd_gotoxy(11, 2);
//    }
    
    void drawMenu(char adv) {
        switch (menuSection) {
            case (MENU_ESTADO): {
                lcd_gotoxy(1, 1);
                printf("Estado proceso: \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                if (ProcessStarted)
                    printf("   %d / %d    ", processState, numCortes);
                else
                    printf("    Detenido    ");
                break;
            }case (MENU_VALP_CUT): {
                lcd_gotoxy(1, 1);
                printf("Valor por Corte:\n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("   %3.3f kg   ", kgXcorte);
                break;
            }case (MENU_CANT_CUT): {
                lcd_gotoxy(1, 1);
                printf("Cantidad Cortes:\n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("      %d       ", numCortes);
                break;
            }case (MENU_DIAM_TUB): {
                lcd_gotoxy(1, 1);
                printf("Diametro Tubo:  \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("   %3.3f mm   ", diamTubo);
                break;
            }case (MENU_VEL_MAS): {
                lcd_gotoxy(1, 1);
                printf("Velocidad Masa: \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("  %3.3f kg/s  ", velocidadMasa);
                break;
            }
        }
    }

    void drawChanVal() {
        switch (menuSection) {
            case (MENU_ESTADO): {
                break;
            }case (MENU_VALP_CUT): {
                lcd_gotoxy(1, 1);
                printf("Valor por Corte:\n");
                drawValEditor();
                printf("kg    ");
                break;
            }case (MENU_CANT_CUT): {
                lcd_gotoxy(1, 1);
                printf("Cantidad Cortes:\n");
                printf("      %d       ", chanVals);
                break;
            }case (MENU_DIAM_TUB): {
                lcd_gotoxy(1, 1);
                printf("Diametro Tubo:  \n");
                drawValEditor();
                printf("mm    ");
                break;
            }case (MENU_VEL_MAS): {
                break;
            }
        }
    }
    
    void drawPass1Lin() {
        lcd_gotoxy(1, 1);
        printf("Contrasena:     \n");
    }

    void drawPassWord() {
        if (!fd) {
            passSection = 0;
            introducido[0] = 0;
            introducido[1] = 0;
            introducido[2] = 0;
            introducido[3] = 0;
            fd = 1;
        }
        int i;
        for (i = 0; i < 4; i++)
            passChar[i] = ' ';
        passChar[passSection] = flech;
        drawPass1Lin();
        printf("    %c%u%c%u%c%u%c%u    ", passChar[0], introducido[0], passChar[1], introducido[1],
                passChar[2], introducido[2], passChar[3], introducido[3]);
    }

    void drawBadPass() {
        drawPass1Lin();
        printf("     Erronea    ");
    }

    void drawAdvON(char on) {
        lcd_gotoxy(1, 1);
        printf("Modo Configurar:\n");
        if(on)
            printf("    Iniciado    ");
        else
            printf("   Finalizado   ");
    }

    void drawSNquest(char tq) {
        int i;
        for (i = 0; i < 2; i++)
            questSN[i] = ' ';
        questSN[selSN] = flech;
        lcd_gotoxy(1, 1);
        if (tq == 0)
            printf("Iniciar Proceso?\n");
        else if(tq == 1)
            printf("Detener Proceso?\n");
        else if(tq == 2)
            printf("Guardar Cambio? \n");
        else if(tq == 3)
            printf("Init AutoCalib? \n");
        printf("   %cSI    %cNO   ", questSN[0], questSN[1]);
    }
    
    void drawAutoCalibRM() {
        lcd_gotoxy(1, 1);
        printf("Peso Real:      \n");
        drawValEditor();
        printf("kg    ");
    }
    
    void drawCalibProc() {
        lcd_gotoxy(1, 1);    
        if(calibLevel == 0) {
            printf("Autocalib usando\n");
            printf("       1 kg     ");
        }else if(calibLevel == 1) {
            printf("Autocalib usando\n");
            printf("     0.5 kg     ");
        }else if(calibLevel == 2) {
            printf("Autocalib usando\n");
            printf("    0.25 kg     ");
        }
    }

    void drawScreen() {
        switch (actualScreen) {
            case (SCREEN_MENU): {
                drawMenu(0);
                break;
            }case (SCREEN_PASSWORD): {
                drawPassWord();
                break;
            }case (SCREEN_BAD_PASS): {
                drawBadPass();
                break;
            }case (SCREEN_MENU_ADV): {
                drawMenu(1);
                break;
            }case (SCREEN_ADVMODE_ON):  {
                drawAdvON(1);
                break;
            }case (SCREEN_ADVMODE_OFF): {
                drawAdvON(0);
                break;
            }case (SCREEN_CHAN_VAL): {
                drawChanVal();
                break;
            }case (SCREEN_ON_PROCESS): {
                drawSNquest(0);
                break;
            }case (SCREEN_OFF_PROCESS): {
                drawSNquest(1);
                break;
            }case (SCREEN_SAVE_ALL): {
                drawSNquest(2);
                break;
            }case (SCREEN_CALIB_INIT): {
                drawSNquest(3);                
                break;
            }case (SCREEN_CALIB_PROCESS): {
                drawCalibProc();
                break;
            }case (SCREEN_CALIB_RMAS): {
                drawAutoCalibRM();
                break;
            }
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* SCREENDRAWERS_H */