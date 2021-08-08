/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "main.h"
#include "sapi.h"
#include "teclas.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void)
{
	// Inicializar y configurar la plataforma
	boardConfig();

	//Inicializacion de estructuras de teclas
	tecla1.tecla = TEC1;
	tecla2.tecla = TEC2;
	tecla3.tecla = TEC3;
	tecla4.tecla = TEC4;

	// Punteros de teclas
	dbn_t *ptecla1 = &tecla1;
	dbn_t *ptecla2 = &tecla2;
	dbn_t *ptecla3 = &tecla3;
	dbn_t *ptecla4 = &tecla4;

	// Variable de numeros
	uint64_t 	number = 0;
	mtd_t		metodo = BRUTE_FORCE_METHOD;


	// ----- Repeat for ever -------------------------
	while (true)
	{
		// Polling de botones.
		if (leerTecla(ptecla1) == OFF)
		{
			number = 1;
			processBF(number,metodo);
		}
		if (leerTecla(ptecla2) == OFF)
		{
			number = 27;
			processBF(number,metodo);
		}
		if (leerTecla(ptecla3) == OFF)
		{
			number = 29;
			processBF(number,metodo);
		}
		if (leerTecla(ptecla4) == OFF)
		{
			number = 10007;
			processBF(number,metodo);
		}
	}

	return 0;
}
