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

bool_t processBF(uint64_t number, mtd_t metodo, uint64_t * time)
{
    bool_t ret_val = 0;
    uint64_t i,p,q;
    uint32_t sqrt_number,max_q;
    bool_t * prime;
    prime = malloc(2 * sizeof(bool_t));
    // Memoria para Steve of Eratosthenes
    if (metodo == SIEVE_OF_ERATOSTHENES_METHOD) {
	sqrt_number = (uint32_t) (sqrt(number));
	prime = realloc(prime, sqrt_number+1 * sizeof(bool_t));
	memset(prime, TRUE, sizeof(prime));
	}
    // Memoria para Steve of Euler
    if (metodo == SIEVE_OF_EULER_METHOD) {
	sqrt_number = (uint32_t) (sqrt(number));
	prime = realloc(prime, sqrt_number+1 * sizeof(bool_t));
	memset(prime, FALSE, sizeof(prime));
	}
    //Declaraciones para calcular tiempo
    uint64_t * H_DWT_DEMCR 	= (uint64_t *)0xE000EDFC;// chequear volatile
    uint64_t * H_DWT_CTRL 	= (uint64_t *)0xE0001000;// chequear volatile
    uint64_t * H_DWT_CYCCNT = (uint64_t *)0xE0001004;// chequear volatile
    *H_DWT_DEMCR |= 1<<24;//
    *H_DWT_CTRL |= 1;

	// Chequeo que el numero sea mayor que 2 para poder aplicar el algoritmo
	if (number >= 2) {
		switch (metodo) {
			case BRUTE_FORCE_METHOD:
				cyclesCounterReset();
				for (i = 2; i <= number; ++i){
					if (number % i == 0){
						if (i == number){
							ret_val = 1;
							*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
							return ret_val;
						}
						else {
							*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
							 return ret_val;
						}
					}
				}
				break;
			case PAIR_LESS_METHOD:
				cyclesCounterReset();
				for (i = 2; i <= number / 2; ++i) {
					if (number % i == 0) {
						*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
						return ret_val;
					}
				}
				ret_val = 1;
				*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
				return ret_val;
				break;
			case SQRT_METHOD:
				cyclesCounterReset();
				for (i = 2; i * i <= number; ++i) {
					if (number % i == 0) {
						*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
						return ret_val;
					}
				}
				ret_val = 1;
				*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
				return ret_val;
				break;
			case SQRT_6KPLUS1_METHOD:
				cyclesCounterReset();
				if(number <= 3) {
					ret_val = 1;
					*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
					return ret_val;
				}
				 if(number % 2 == 0 || number % 3 == 0) {
					 *time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
					 return ret_val;
				 }
				 for (i = 5; i * i <= number; i = i + 6) {
					if (number % i == 0) {
						*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
						return ret_val;
					}
				 }
				 ret_val = 1;
				 *time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
				 return ret_val;
				 break;
			case SIEVE_OF_ERATOSTHENES_METHOD:
				cyclesCounterReset();
				for (p = 2; p * p <= sqrt_number; p++){
					if (prime[p] == TRUE){
						for (i = p * p; i <= sqrt_number; i += p)
							prime[i] = FALSE;
					}
				}
				for (p = 2; p <= sqrt_number; p++){
					if (prime[p] == TRUE){
						if (number % p == 0) {
							*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
							free(prime);
							return ret_val;
						}
					}
				}
				ret_val = 1;
				*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
				free(prime);
				return ret_val;
				break;
			case SIEVE_OF_EULER_METHOD:
				cyclesCounterReset();
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
						if (number % p == 0) {
							*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
							free(prime);
							return ret_val;
						}
					}
				}
				ret_val = 1;
				*time = (cyclesCounterRead()/(uint64_t)(SystemCoreClock/100000000))*10;
				free(prime);
				return ret_val;
				break;
			default:
			break;
		}
   }
   else {
	    printf("Numero ");
		printf("%" PRIu64, number);
		printf(" no puede ser procesado\r\n");
   }
   return ret_val;
}

