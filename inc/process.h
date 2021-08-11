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

typedef struct
{ // estructura para controlar el antirrebote de un tecla
	uint64_t 	number;
	uint64_t 	time;
	mtd_t 		method;
	uint64_t	memory;
	bool_t		result;
} primepro_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

bool_t process(primepro_t *primeProcess);
static bool_t MetohdBF(primepro_t *primeProcess);
static bool_t MetohdPL(primepro_t *primeProcess);
static bool_t MetohdSQRT(primepro_t *primeProcess);
static bool_t Metohd6KPLUS1(primepro_t *primeProcess);
static bool_t MetohdERATO(primepro_t *primeProcess);
static bool_t MetohdEuler(primepro_t *primeProcess);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PROCESS_H__ */
