/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/09
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __MENU_H__
#define __MENU_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "process.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

	/*=====[Definition macros of public constants]===============================*/

	/*=====[Public function-like macros]=========================================*/

	/*=====[Definitions of public data types]====================================*/

	typedef enum
	{
		HOME_STATE,
		PROCESS_STATE,
		METHOD_STATE,
		NUMBER_STATE,
		RESULT_STATE
	} estadoMenu_t;

	estadoMenu_t menuState;

	/*=====[Prototypes (declarations) of public functions]=======================*/

	void initMenuMEF(primepro_t *primeProcess);
	void MenuMEF(primepro_t *primeProcess);

	/*=====[Prototypes (declarations) of public interrupt functions]=============*/

	/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __MENU_H__ */
