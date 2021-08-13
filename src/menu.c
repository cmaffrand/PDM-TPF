/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/39
 *===========================================================================*/

#include "sapi.h"
#include "menu.h"
#include "led.h"
#include "teclas.h"
#include "process.h"
#include "uart.h"
#include <math.h>

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: MenuMEF -> Maquina de estado finito que maneja el menu.
*=============================================================================*/

void MenuMEF(primepro_t *primeProcess, menu_t *menu)
{
	static uint8_t	dataRead,i 	= 0;
	static bool_t 	newData 	= FALSE;

	switch (menu -> state)
    {
    case HOME_STATE:
    	// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
    	newData = uartReadByte( UART_USB, &dataRead);
	    if (((newData == TRUE) && (dataRead-48 == 1)) || (leerTecla(ptecla1) == OFF)){
	    	menu -> state = METHOD_STATE;
	    	displayMethod();
	    	newData = FALSE;
			RGBtoggle();
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 2)) || (leerTecla(ptecla2) == OFF)){
	    	menu -> state = NUMBER_STATE;
	    	primeProcess -> number = 0;
	    	displayNumber();
	    	newData = FALSE;
			RGBtoggle();
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 3)) || (leerTecla(ptecla3) == OFF)){
	    	menu -> state = RESULT_STATE;
			displayResult(primeProcess);
			newData = FALSE;
			apagarLeds();
			if (primeProcess -> result) encenderLed(LED3);
			else encenderLed(LED2);
			RGBtoggle();
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 4)) || (leerTecla(ptecla4) == OFF)){
	    	menu -> state = PROCESS_STATE;
			displayProcess();
			newData = FALSE;
			apagarLeds();
			encenderLed(LED1);
			RGBtoggle();
		}
	    else{
	    	menu -> state = HOME_STATE;
	    	newData = FALSE;
			RGBtoggle();
	    }
        break;
    case PROCESS_STATE:
    	if (primeProcess -> number >= 2){ //Defensivo para que no entre a los algoritmos
    		process(primeProcess);
			menu -> state = RESULT_STATE;
			displayResult(primeProcess);
			apagarLeds();
			RGBtoggle();
			if (primeProcess -> result) encenderLed(LED3);
			else encenderLed(LED2);
			uartRxFlush(UART_USB);
    	}
    	else {
    		menu -> state = NUMBER_STATE;
			primeProcess -> number = 0;
			displayNumber();
			RGBtoggle();
    	}
        break;
    case METHOD_STATE:
		if (uartReadByte( UART_USB, &dataRead)) {
			if 		(dataRead-48 == 1) primeProcess -> method 	= BRUTE_FORCE_METHOD;
			else if (dataRead-48 == 2) primeProcess -> method 	= PAIR_LESS_METHOD;
			else if (dataRead-48 == 3) primeProcess -> method 	= SQRT_METHOD;
			else if (dataRead-48 == 4) primeProcess -> method 	= SQRT_6KPLUS1_METHOD;
			else if (dataRead-48 == 5) primeProcess -> method 	= SIEVE_OF_ERATOSTHENES_METHOD;
			else if (dataRead-48 == 6) primeProcess -> method 	= SIEVE_OF_EULER_METHOD;
			else if (dataRead-48 == 7) primeProcess -> method 	= SQRT_30K235_METHOD;
			else if (dataRead-48 == 8) primeProcess -> method 	= SQRT_210K2357_METHOD;
			menu -> state = HOME_STATE;
			displayHome(primeProcess);
			RGBtoggle();
		}
    	break;
    case NUMBER_STATE:
    	newData = uartReadByte( UART_USB, &dataRead);
    	if (newData == TRUE) {
    		if ((dataRead >= 48) && (dataRead <= 57)){
    			primeProcess -> number = (primeProcess -> number)*10+dataRead-48;
				uartWriteByte( UART_USB, dataRead );
			}
			else {
				menu -> state = HOME_STATE;
				displayHome(primeProcess);
				i = 0;
			}
    		newData = FALSE;
    		i++;
    		if (i == 20){
    			menu -> state = HOME_STATE;
    			displayHome(primeProcess);
    			i = 0;
    		}
    		RGBtoggle();
    	}
    	if ((leerTecla(ptecla1) == OFF) || (leerTecla(ptecla2) == OFF) || (leerTecla(ptecla3) == OFF) || (leerTecla(ptecla4) == OFF)){
    		menu -> state = HOME_STATE;
			displayHome(primeProcess);
			i = 0;
			RGBtoggle();
    	}
        break;
    case RESULT_STATE:
    	newData = uartReadByte( UART_USB, &dataRead);
    	if (newData == TRUE) {
    		menu -> state = HOME_STATE;
    		displayHome(primeProcess);
    		apagarLeds();
    		RGBtoggle();
    		newData = FALSE;
    	}
    	if ((leerTecla(ptecla1) == OFF) || (leerTecla(ptecla2) == OFF) || (leerTecla(ptecla3) == OFF) || (leerTecla(ptecla4) == OFF)){
    		menu -> state = HOME_STATE;
			displayHome(primeProcess);
			apagarLeds();
			RGBtoggle();
		}
        break;
    default:
    	menu -> state = HOME_STATE;
		displayHome(primeProcess);
		newData = FALSE;
		apagarLeds();
		RGBtoggle();
        break;
    }
}

/*=============================================================================
* Funcion: initMenuMEF -> Inicializa el Menu en el Home
*=============================================================================*/

void initMenuMEF(primepro_t *primeProcess, menu_t *menu)
{
	menu -> state = HOME_STATE;

	//Inicializacion de estructuras de teclas
	tecla1.tecla = TEC1;
	tecla2.tecla = TEC2;
	tecla3.tecla = TEC3;
	tecla4.tecla = TEC4;

	// Punteros de teclas
	ptecla1 = &tecla1;
	ptecla2 = &tecla2;
	ptecla3 = &tecla3;
	ptecla4 = &tecla4;

	primeProcess -> number		= 0;
	primeProcess -> method		= BRUTE_FORCE_METHOD;
	primeProcess -> time		= 0;
	primeProcess -> result		= 0;
	primeProcess -> memory		= 0;
	primeProcess -> divider		= 0;
    primeProcess -> result		= FALSE;
    primeProcess -> memoryOV	= FALSE;

    displayHome(primeProcess);
}
