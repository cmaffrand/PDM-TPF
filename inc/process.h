/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __PROCESS_H__
#define __PROCESS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

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
	BRUTE_FORCE_METHOD,
	PAIR_LESS_METHOD,
	SQRT_METHOD,
	SQRT_6KPLUS1_METHOD,
	SIEVE_OF_ERATOSTHENES_METHOD,
	SIEVE_OF_EULER_METHOD
} mtd_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

bool_t processBF(uint64_t number, mtd_t metodo, uint64_t * time);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PROCESS_H__ */
