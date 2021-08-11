/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "main.h"
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
    uint64_t * H_DWT_DEMCR 	= (uint64_t *)0xE000EDFC;// chequear volatile
    uint64_t * H_DWT_CTRL 	= (uint64_t *)0xE0001000;// chequear volatile
    uint64_t * H_DWT_CYCCNT = (uint64_t *)0xE0001004;// chequear volatile
    *H_DWT_DEMCR |= 1<<24;//
    *H_DWT_CTRL |= 1;

	primepro_t primeProcess;
	primepro_t * pprimeProcess = &primeProcess;

	initMenuMEF(pprimeProcess);

	// ----- Repeat for ever -------------------------
	while (true)
	{
		MenuMEF(pprimeProcess);
		//817504243;//15485863; 982451653;
	}

	return 0;
}
