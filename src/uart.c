/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/07/31
 *===========================================================================*/

#include "sapi.h"
#include "process.h"
#include <string.h>
#include <inttypes.h>

/*=====[Definitions of public global variables]==============================*/

/*=============================================================================
* Funcion: displayHome -> Muestra por la consola serie el menu en Home.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
*=============================================================================*/

void displayHome(primepro_t *primeProcess)
{

	uint8_t mensajeMetodo[50];

	//se genera el mensaje de metodo
	switch (primeProcess->method)
	{
	case BRUTE_FORCE_METHOD:
		strcpy(mensajeMetodo, "BRUTE_FORCE_METHOD");
		break;
	case PAIR_LESS_METHOD:
		strcpy(mensajeMetodo, "PAIR_LESS_METHOD");
		break;
	case SQRT_METHOD:
		strcpy(mensajeMetodo, "SQRT_METHOD");
		break;
	case SQRT_6KPLUS1_METHOD:
		strcpy(mensajeMetodo, "SQRT_6KPLUS1_METHOD");
		break;
	case SIEVE_OF_ERATOSTHENES_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_ERATOSTHENES_METHOD");
		break;
	case SIEVE_OF_EULER_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_EULER_METHOD");
		break;
	case SQRT_30K235_METHOD:
		strcpy(mensajeMetodo, "SQRT_30K235_METHOD");
		break;
	case SQRT_210K2357_METHOD:
		strcpy(mensajeMetodo, "SQRT_210K2357_METHOD");
		break;
	case SIEVE_OF_SUNDARAM_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_SUNDARAM_METHOD");
		break;
	case SIEVE_OF_ATKIN_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_ATKIN_METHOD");
		break;
	case FERMAT_METHOD:
		strcpy(mensajeMetodo, "FERMAT_METHOD");
		break;
	case MILLER_RABIN_METHOD:
		strcpy(mensajeMetodo, "MILLER_RABIN_METHOD");
		break;
	case SOLOWAY_STRSSEN_METHOD:
		strcpy(mensajeMetodo, "SOLOWAY_STRSSEN_METHOD");
		break;
	default:
		break;
	}

	//se borra pantalla
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[2J"); // Clear screen command
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[H");  // Cursor to home command
	printf("|------------------------------------------------|\r\n");
	printf("| Programa de detección de números primos        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Numero:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Metodo:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Presione M o TEC1 Para selecionar el metodo.   |\r\n");
	printf("| Presione N o TEC2 Para ingresar un número.     |\r\n");
	printf("| Presione R o TEC3 Para para ver el resultado.  |\r\n");
	printf("| Presione P o TEC4 Para procesar                |\r\n");
	printf("|------------------------------------------------|\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[7A"); // Cursordos lineas arriba
	printf("| Metodo: ");
	printf("%s", mensajeMetodo);
	printf("\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Numero: ");
	printf("%" PRIu64, primeProcess->number);
	printf("\r\n");
}

/*=============================================================================
* Funcion: displayMethod -> Muestra por la consola serie el menu en la pantalla
* de seleccion de metodo.
*=============================================================================*/

void displayMethod(void)
{
	//se borra pantalla
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[2J"); // Clear screen command
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[H");  // Cursor to home command
	printf("|------------------------------------------------|\r\n");
	printf("| Seleccione un metodo de deteccion de primos    |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Presione 1 BRUTE_FORCE_METHOD                  |\r\n");
	printf("| Presione 2 PAIR_LESS_METHOD                    |\r\n");
	printf("| Presione 3 SQRT_METHOD                         |\r\n");
	printf("| Presione 4 SQRT_6KPLUS1_METHOD                 |\r\n");
	printf("| Presione 5 SIEVE_OF_ERATOSTHENES_METHOD        |\r\n");
	printf("| Presione 6 SIEVE_OF_EULER_METHOD               |\r\n");
	printf("| Presione 7 SQRT_30K235_METHOD                  |\r\n");
	printf("| Presione 8 SQRT_210K2357_METHOD                |\r\n");
	printf("| Presione 9 SIEVE_OF_SUNDARAM_METHOD            |\r\n");
	printf("| Presione 0 SIEVE_OF_ATKIN_METHOD               |\r\n");
	printf("| Presione A FERMAT_METHOD                       |\r\n");
	printf("| Presione B MILLER_RABIN_METHOD                 |\r\n");
	printf("| Presione C SOLOWAY_STRSSEN_METHOD              |\r\n");
	printf("|------------------------------------------------|\r\n");
}

/*=============================================================================
* Funcion: displayProcess -> Muestra por la consola serie el menu en la pantalla
* de process.
*=============================================================================*/

void displayProcess(void)
{
	//se borra pantalla
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[2J"); // Clear screen command
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[H");  // Cursor to home command
	printf("|------------------------------------------------|\r\n");
	printf("| Procesando                                     |\r\n");
	printf("|------------------------------------------------|\r\n");
}

/*=============================================================================
* Funcion: displayNumber -> Muestra por la consola serie el menu en la pantalla
* de seleccion de numero.
*=============================================================================*/

void displayNumber(void)
{
	//se borra pantalla
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[2J"); // Clear screen command
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[H");  // Cursor to home command
	printf("|------------------------------------------------|\r\n");
	printf("| El numero debe ser mayor o igual a 2           |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Ingrese un numero:                             |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Luego presione cualquier tecla para ir al menu |\r\n");
	printf("|------------------------------------------------|\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[5A"); // Cursordos lineas arriba
	printf("|--------------------\n");
}

/*=============================================================================
* Funcion: displayResult -> Muestra por la consola serie el menu en la pantalla
* de visualizacion de resultados.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
*=============================================================================*/

void displayResult(primepro_t *primeProcess)
{

	uint8_t mensajeMetodo[50], timeUnit[3];
	uint16_t timeQ, timeF;

	//se genera el mensaje de metodo
	switch (primeProcess->method)
	{
	case BRUTE_FORCE_METHOD:
		strcpy(mensajeMetodo, "BRUTE_FORCE_METHOD");
		break;
	case PAIR_LESS_METHOD:
		strcpy(mensajeMetodo, "PAIR_LESS_METHOD");
		break;
	case SQRT_METHOD:
		strcpy(mensajeMetodo, "SQRT_METHOD");
		break;
	case SQRT_6KPLUS1_METHOD:
		strcpy(mensajeMetodo, "SQRT_6KPLUS1_METHOD");
		break;
	case SIEVE_OF_ERATOSTHENES_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_ERATOSTHENES_METHOD");
		break;
	case SIEVE_OF_EULER_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_EULER_METHOD");
		break;
	case SQRT_30K235_METHOD:
		strcpy(mensajeMetodo, "SQRT_30K235_METHOD");
		break;
	case SQRT_210K2357_METHOD:
		strcpy(mensajeMetodo, "SQRT_210K2357_METHOD");
		break;
	case SIEVE_OF_SUNDARAM_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_SUNDARAM_METHOD");
		break;
	case SIEVE_OF_ATKIN_METHOD:
		strcpy(mensajeMetodo, "SIEVE_OF_ATKIN_METHOD");
		break;
	case FERMAT_METHOD:
		strcpy(mensajeMetodo, "FERMAT_METHOD");
		break;
	case MILLER_RABIN_METHOD:
		strcpy(mensajeMetodo, "MILLER_RABIN_METHOD");
		break;
	case SOLOWAY_STRSSEN_METHOD:
		strcpy(mensajeMetodo, "SOLOWAY_STRSSEN_METHOD");
		break;
	default:
		break;
	}

	// Calculo de tiempo en formato humano
	if (primeProcess->time >= 1000000000)
	{
		timeQ = primeProcess->time / 1000000000;
		timeF = (uint16_t)((primeProcess->time - timeQ * 1000000000) / 10000000);
		strcpy(timeUnit, "s");
	}
	else if (primeProcess->time >= 1000000)
	{
		timeQ = primeProcess->time / 1000000;
		timeF = (uint16_t)((primeProcess->time - timeQ * 1000000) / 10000);
		strcpy(timeUnit, "ms");
	}
	else if (primeProcess->time >= 1000)
	{
		timeQ = primeProcess->time / 1000;
		(uint16_t)((primeProcess->time - timeQ * 1000) / 10);
		strcpy(timeUnit, "us");
	}
	else
	{
		timeQ = primeProcess->time;
		timeF = 0;
		strcpy(timeUnit, "ns");
	}
	//se borra pantalla
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[2J"); // Clear screen command
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[H");  // Cursor to home command
	printf("|------------------------------------------------|\r\n");
	printf("| Numero:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Resultado:                                     |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Divisor:                                       |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Tiempo:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Metodo:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Memoria:                                       |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Presione cualquier tecla para volver al menu   |\r\n");
	printf("|------------------------------------------------|\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[4A"); // Cursordos lineas arriba
	printf("| Memoria: ");
	printf("%" PRIu64, primeProcess->memory);
	printf(" Bytes");
	if (primeProcess->memoryOV)
		printf(" OverFlow\r\n");
	else
		printf("\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Metodo: ");
	printf("%s", mensajeMetodo);
	printf("\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Tiempo: %d.%d %s\r\n", timeQ, timeF, timeUnit);
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Divisor: ");
	printf("%" PRIu64, primeProcess->divider);
	printf("\r\n");
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Resultado: ");
	if (primeProcess->memoryOV)
	{
		if (!(primeProcess->result))
			printf("no es primo\r\n");
		else
			printf("Numero grande para el metodo\r\n");
	}
	else
	{
		if (!(primeProcess->result))
			printf("no ");
		printf("es primo\r\n");
	}
	uartWriteByte(UART_USB, 27);	  // ESC command
	uartWriteString(UART_USB, "[3A"); // Cursordos lineas arriba
	printf("| Numero: ");
	printf("%" PRIu64, primeProcess->number);
	printf("\r\n");
}
