/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/13
 *===========================================================================*/

#include "sapi.h"
#include "time.h"

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: getTime -> Cuenta el tiempo desde el ultimo reseteo del contador de
* ticks.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
*=============================================================================*/

void getTime(primepro_t *primeProcess)
{
	primeProcess->time = ((uint64_t)DWT_CYCCNT * (uint64_t)1000000000) / (uint64_t)SystemCoreClock;
}

/*=============================================================================
* Funcion: setTime -> Setea el contador de ticks de sistema en un valor
* determinado (uint32_t set).
* Parametros de Entrada:  uint32_t set (valor de seteo)
*=============================================================================*/

void setTime(uint32_t set)
{
	DWT_CYCCNT = set;
}
