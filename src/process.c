/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

#include "sapi.h"
#include "process.h"
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*=============================================================================
* Funcion: proccesFB -> 
* Parametros de Entrada: 
* Valor de retorno:	ret_val -> TRUE 
* 							-> FALSE 
*=============================================================================*/

bool_t process(primepro_t *primeProcess)
{
    bool_t ret_val = 0;

	// Chequeo que el numero sea mayor que 2 para poder aplicar el algoritmo
	if (primeProcess -> number >= 2) {
		switch (primeProcess -> method) {
			case BRUTE_FORCE_METHOD:
				ret_val = MetohdBF(primeProcess);
				break;
			case PAIR_LESS_METHOD:
				ret_val = MetohdPL(primeProcess);
				break;
			case SQRT_METHOD:
				ret_val = MetohdSQRT(primeProcess);
				break;
			case SQRT_6KPLUS1_METHOD:
				ret_val = Metohd6KPLUS1(primeProcess);
				 break;
			case SIEVE_OF_ERATOSTHENES_METHOD:
				ret_val = MetohdERATO(primeProcess);
				break;
			case SIEVE_OF_EULER_METHOD:
				ret_val = MetohdEuler(primeProcess);
				break;
			default:
			break;
		}
   }
   else {
	    printf("Numero ");
		printf("%" PRIu64, primeProcess -> number);
		printf(" no puede ser procesado\r\n");
   }
   return ret_val;
}

static bool_t MetohdBF(primepro_t *primeProcess){
    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    DWT_CYCCNT = 0;
	for (i = 2; i <= primeProcess -> number/2; ++i){
		if (primeProcess -> number % i == 0){
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			return primeProcess -> result;
		}
	}
	primeProcess -> result = TRUE;
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	return primeProcess -> result;
}

static bool_t MetohdPL(primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
	DWT_CYCCNT = 0;
	primeProcess -> result = FALSE;
	if (primeProcess -> number == 2) {
		primeProcess -> result = TRUE;
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		return primeProcess -> result;
	}
	for (i = 3; i <= primeProcess -> number / 2; i = i + 2) {
		if (primeProcess -> number % i == 0) {
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			return primeProcess -> result;
		}
	}
	primeProcess -> result = TRUE;
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	return primeProcess -> result;
}

static bool_t MetohdSQRT(primepro_t *primeProcess){

    uint32_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint32_t);
    DWT_CYCCNT = 0;
    primeProcess -> result = FALSE;
    for (i = 2; i * i <= primeProcess -> number; ++i) {
		if (primeProcess -> number % i == 0) {
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			return primeProcess -> result;
		}
	}
    primeProcess -> result = TRUE;
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	return primeProcess -> result;
}

static bool_t Metohd6KPLUS1(primepro_t *primeProcess){

    uint32_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint32_t);
    DWT_CYCCNT = 0;
    primeProcess -> result = FALSE;
	if(primeProcess -> number <= 3) {
		primeProcess -> result = TRUE;
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		return primeProcess -> result;
	}
	 if(primeProcess -> number % 2 == 0 || primeProcess -> number % 3 == 0) {
		 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		 return primeProcess -> result;
	 }
	 for (i = 5; i * i <= primeProcess -> number; i = i + 6) {
		if (primeProcess -> number % i == 0) {
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			return primeProcess -> result;
		}
	 }
	 primeProcess -> result = TRUE;
	 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	 return primeProcess -> result;
}

static bool_t MetohdERATO(primepro_t *primeProcess){

    uint32_t i,p,sqrt_number;
    sqrt_number = (uint32_t) (sqrt(primeProcess -> number));
    bool_t prime[sqrt_number+1];
	memset(prime, TRUE, sizeof(prime));

    primeProcess -> memory = sizeof(primepro_t) + 3*sizeof(uint32_t) + sqrt_number+1 * sizeof(bool_t);
    DWT_CYCCNT = 0;
    primeProcess -> result = FALSE;
	for (p = 2; p * p <= sqrt_number; p++){
		if (prime[p] == TRUE){
			for (i = p * p; i <= sqrt_number; i += p)
				prime[i] = FALSE;
		}
	}
	for (p = 2; p <= sqrt_number; p++){
		if (prime[p] == TRUE){
			if (primeProcess -> number % p == 0) {
				primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
				return primeProcess -> result;
			}
		}
	}
	primeProcess -> result = TRUE;
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	return primeProcess -> result;
}

static bool_t MetohdEuler(primepro_t *primeProcess){

    uint32_t i,p,q,sqrt_number,max_q;
    sqrt_number = (uint32_t) (sqrt(primeProcess -> number));
    bool_t prime[sqrt_number+1];
	memset(prime, FALSE, sizeof(prime));

    primeProcess -> memory = sizeof(primepro_t) + 5*sizeof(uint32_t) + sqrt_number+1 * sizeof(bool_t);
    DWT_CYCCNT = 0;
    primeProcess -> result = FALSE;
	prime[2] = TRUE;
	for (i = 3; i <= sqrt_number; i += 2) prime[i] = TRUE;
	for (p = 3; p <= sqrt_number; p += 2){
		if (prime[p]){
			max_q = sqrt_number / p;
			if (max_q % 2 == 0) max_q--;
			for (q = max_q; q >= p; q -= 2){
				if (prime[q]) prime[p * q] = FALSE;
			}
		}
	}
	for (p = 2; p <= sqrt_number; p++){
		if (prime[p] == TRUE){
			if (primeProcess -> number % p == 0) {
				primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
				return primeProcess -> result;
			}
		}
	}
	primeProcess -> result = TRUE;
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	return primeProcess -> result;
}
