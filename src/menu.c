/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/09
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
* Funcion: MenuMEF -> Actualiza Maquina de estado finito que maneja el menu.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* menu_t *menu -> Puntero a estructura de menu "menu.h".
*=============================================================================*/

void MenuMEF(primepro_t *primeProcess, menu_t *menu)
{
	static uint8_t dataRead, i = 0;
	static bool_t newData = FALSE;

	// MEF de navegación por el menu del programa de procesamiento de primos
	switch (menu->state)
	{
	case HOME_STATE:
		// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
		newData = uartReadByte(UART_USB, &dataRead);
		// Entrada a seleccion de Metodo
		if (((newData == TRUE) && ((dataRead == 'm') || (dataRead == 'M'))) || (leerTecla(ptecla1) == OFF))
		{
			menu->state = METHOD_STATE;
			displayMethod();
			newData = FALSE;
		}
		// Entrada a seleccion de Numero
		else if (((newData == TRUE) && ((dataRead == 'n') || (dataRead == 'N'))) || (leerTecla(ptecla2) == OFF))
		{
			menu->state = NUMBER_STATE;
			primeProcess->number = 0;
			i = 0;
			displayNumber();
			newData = FALSE;
		}
		// Entrada a ver el resultado anterior
		else if (((newData == TRUE) && ((dataRead == 'r') || (dataRead == 'R'))) || (leerTecla(ptecla3) == OFF))
		{
			menu->state = RESULT_STATE;
			displayResult(primeProcess);
			newData = FALSE;
		}
		// Entrada a procesamiento
		else if (((newData == TRUE) && ((dataRead == 'p') || (dataRead == 'P'))) || (leerTecla(ptecla4) == OFF))
		{
			menu->state = PROCESS_STATE;
			displayProcess();
			newData = FALSE;
		}
		// Si era cualquier otra tecla sigo en HOME
		else
		{
			menu->state = HOME_STATE;
			newData = FALSE;
		}
		break;
	case PROCESS_STATE:
		// Procesa el número y una vez finalizado pasa directamente al menu de resultado.
		if (primeProcess->number >= 2)
		{
			process(primeProcess);
			menu->state = RESULT_STATE;
			displayResult(primeProcess);
			uartRxFlush(UART_USB);
		}
		// Defensivo para que no entre a los algoritmos de procesamiento con numeros menores que dos.
		// Si eso pasa el menu se va a selección de número.
		else
		{
			menu->state = NUMBER_STATE;
			primeProcess->number = 0;
			i = 0;
			displayNumber();
		}
		break;
	case METHOD_STATE:
		// Seleccion del metodo segun la tecla presionada una vez presionada se vuelve al Home.
		if (uartReadByte(UART_USB, &dataRead))
		{
			if (dataRead == '1')
				primeProcess->method = BRUTE_FORCE_METHOD;
			else if (dataRead == '2')
				primeProcess->method = PAIR_LESS_METHOD;
			else if (dataRead == '3')
				primeProcess->method = SQRT_METHOD;
			else if (dataRead == '4')
				primeProcess->method = SQRT_6KPLUS1_METHOD;
			else if (dataRead == '5')
				primeProcess->method = SIEVE_OF_ERATOSTHENES_METHOD;
			else if (dataRead == '6')
				primeProcess->method = SIEVE_OF_EULER_METHOD;
			else if (dataRead == '7')
				primeProcess->method = SQRT_30K235_METHOD;
			else if (dataRead == '8')
				primeProcess->method = SQRT_210K2357_METHOD;
			else if (dataRead == '9')
				primeProcess->method = SIEVE_OF_SUNDARAM_METHOD;
			else if (dataRead == '0')
				primeProcess->method = SIEVE_OF_ATKIN_METHOD;
			else if ((dataRead == 'a') || (dataRead == 'A'))
				primeProcess->method = FERMAT_METHOD;
			else if ((dataRead == 'b') || (dataRead == 'B'))
				primeProcess->method = MILLER_RABIN_METHOD;
			else if ((dataRead == 'c') || (dataRead == 'C'))
				primeProcess->method = SOLOVAY_STRASSEN_METHOD;
			menu->state = HOME_STATE;
			displayHome(primeProcess);
		}
		break;
	case NUMBER_STATE:
		// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
		newData = uartReadByte(UART_USB, &dataRead);
		if (newData == TRUE)
		{
			// Si es un numero se va acumulando en primeProcess -> number
			if ((dataRead >= '0') && (dataRead <= '9'))
			{
				primeProcess->number = (primeProcess->number) * 10 + dataRead - 48;
				uartWriteByte(UART_USB, dataRead);
			}
			// Presionando cualquier otro caracter se sale de la seleccion de numero
			// regresando a Home.
			else
			{
				menu->state = HOME_STATE;
				displayHome(primeProcess);
			}
			newData = FALSE;
			// Si el dato ya tiene 20 digitos se vuelve al home.
			// (máximo entero representable por un uint64_t)
			if (i == MAX_DIGIT - 1)
			{
				menu->state = HOME_STATE;
				displayHome(primeProcess);
			}
			else
				i++;
		}
		// Manejo del menu por teclas, vuelve por cualquier tecla en placa
		if ((leerTecla(ptecla1) == OFF) || (leerTecla(ptecla2) == OFF) || (leerTecla(ptecla3) == OFF) || (leerTecla(ptecla4) == OFF))
		{
			menu->state = HOME_STATE;
			displayHome(primeProcess);
		}
		break;
	case RESULT_STATE:
		// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
		newData = uartReadByte(UART_USB, &dataRead);
		// Vuelve a Home con cualquier tecla
		if (newData == TRUE)
		{
			menu->state = HOME_STATE;
			displayHome(primeProcess);
			newData = FALSE;
		}
		// Vuelve a Home con cualquier tecla en placa
		if ((leerTecla(ptecla1) == OFF) || (leerTecla(ptecla2) == OFF) || (leerTecla(ptecla3) == OFF) || (leerTecla(ptecla4) == OFF))
		{
			menu->state = HOME_STATE;
			displayHome(primeProcess);
		}
		break;
	default:
		// Defensivo vuelve a home
		menu->state = HOME_STATE;
		displayHome(primeProcess);
		newData = FALSE;
		break;
	}
	// Muestra led segun corresponda
	ledManage(primeProcess, menu);
}

/*=============================================================================
* Funcion: initMenuMEF -> Inicializa el Menu en el Home
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* menu_t *menu -> Puntero a estructura de menu "menu.h".
*=============================================================================*/

void initMenuMEF(primepro_t *primeProcess, menu_t *menu)
{
	// Inicializa el menu en Home.
	menu->state = HOME_STATE;

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

	// Inicializa la estructura de procesamiento de primos
	primeProcess->number = 0;
	primeProcess->method = BRUTE_FORCE_METHOD;
	primeProcess->time = 0;
	primeProcess->result = 0;
	primeProcess->memory = 0;
	primeProcess->divider = 0;
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;

	// Muestra Menu y Leds
	displayHome(primeProcess);
	ledManage(primeProcess, menu);
}
