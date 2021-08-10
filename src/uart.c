/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/31
 *===========================================================================*/

#include "sapi.h"
#include "teclas.h"
#include "process.h"
#include <string.h>
#include <inttypes.h>

/*=====[Definitions of public global variables]==============================*/

/*=============================================================================
* Funcion: displaySemaforo -> Muestra por consola los estados y modos del
* semaforo y las teclas.
*=============================================================================*/

void displayHome(void) {
	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command
	printf("|------------------------------------------------| \r\n");
	printf("| Programa de detección de números Primos        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Presione 1 o TEC1 Para selecionar el metodo.   |\r\n");
	printf("| Presione 2 o TEC2 Para ingresar un número.     |\r\n");
	printf("| Presione 3 o TEC3 Para para ver el resultado.  |\r\n");
	printf("| Presione 4 o TEC4 Para procesar                |\r\n");
	printf("|------------------------------------------------|\r\n");
}
void displayMethod(void) {
	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command
	printf("|------------------------------------------------| \r\n");
	printf("| Seleccione un metodo de deteccion de primos    |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Presione 1 BRUTE_FORCE_METHOD                  |\r\n");
	printf("| Presione 2 PAIR_LESS_METHOD                    |\r\n");
	printf("| Presione 3 SQRT_METHOD                         |\r\n");
	printf("| Presione 4 SQRT_6KPLUS1_METHOD                 |\r\n");
	printf("| Presione 5 SIEVE_OF_ERATOSTHENES_METHOD        |\r\n");
	printf("| Presione 6 SIEVE_OF_EULER_METHOD               |\r\n");
	printf("|------------------------------------------------|\r\n");
}
void displayProcess(void) {
	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command
	printf("|------------------------------------------------| \r\n");
	printf("| Procesando                                     |\r\n");
	printf("|------------------------------------------------|\r\n");
}
void displayNumber(void) {
	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command
	printf("|------------------------------------------------| \r\n");
	printf("| Ingrese un numero:                             |\r\n");
	printf("|------------------------------------------------|\r\n");
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[3A"  );  // Cursordos lineas arriba
	printf("|--------------------\n");
}

void displayResult(bool_t result, uint64_t number, mtd_t metodo, uint64_t time) {

	uint8_t mensajeMetodo[50];

	//se genera el mensaje de metodo
	switch (metodo){
	case BRUTE_FORCE_METHOD:
		strcpy(mensajeMetodo,"BRUTE_FORCE_METHOD");
		break;
	case PAIR_LESS_METHOD:
		strcpy(mensajeMetodo,"PAIR_LESS_METHOD");
		break;
	case SQRT_METHOD:
		strcpy(mensajeMetodo,"SQRT_METHOD");
		break;
	case SQRT_6KPLUS1_METHOD:
		strcpy(mensajeMetodo,"SQRT_6KPLUS1_METHOD");
		break;
	case SIEVE_OF_ERATOSTHENES_METHOD:
		strcpy(mensajeMetodo,"SIEVE_OF_ERATOSTHENES_METHOD");
		break;
	case SIEVE_OF_EULER_METHOD:
		strcpy(mensajeMetodo,"SIEVE_OF_EULER_METHOD");
		break;
	default:
		break;
	}

	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command
	printf("|------------------------------------------------| \r\n");
	printf("| Numero:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Resultado:                                     |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Tiempo:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	printf("| Metodo:                                        |\r\n");
	printf("|------------------------------------------------|\r\n");
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2A"  );  // Cursordos lineas arriba
	printf("| Metodo: ");
	printf("%s",mensajeMetodo);
	printf("\r\n");
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[3A"  );  // Cursordos lineas arriba
	printf("| Tiempo: ");
	printf("%" PRIu64, time);
	printf(" ns\r\n");
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[3A"  );  // Cursordos lineas arriba
	printf("| Resultado: ");
	if (!result) printf("no ");
	printf("es primo\r\n");
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[3A"  );  // Cursordos lineas arriba
	printf("| Numero: ");
	printf("%" PRIu64, number);
	printf("\r\n");
}

/*void displaySemaforo(void)
{
	char mensajeModo[20];
	char mensajeEstado[20];
	char mensajeEstadoTecla1[20];
	char mensajeEstadoTecla2[20];
	char mensajeEstadoTecla3[20];
	char mensajeEstadoTecla4[20];

	//se genera el mensaje de modo del semaforo
	switch (semaforoMode){
	case NORMAL_MODE:
		strcpy(mensajeModo,"NORMAL_MODE");
		break;
	case DISCONNECTED_MODE:
		strcpy(mensajeModo,"DISCONNECTED_MODE");
		break;
	case ALARM_MODE:
		strcpy(mensajeModo,"ALARM_MODE");
		break;
	default:
		break;
	}

	//se genera el mensaje de estado del semaforo
	switch (semaforoState){
		case RED_STATE:
			strcpy(mensajeEstado,"RED_STATE");
			break;
		case REDYELLOW_STATE:
			strcpy(mensajeEstado,"REDYELLOW_STATE");
			break;
		case GREEN_STATE:
			strcpy(mensajeEstado,"GREEN_STATE");
			break;
		case YELLOW_STATE:
			strcpy(mensajeEstado,"YELLOW_STATE");
			break;
		case OFF_STATE:
			strcpy(mensajeEstado,"OFF_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 1
	switch (tecla1.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla1,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla1,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla1,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla1,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 2
	switch (tecla2.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla2,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla2,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla2,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla2,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 3
	switch (tecla3.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla3,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla3,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla3,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla3,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 4
	switch (tecla4.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla4,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla4,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla4,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla4,"RISING_STATE");
			break;
		default:
			break;
		}

	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command

	//se imprime el mensaje
	printf("Modo actual: %s\r\n",mensajeModo);
	printf("Estado actual: %s\r\n",mensajeEstado);
	printf("Tecla %d: %s\r\n",tecla1.tecla - 35,mensajeEstadoTecla1);
	printf("Tecla %d: %s\r\n",tecla2.tecla - 35,mensajeEstadoTecla2);
	printf("Tecla %d: %s\r\n",tecla3.tecla - 35,mensajeEstadoTecla3);
	printf("Tecla %d: %s\r\n",tecla4.tecla - 35,mensajeEstadoTecla4);

}*/
