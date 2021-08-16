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

#define SEGMENT_SIZE 20480 // 20480 - 20k

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef enum
{
	BRUTE_FORCE_METHOD,
	PAIR_LESS_METHOD,
	SQRT_METHOD,
	SQRT_6KPLUS1_METHOD,
	SIEVE_OF_ERATOSTHENES_METHOD,
	SIEVE_OF_EULER_METHOD,
	SQRT_30K235_METHOD,
	SQRT_210K2357_METHOD,
	SIEVE_OF_SUNDARAM_METHOD,
	SIEVE_OF_ATKIN_METHOD,
	FERMAT_METHOD,
} mtd_t;

typedef struct
{ // estructura para controlar el proceso
	uint64_t 	number;
	uint64_t 	time;
	mtd_t 		method;
	uint64_t	memory;
	bool_t		memoryOV;
	bool_t		result;
	uint64_t 	divider;
} primepro_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

bool_t process(primepro_t *primeProcess);
static bool_t MethodBF(primepro_t *primeProcess);
static bool_t MethodPL(primepro_t *primeProcess);
static bool_t MethodSQRT(primepro_t *primeProcess);
static bool_t Method6KPLUS1(primepro_t *primeProcess);
static bool_t MethodERATO(primepro_t *primeProcess);
static bool_t MethodEuler(primepro_t *primeProcess);
static bool_t Method30K(primepro_t *primeProcess);
static bool_t Method210K (primepro_t *primeProcess);
static bool_t MethodSundaram(primepro_t *primeProcess);
static bool_t MethodAtkin(primepro_t *primeProcess);
static uint64_t power(uint64_t a, uint64_t n, uint64_t p);
static uint64_t gcd(uint64_t a, uint64_t b);
static bool_t MethodFermat(primepro_t *primeProcess);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PROCESS_H__ */
