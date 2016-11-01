#ifndef SCREENDRAWERS_H
#define	SCREENDRAWERS_H

#include "sysParams.h"

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
#define SCREEN_BAD_PASS     7   
#define SCREEN_ADVMODE_ON   8
#define SCREEN_ADVMODE_OFF  9
#define SCREEN_SAVE_ALL    10

#define MENU_ESTADO         0
#define MENU_TIP_VAR        1
#define MENU_VALP_CUT       2
#define MENU_CANT_CUT       3   
#define MENU_DIAM_TUB       4   
#define MENU_DENS_MAS       5   
#define MENU_VEL_MAS        6
    
#define SI                  0
#define NO                  1

    signed char actualScreen = SCREEN_MENU;
    signed char menuSection = 0;
    signed char passSection = 0;
    char contra[4] = {1, 2, 3, 4};
    signed char introducido[4] = {0, 0, 0, 0};
    char passChar[4] = {0, 0, 0, 0};
    char questKMT[3] = {0, 0, 0};
    signed char selKMT = 0;
    char questSN[2] = {0, 0};
    char selSN = 0;
    char fd = 0;
    char tempLastScreen = 0;

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
                    printf("   %d / %d    ", proceso, numCortes);
                else
                    printf("    Detenido    ");
                break;
            }case (MENU_TIP_VAR): {
                lcd_gotoxy(1, 1);
                printf("Proceso en:     \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                if(tVarProceso == tvp_kg)
                    printf("       kg        ");
                else if(tVarProceso == tvp_m3)
                    printf("       m3       ");
                else if(tVarProceso == tvp_ti)
                    printf("      sec       ");
                break;
            }case (MENU_VALP_CUT): {
                lcd_gotoxy(1, 1);
                printf("Valor por Corte:\n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                if(tVarProceso == tvp_kg)
                    printf("   %3.3f kg   ", kgXcorte);
                else if(tVarProceso == tvp_m3)
                    printf("   %3.3f m3   ", m3Xcorte);
                else if(tVarProceso == tvp_ti)    
                    printf("   %3.3f sec  ", tiXcorte);
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
            }case (MENU_DENS_MAS): {
                lcd_gotoxy(1, 1);
                printf("Densidad Masa:  \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("  %3.3f kg/m3 ", densidadMasa);
                break;
            }case (MENU_VEL_MAS): {
                lcd_gotoxy(1, 1);
                printf("Velocidad Masa: \n");
                if (adv)
                    lcd_putc('A');
                else
                    lcd_putc(' ');
                lcd_gotoxy(2, 2);
                printf("   %3.3f m/s  ", velocidadMasa);
                break;
            }
        }
    }

    void drawChanVal() {
        switch (menuSection) {
            case (MENU_ESTADO): {
                break;
            }case (MENU_TIP_VAR): {
                int i;
                for (i = 0; i < 4; i++)
                    questKMT[i] = ' ';
                questKMT[selKMT] = 0b01111110;
                lcd_gotoxy(1, 1);
                printf("Proceso en:     \n");
                printf(" %ckg  %cm3  %csec ", questKMT[0], questKMT[1], questKMT[2]);
                break;
            }case (MENU_VALP_CUT): {
                lcd_gotoxy(1, 1);
                printf("Valor por Corte:\n");
                if(tVarProceso == tvp_kg)
                    printf("   %3.3f kg   ", kgXcorte);
                else if(tVarProceso == tvp_m3)
                    printf("   %3.3f m3   ", m3Xcorte);
                else if(tVarProceso == tvp_ti)    
                    printf("   %3.3f sec  ", tiXcorte);
                break;
            }case (MENU_CANT_CUT): {
                lcd_gotoxy(1, 1);
                printf("Cantidad Cortes:\n");
                printf("      %d       ", numCortes);
                break;
            }case (MENU_DIAM_TUB): {
                lcd_gotoxy(1, 1);
                printf("Diametro Tubo:  \n");
                printf("   %3.3f mm   ", diamTubo);
                break;
            }case (MENU_DENS_MAS): {
                lcd_gotoxy(1, 1);
                printf("Densidad Masa:  \n");
                printf("  %3.3f kg/m3 ", densidadMasa);
                break;
            }case (MENU_VEL_MAS): {
                lcd_gotoxy(1, 1);
                printf("Velocidad Masa: \n");
                printf("   %3.3f m/s  ", velocidadMasa);
                break;
            }
        }
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
        passChar[passSection] = 0b01111110;
        lcd_gotoxy(1, 1);
        printf("Contrasena:     \n");
        printf("    %c%u%c%u%c%u%c%u    ", passChar[0], introducido[0], passChar[1], introducido[1],
                passChar[2], introducido[2], passChar[3], introducido[3]);
    }

    void drawBadPass() {
        lcd_gotoxy(1, 1);
        printf("Contrasena      \n");
        printf("     Erronea    ");
    }

    void drawAdvON() {
        lcd_gotoxy(1, 1);
        printf("Modo Configurar:\n");
        printf("    Iniciado    ");
    }

    void drawAdvOFF() {
        lcd_gotoxy(1, 1);
        printf("Modo Configurar:\n");
        printf("   Finalizado   ");
    }

    void drawSNquest(char tq) {
        int i;
        for (i = 0; i < 2; i++)
            questSN[i] = ' ';
        questSN[selSN] = 0b01111110;
        lcd_gotoxy(1, 1);
        if (tq == 0)
            printf("Iniciar Proceso?\n");
        else if(tq == 1)
            printf("Detener Proceso?\n");
        else if(tq == 2)
            printf("Guardar Cambio? \n");
        printf("   %cSI    %cNO   ", questSN[0], questSN[1]);
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
                drawAdvON();
                break;
            }case (SCREEN_ADVMODE_OFF): {
                drawAdvOFF();
                break;
            }case (SCREEN_CALIB_VEL): {

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
            }
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* SCREENDRAWERS_H */

