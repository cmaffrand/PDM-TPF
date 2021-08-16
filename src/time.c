/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/07/13
 *===========================================================================*/

#include "sapi.h"
#include "time.h"

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: encenderLed -> Utilizada para encender leds en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t led, tipo de datos de sapi.h
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente.
* 							-> FALSE si no se pudo encender el led.
*=============================================================================*/

void getTime(primepro_t *primeProcess)
{
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
}

/*=============================================================================
* Funcion: apagarLeds -> Utilizada para apagar todos los leds de la placa EDU CIAA.
* Parametros de Entrada:  void
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente
*=============================================================================*/

void setTime(uint32_t set)
{
	DWT_CYCCNT = set;
}
