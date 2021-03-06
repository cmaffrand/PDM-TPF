/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/07/30
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __UART_H__
#define __UART_H__

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

    /*=====[Prototypes (declarations) of public functions]=======================*/

    void displayHome(primepro_t *primeProcess);
    void displayMethod(void);
    void displayProcess(void);
    void displayResult(primepro_t *primeProcess);
    void displayNumber(void);

    /*=====[Prototypes (declarations) of public interrupt functions]=============*/

    /*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __UART_H__ */
