#ifndef BUTTONCONTROLLER_H
#define	BUTTONCONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif


    void buttonChecking() {
        if(!UP && lastSttUP) {
            lastSttUP = 0;
            delay_ms(200);
        }else if(UP && !lastSttUP) {
            lastSttUP = 1;
            if(holdUPcont < 10)
                pressUP();
            delay_ms(50);
        }else if(UP == lastSttUP) {
            if(UP) {
                holdUPcont = 0;
                releaseUP();
            }else {
                if(!UPsecurLock)
                    holdUPcont++;
                if(holdUPcont > 9) {
                    if(holdUPcont < 26)
                        longPressUP();
                    else
                        UPsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!DOWN && lastSttDOWN) {
            lastSttDOWN = 0;
            delay_ms(200);
        }else if(DOWN && !lastSttDOWN) {
            lastSttDOWN = 1;
            if(holdDOWNcont < 10)
                pressDOWN();
            delay_ms(50);
        }else if(DOWN == lastSttDOWN) {
            if(DOWN) {
                holdDOWNcont = 0;
                releaseDOWN();
            }else {
                if(!DOWNsecurLock)
                    holdDOWNcont++;
                if(holdDOWNcont > 9) {
                    if(holdDOWNcont < 26)
                        longPressDOWN();
                    else
                        DOWNsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!RETRO && lastSttRETRO) {
            lastSttRETRO = 0;
            delay_ms(200);
        }else if(RETRO && !lastSttRETRO) {
            lastSttRETRO = 1;
            if(holdRETROcont < 10)
                pressRETRO();
            delay_ms(50);
        }else if(RETRO == lastSttRETRO) {
            if(RETRO) {
                holdRETROcont = 0;
                releaseRETRO();
            }else {
                if(!RETROsecurLock)
                    holdRETROcont++;
                if(holdRETROcont > 9) {
                    if(holdRETROcont < 26)
                        longPressRETRO();
                    else
                        RETROsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
        if(!ENTER && lastSttENTER) {
            lastSttENTER = 0;
            delay_ms(200);
        }else if(ENTER && !lastSttENTER) {
            lastSttENTER = 1;
            if(holdENTERcont < 10)
                pressENTER();
            delay_ms(50);
        }else if(ENTER == lastSttENTER) {
            if(ENTER) {
                holdENTERcont = 0;
                releaseENTER();
            }else {
                if(!ENTERsecurLock)
                    holdENTERcont++;
                if(holdENTERcont > 9) {
                    if(holdENTERcont < 26)
                        longPressENTER();
                    else
                        ENTERsecurLock = 1;//Alguien apoyado!
                }
                delay_ms(200);
            }
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONCONTROLLER_H */

