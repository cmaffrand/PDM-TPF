/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/09
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __LED_H__
#define __LED_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "process.h"
#include "menu.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

	/*=====[Definition macros of public constants]===============================*/

#define LED_OFF 46

	/*=====[Public function-like macros]=========================================*/

	/*=====[Definitions of public data types]====================================*/

	typedef enum
	{
		RED_STATE,
		GREEN_STATE,
		YELLOW_STATE,
		OFF_STATE
	} ledState_t;

	ledState_t ledState;

	typedef enum
	{
		HOME_MODE,
		RESULT_MODE,
		PROCESS_MODE
	} ledMode_t;

	ledMode_t ledMode;

	/*=====[Prototypes (declarations) of public functions]=======================*/

	bool_t encenderLed(gpioMap_t led);
	bool_t apagarLeds(void);
	bool_t RGBtoggle(void);
	void ledManage(primepro_t *primeProcess, menu_t *menu);

	/*=====[Prototypes (declarations) of public interrupt functions]=============*/

	/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __LED_H__ */
