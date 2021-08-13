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
				ret_val = MethodBF(primeProcess);
				break;
			case PAIR_LESS_METHOD:
				ret_val = MethodPL(primeProcess);
				break;
			case SQRT_METHOD:
				ret_val = MethodSQRT(primeProcess);
				break;
			case SQRT_6KPLUS1_METHOD:
				ret_val = Method6KPLUS1(primeProcess);
				 break;
			case SIEVE_OF_ERATOSTHENES_METHOD:
				ret_val = MethodERATO(primeProcess);
				break;
			case SIEVE_OF_EULER_METHOD:
				ret_val = MethodEuler(primeProcess);
				break;
			case SQRT_30K235_METHOD:
				ret_val = Method30K(primeProcess);
				break;
			case SQRT_210K2357_METHOD:
				ret_val = Method210K(primeProcess);
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

static bool_t MethodBF(primepro_t *primeProcess){
	uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    primeProcess -> memoryOV = FALSE;

    DWT_CYCCNT = 0;
	for (i = 2; i <= primeProcess -> number/2; ++i){
		if (primeProcess -> number % i == 0){
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			primeProcess -> divider = i;
			return primeProcess -> result;
		}
	}
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	primeProcess -> divider = primeProcess -> number;
	return primeProcess -> result = TRUE;;
}
static bool_t MethodPL(primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess -> result = FALSE;
    primeProcess -> memoryOV = FALSE;

	DWT_CYCCNT = 0;
	if (primeProcess -> number == 2) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = primeProcess -> number;
		return primeProcess -> result = TRUE;
	}
	if (primeProcess -> number % 2 == 0) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = 2;
		return primeProcess -> result;
	}
	for (i = 3; i <= primeProcess -> number / 2; i+=2) {
		if (primeProcess -> number % i == 0) {
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			primeProcess -> divider = i;
			return primeProcess -> result;
		}
	}
	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	primeProcess -> divider = primeProcess -> number;
	return primeProcess -> result = TRUE;
}
static bool_t MethodSQRT(primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    primeProcess -> memoryOV = FALSE;

    DWT_CYCCNT = 0;
    if (primeProcess -> number == 2) {
    		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
    		primeProcess -> divider = primeProcess -> number;
    		return primeProcess -> result = TRUE;
    }
	if (primeProcess -> number % 2 == 0) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = 2;
		return primeProcess -> result;
	}
    for (i = 3; i * i <= primeProcess -> number; i+=2) {
		if (primeProcess -> number % i == 0) {
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			primeProcess -> divider = i;
			return primeProcess -> result;
		}
	}
    primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	primeProcess -> divider = primeProcess -> number;
	return primeProcess -> result = TRUE;
}
static bool_t Method6KPLUS1(primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    primeProcess -> memoryOV = FALSE;

    DWT_CYCCNT = 0;
	if(primeProcess -> number <= 3) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = primeProcess -> number;
		return primeProcess -> result = TRUE;
	}
	 if(primeProcess -> number % 2 == 0 || primeProcess -> number % 3 == 0) {
		 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		 if(primeProcess -> number % 2 == 0) primeProcess -> divider = 2;
		 else primeProcess -> divider = 3;
		 return primeProcess -> result;
	 }
	 for (i = 5; i * i <= primeProcess -> number; i+=6) {
		if ((primeProcess -> number % i == 0) || (primeProcess -> number % (i + 2) == 0)){
			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			if (primeProcess -> number % i == 0) primeProcess -> divider = i;
			else primeProcess -> divider = i + 2;
			return primeProcess -> result;
		}
	 }
	 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	 primeProcess -> divider = primeProcess -> number;
	 return primeProcess -> result = TRUE;
}
static bool_t MethodERATO(primepro_t *primeProcess){

    uint32_t i,j,sqrtNumber,iterationLimit;
    sqrtNumber = (uint32_t) (sqrt(primeProcess -> number));

    primeProcess -> result = FALSE;

    if ( sqrtNumber/2 > SEGMENT_SIZE){ //Chequeo de cantidad de memoria.
    	primeProcess -> memoryOV = TRUE;
    	iterationLimit = SEGMENT_SIZE;
    }
    else {
    	primeProcess -> memoryOV = FALSE;
		iterationLimit = sqrtNumber/2;
    }
    bool_t prime[SEGMENT_SIZE];
    primeProcess -> memory = sizeof(primepro_t) + 4*sizeof(uint32_t) + sqrtNumber/2 * sizeof(bool_t);
    memset(prime, TRUE, sizeof(prime));

    DWT_CYCCNT = 0;
    if ((primeProcess -> number == 2) || (primeProcess -> number == 3) || (primeProcess -> number == 5)) {
    	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = primeProcess -> number;
		return primeProcess -> result = TRUE;
    }
	else if (primeProcess -> number % 2 == 0) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = 2;
		return primeProcess -> result;
	}
	else {
		//SIEVE
		for (i = 3; i * i <= iterationLimit; i+=2){
			if (prime[i/2-1] == TRUE){
				for (j = i * i; j <= iterationLimit; j+=i*2)
					prime[j/2-1] = FALSE;
			}
		}
		// PRIMARITY_CHECK
		for (i = 0; i <= iterationLimit; i++){
			if (prime[i] == TRUE){
				if (primeProcess -> number % (2*(i+1)+1) == 0) {
					primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
					primeProcess -> divider = (2*(i+1)+1);
					return primeProcess -> result;
				}
			}
		}
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = primeProcess -> number;
		return primeProcess -> result = TRUE;
	}
}

static bool_t MethodEuler(primepro_t *primeProcess){

	uint32_t i,p,q,sqrtNumber,iterationLimit,max_q;
	sqrtNumber = (uint32_t) (sqrt(primeProcess -> number));

	primeProcess -> result = FALSE;

	if ( sqrtNumber/2 > SEGMENT_SIZE){ //Chequeo de cantidad de memoria.
		primeProcess -> memoryOV = TRUE;
		iterationLimit = SEGMENT_SIZE;
	}
	else {
		primeProcess -> memoryOV = FALSE;
		iterationLimit = sqrtNumber;
	}
	bool_t prime[SEGMENT_SIZE];
	primeProcess -> memory = sizeof(primepro_t) + 6*sizeof(uint32_t) + sqrtNumber/2 * sizeof(bool_t);
	memset(prime, TRUE, sizeof(prime));

	DWT_CYCCNT = 0;
	if (primeProcess -> number == 2) {
	    	primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			primeProcess -> divider = primeProcess -> number;
			return primeProcess -> result = TRUE;
	    }
	else if (primeProcess -> number % 2 == 0) {
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = 2;
		return primeProcess -> result;
	}
	else {
		//SIEVE
		for (p = 3; p <= iterationLimit; p += 2){
			if (prime[p/2-1]){
				max_q = (iterationLimit / p);
				if (max_q % 2 == 0) max_q--;
				for (q = max_q; q >= p; q -= 2){
					if (prime[q/2-1]) prime[((p*q)/2-1)] = FALSE;
				}
			}
		}
		//PRIMARY TEST
		for (p = 3; p <= iterationLimit; p+=2){
			if (prime[p/2-1] == TRUE){
				if (primeProcess -> number % p == 0) {
					primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
					primeProcess -> divider = p;
					return primeProcess -> result;
				}
			}
		}
		primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		primeProcess -> divider = primeProcess -> number;
		return primeProcess -> result = TRUE;
	}
}

static bool_t Method30K (primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    DWT_CYCCNT = 0;
    if(primeProcess -> number <= 30){
    	return MethodSQRT(primeProcess);
    }
	if(primeProcess -> number % 2 == 0 || primeProcess -> number % 3 == 0 || primeProcess -> number % 5 == 0) {
		 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		 if(primeProcess -> number % 2 == 0) primeProcess -> divider = 2;
		 else if(primeProcess -> number % 3 == 0) primeProcess -> divider = 3;
		 else primeProcess -> divider = 5;
		 return primeProcess -> result;
	 }

	 for (i = 7; i * i <= primeProcess -> number; i+=30) {
		if 	((	primeProcess -> number % i == 0)
			||(	primeProcess -> number % (i + 4) == 0)
			||(	primeProcess -> number % (i + 6) == 0)
			||(	primeProcess -> number % (i + 10) == 0)
			||(	primeProcess -> number % (i + 12) == 0)
			||(	primeProcess -> number % (i + 16) == 0)
			||(	primeProcess -> number % (i + 22) == 0)
			||(	primeProcess -> number % (i + 24) == 0)){

			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			if 		(primeProcess -> number % i == 0) 			primeProcess -> divider = i;
			else if (primeProcess -> number % (i + 4) == 0) 	primeProcess -> divider = i + 4;
			else if (primeProcess -> number % (i + 6) == 0) 	primeProcess -> divider = i + 6;
			else if (primeProcess -> number % (i + 10) == 0) 	primeProcess -> divider = i + 10;
			else if (primeProcess -> number % (i + 12) == 0) 	primeProcess -> divider = i + 12;
			else if (primeProcess -> number % (i + 16) == 0) 	primeProcess -> divider = i + 16;
			else if (primeProcess -> number % (i + 22) == 0) 	primeProcess -> divider = i + 22;
			else primeProcess -> divider = i + 24;
			return primeProcess -> result;
		}
	 }
	 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	 primeProcess -> divider = primeProcess -> number;
	 return primeProcess -> result = TRUE;
}

static bool_t Method210K (primepro_t *primeProcess){

    uint64_t i;

    primeProcess -> memory = sizeof(primepro_t) + sizeof(uint64_t);
    primeProcess -> result = FALSE;
    DWT_CYCCNT = 0;
    if(primeProcess -> number <= 210){
    	return MethodSQRT(primeProcess);
    }
	if	(	primeProcess -> number % 2 == 0 ||
			primeProcess -> number % 3 == 0 ||
			primeProcess -> number % 5 == 0 ||
			primeProcess -> number % 7 == 0)  {
		 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
		 if(		primeProcess -> number % 2 == 0) primeProcess -> divider = 2;
		 else if(	primeProcess -> number % 3 == 0) primeProcess -> divider = 3;
		 else if(	primeProcess -> number % 5 == 0) primeProcess -> divider = 5;
		 else 		primeProcess -> divider = 7;
		 return primeProcess -> result;
	 }

	 for (i = 11; i * i <= primeProcess -> number; i+=210) {
		if 	((	primeProcess -> number % i == 0)
			||(	primeProcess -> number % (i + 2) == 0)
			||(	primeProcess -> number % (i + 6) == 0)
			||(	primeProcess -> number % (i + 8) == 0)
			||(	primeProcess -> number % (i + 12) == 0)
			||(	primeProcess -> number % (i + 18) == 0)
			||(	primeProcess -> number % (i + 20) == 0)
			||(	primeProcess -> number % (i + 26) == 0)
			||(	primeProcess -> number % (i + 30) == 0)
			||(	primeProcess -> number % (i + 32) == 0)
			||(	primeProcess -> number % (i + 36) == 0)
			||(	primeProcess -> number % (i + 42) == 0)
			||(	primeProcess -> number % (i + 48) == 0)
			||(	primeProcess -> number % (i + 50) == 0)
			||(	primeProcess -> number % (i + 56) == 0)
			||(	primeProcess -> number % (i + 60) == 0)
			||(	primeProcess -> number % (i + 62) == 0)
			||(	primeProcess -> number % (i + 68) == 0)
			||(	primeProcess -> number % (i + 72) == 0)
			||(	primeProcess -> number % (i + 78) == 0)
			||(	primeProcess -> number % (i + 86) == 0)
			||(	primeProcess -> number % (i + 90) == 0)
			||(	primeProcess -> number % (i + 92) == 0)
			||(	primeProcess -> number % (i + 96) == 0)
			||(	primeProcess -> number % (i + 98) == 0)
			||(	primeProcess -> number % (i + 102) == 0)
			||(	primeProcess -> number % (i + 110) == 0)
			||(	primeProcess -> number % (i + 116) == 0)
			||(	primeProcess -> number % (i + 120) == 0)
			||(	primeProcess -> number % (i + 126) == 0)
			||(	primeProcess -> number % (i + 128) == 0)
			||(	primeProcess -> number % (i + 132) == 0)
			||(	primeProcess -> number % (i + 138) == 0)
			||(	primeProcess -> number % (i + 140) == 0)
			||(	primeProcess -> number % (i + 146) == 0)
			||(	primeProcess -> number % (i + 152) == 0)
			||(	primeProcess -> number % (i + 156) == 0)
			||(	primeProcess -> number % (i + 158) == 0)
			||(	primeProcess -> number % (i + 162) == 0)
			||(	primeProcess -> number % (i + 168) == 0)
			||(	primeProcess -> number % (i + 170) == 0)
			||(	primeProcess -> number % (i + 176) == 0)
			||(	primeProcess -> number % (i + 180) == 0)
			||(	primeProcess -> number % (i + 182) == 0)
			||(	primeProcess -> number % (i + 186) == 0)
			||(	primeProcess -> number % (i + 188) == 0)
			||(	primeProcess -> number % (i + 198) == 0)){

			primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
			if 		(	primeProcess -> number % 	i 		  == 0)	primeProcess -> divider = i;
            else if	(	primeProcess -> number % (	i + 2	) == 0) primeProcess -> divider = i + 2;
			else if	(	primeProcess -> number % (	i + 6	) == 0) primeProcess -> divider = i + 6;
			else if	(	primeProcess -> number % (	i + 8	) == 0) primeProcess -> divider = i + 8;
			else if	(	primeProcess -> number % (	i + 12	) == 0) primeProcess -> divider = i + 12;
			else if	(	primeProcess -> number % (	i + 18	) == 0) primeProcess -> divider = i + 18;
			else if	(	primeProcess -> number % (	i + 20	) == 0) primeProcess -> divider = i + 20;
			else if	(	primeProcess -> number % (	i + 26	) == 0) primeProcess -> divider = i + 26;
			else if	(	primeProcess -> number % (	i + 30	) == 0) primeProcess -> divider = i + 30;
			else if	(	primeProcess -> number % (	i + 32	) == 0) primeProcess -> divider = i + 32;
			else if	(	primeProcess -> number % (	i + 36	) == 0) primeProcess -> divider = i + 36;
			else if	(	primeProcess -> number % (	i + 42	) == 0) primeProcess -> divider = i + 42;
			else if	(	primeProcess -> number % (	i + 48	) == 0) primeProcess -> divider = i + 48;
			else if	(	primeProcess -> number % (	i + 50	) == 0) primeProcess -> divider = i + 50;
			else if	(	primeProcess -> number % (	i + 56	) == 0) primeProcess -> divider = i + 56;
			else if	(	primeProcess -> number % (	i + 60	) == 0) primeProcess -> divider = i + 60;
			else if	(	primeProcess -> number % (	i + 62	) == 0) primeProcess -> divider = i + 62;
			else if	(	primeProcess -> number % (	i + 68	) == 0) primeProcess -> divider = i + 68;
			else if	(	primeProcess -> number % (	i + 72	) == 0) primeProcess -> divider = i + 72;
			else if	(	primeProcess -> number % (	i + 78	) == 0) primeProcess -> divider = i + 78;
			else if	(	primeProcess -> number % (	i + 86	) == 0) primeProcess -> divider = i + 86;
			else if	(	primeProcess -> number % (	i + 90	) == 0) primeProcess -> divider = i + 90;
			else if	(	primeProcess -> number % (	i + 92	) == 0) primeProcess -> divider = i + 92;
			else if	(	primeProcess -> number % (	i + 96	) == 0) primeProcess -> divider = i + 96;
			else if	(	primeProcess -> number % (	i + 98	) == 0) primeProcess -> divider = i + 98;
			else if	(	primeProcess -> number % (	i + 102	) == 0) primeProcess -> divider = i + 102;
			else if	(	primeProcess -> number % (	i + 110	) == 0) primeProcess -> divider = i + 110;
			else if	(	primeProcess -> number % (	i + 116	) == 0) primeProcess -> divider = i + 116;
			else if	(	primeProcess -> number % (	i + 120	) == 0) primeProcess -> divider = i + 120;
			else if	(	primeProcess -> number % (	i + 126	) == 0) primeProcess -> divider = i + 126;
			else if	(	primeProcess -> number % (	i + 128	) == 0) primeProcess -> divider = i + 128;
			else if	(	primeProcess -> number % (	i + 132	) == 0) primeProcess -> divider = i + 132;
			else if	(	primeProcess -> number % (	i + 138	) == 0) primeProcess -> divider = i + 138;
			else if	(	primeProcess -> number % (	i + 140	) == 0) primeProcess -> divider = i + 140;
			else if	(	primeProcess -> number % (	i + 146	) == 0) primeProcess -> divider = i + 146;
			else if	(	primeProcess -> number % (	i + 152	) == 0) primeProcess -> divider = i + 152;
			else if	(	primeProcess -> number % (	i + 156	) == 0) primeProcess -> divider = i + 156;
			else if	(	primeProcess -> number % (	i + 158	) == 0) primeProcess -> divider = i + 158;
			else if	(	primeProcess -> number % (	i + 162	) == 0) primeProcess -> divider = i + 162;
			else if	(	primeProcess -> number % (	i + 168	) == 0) primeProcess -> divider = i + 168;
			else if	(	primeProcess -> number % (	i + 170	) == 0) primeProcess -> divider = i + 170;
			else if	(	primeProcess -> number % (	i + 176	) == 0) primeProcess -> divider = i + 176;
			else if	(	primeProcess -> number % (	i + 180	) == 0) primeProcess -> divider = i + 180;
			else if	(	primeProcess -> number % (	i + 182	) == 0) primeProcess -> divider = i + 182;
			else if	(	primeProcess -> number % (	i + 186	) == 0) primeProcess -> divider = i + 186;
			else if	(	primeProcess -> number % (	i + 188	) == 0) primeProcess -> divider = i + 188;
			else primeProcess -> divider = i + 198;
			return primeProcess -> result;
		}
	 }
	 primeProcess -> time = ((uint64_t) DWT_CYCCNT * (uint64_t) 1000000000)/ (uint64_t) SystemCoreClock;
	 primeProcess -> divider = primeProcess -> number;
	 return primeProcess -> result = TRUE;
}
