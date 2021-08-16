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

	#define MAX_DIGIT 20

	/*=====[Public function-like macros]=========================================*/

	/*=====[Definitions of public data types]====================================*/

	typedef enum
	{
		HOME_STATE,
		PROCESS_STATE,
		METHOD_STATE,
		NUMBER_STATE,
		RESULT_STATE
	} menuState_t;

	typedef struct
	{ // estructura para controlar el menu
		menuState_t state;
	} menu_t;

	/*=====[Prototypes (declarations) of public functions]=======================*/

	void initMenuMEF(primepro_t *primeProcess, menu_t *menu);
	void MenuMEF(primepro_t *primeProcess, menu_t *menu);

	/*=====[Prototypes (declarations) of public interrupt functions]=============*/

	/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __MENU_H__ */
