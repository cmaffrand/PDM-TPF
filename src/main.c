/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "main.h"
#include "menu.h"

/*=====[Definition macros o
#include <inttypes.h>f private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void)
{
	// Inicializar y configurar la plataforma
	boardConfig();

	initMenuMEF();

	// ----- Repeat for ever -------------------------
	while (true)
	{
		MenuMEF();
		//817504243;//15485863; 982451653;
	}

	return 0;
}
