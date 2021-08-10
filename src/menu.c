/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/39
 *===========================================================================*/

#include "sapi.h"
#include "led.h"
#include "teclas.h"
#include "process.h"
#include "uart.h"
#include "menu.h"
#include <math.h>

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: MenuMEF -> Maquina de estado finito que maneja el menu.
*=============================================================================*/

void MenuMEF(void)
{
	switch (menuState)
    {
    case HOME_STATE:
    	// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
    	newData = uartReadByte( UART_USB, &dataRead);
	    if (((newData == TRUE) && (dataRead-48 == 1)) || (leerTecla(ptecla1) == OFF)){
	    	menuState = METHOD_STATE;
	    	displayMethod();
	    	newData = FALSE;
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 2)) || (leerTecla(ptecla2) == OFF)){
	    	menuState = NUMBER_STATE;
	    	selectedNumber = 0;
	    	displayNumber();
	    	newData = FALSE;
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 3)) || (leerTecla(ptecla3) == OFF)){
			menuState = RESULT_STATE;
			displayResult(newResult,selectedNumber,selectedMethod,processTime);
			newData = FALSE;
	    }
	    else if (((newData == TRUE) && (dataRead-48 == 4)) || (leerTecla(ptecla4) == OFF)){
			menuState = PROCESS_STATE;
			displayProcess();
			newData = FALSE;
		}
	    else{
	    	menuState = HOME_STATE;
	    	newData = FALSE;
	    }
        break;
    case PROCESS_STATE:
    	newResult = processBF(selectedNumber,selectedMethod,pprocessTime);
    	menuState = RESULT_STATE;
    	displayResult(newResult,selectedNumber,selectedMethod,processTime);
	    uartRxFlush(UART_USB);
        break;
    case METHOD_STATE:
		if (uartReadByte( UART_USB, &dataRead)) {
			if 		(dataRead-48 == 1) selectedMethod 	= BRUTE_FORCE_METHOD;
			else if (dataRead-48 == 2) selectedMethod 	= PAIR_LESS_METHOD;
			else if (dataRead-48 == 3) selectedMethod 	= SQRT_METHOD;
			else if (dataRead-48 == 4) selectedMethod 	= SQRT_6KPLUS1_METHOD;
			else if (dataRead-48 == 5) selectedMethod 	= SIEVE_OF_ERATOSTHENES_METHOD;
			else if (dataRead-48 == 6) selectedMethod 	= SIEVE_OF_EULER_METHOD;
			menuState 	= HOME_STATE;
			displayHome();
		}
    	break;
    case NUMBER_STATE:
    	newData = uartReadByte( UART_USB, &dataRead);
    	if (newData == TRUE) {
    		if ((dataRead >= 48) && (dataRead <= 57)){
				selectedNumber = selectedNumber*10+dataRead-48;
				uartWriteByte( UART_USB, dataRead );
			}
			else {
				menuState 	= HOME_STATE;
				displayHome();
			}
    		newData = FALSE;
    	}

        break;
    case RESULT_STATE:
    	newData = uartReadByte( UART_USB, &dataRead);
    	if (newData == TRUE) {
    		menuState = HOME_STATE;
    		displayHome();
    		newData = FALSE;
    	}
        break;
    default:
    	menuState = HOME_STATE;
		displayHome();
		newData = FALSE;
        break;
    }
}

/*=============================================================================
* Funcion: initMenuMEF -> Inicializa el Menu en el Home
*=============================================================================*/

void initMenuMEF(void)
{
	dataRead  	= 0;
	newResult	= FALSE;
	newData 	= FALSE;
	menuState 	= HOME_STATE;
	i			= 0;
	p			= 0;

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

	selectedNumber = 0;
	selectedMethod = BRUTE_FORCE_METHOD;
	processTime = 0;
	pprocessTime = &processTime;

    displayHome();
}
