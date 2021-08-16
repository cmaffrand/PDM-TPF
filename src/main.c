/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "main.h"
#include "led.h"
#include "menu.h"
#include "process.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void)
{
	// Inicializar y configurar la plataforma
	boardConfig();

	//Declaraciones para calcular tiempo
	uint64_t *H_DWT_DEMCR = (uint64_t *)0xE000EDFC;
	uint64_t *H_DWT_CTRL = (uint64_t *)0xE0001000;
	uint64_t *H_DWT_CYCCNT = (uint64_t *)0xE0001004;
	*H_DWT_DEMCR |= 1 << 24; //
	*H_DWT_CTRL |= 1;

	// Punteros a estructuras para manejo de menu y procesamiento
	menu_t menu;
	menu_t *pmenu = &menu;
	primepro_t primeProcess;
	primepro_t *pprimeProcess = &primeProcess;

	initMenuMEF(pprimeProcess, pmenu);

	// ----- Repeat for ever -------------------------
	while (true)
	{
		MenuMEF(pprimeProcess, pmenu);

		// TEST NUMBERS
		// 6516547 					-> No primo, divisor en 487.
		// 100140049				-> No primo, 10007^2
		// 15485863                 -> Primo
		// 817504243
		// 838041641 // Máximo primo para método 0
		// 982451653
		// 1500000001
		// 3333323333 primo maximo para metodos 5 y 6. Memoria.
		// 10000600009 100003*100003
		// 100123456789
		// 1000000000039
		// 999998727899999
		// 18446744069414584321 // Primo más grande que se puede ingresar en un uint64_t
	}

	return 0;
}
