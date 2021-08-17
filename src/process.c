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
#include "time.h"

/*=============================================================================
* Funcion: process -> Selector de metodo a ejecutar segun estructura
* primeProcess.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

bool_t process(primepro_t *primeProcess)
{
	bool_t ret_val = 0;

	// Chequeo que el numero sea mayor que 2 para poder aplicar el algoritmo
	if (primeProcess->number >= 2)
	{
		// Selección de la función a ejecutar
		switch (primeProcess->method)
		{
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
		case SIEVE_OF_SUNDARAM_METHOD:
			ret_val = MethodSundaram(primeProcess);
			break;
		case SIEVE_OF_ATKIN_METHOD:
			ret_val = MethodAtkin(primeProcess);
			break;
		case FERMAT_METHOD:
			ret_val = MethodFermat(primeProcess);
		default:
			break;
		}
	}
	return ret_val;
}

/*=============================================================================
* Funcion: MethodBF -> Metodo de Fuerza Bruta
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodBF(primepro_t *primeProcess)
{
	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;

	setTime(0);
	// Itera hasta el valor de numero sobre dos de uno en uno.
	// Si encuentra un numero en que el resto es cero sale.
	for (i = 2; i <= primeProcess->number / 2; ++i)
	{
		if (primeProcess->number % i == 0)
		{
			getTime(primeProcess);
			primeProcess->divider = i;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
	;
}

/*=============================================================================
* Funcion: MethodPL -> Metodo de chequeo sin pares
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodPL(primepro_t *primeProcess)
{

	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;

	setTime(0);
	// Chequea si es dos
	if (primeProcess->number == 2)
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par
	if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	// Itera hasta el valor de numero sobre dos para todos los impares.
	// Si encuentra un numero en que el resto es cero sale.
	for (i = 3; i <= primeProcess->number / 2; i += 2)
	{
		if (primeProcess->number % i == 0)
		{
			getTime(primeProcess);
			primeProcess->divider = i;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
}

/*=============================================================================
* Funcion: MethodSQRT -> Metodo de chequeo sin pares y limite SQRT(numero)
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodSQRT(primepro_t *primeProcess)
{

	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;

	setTime(0);
	// Chequea si es dos
	if (primeProcess->number == 2)
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par
	if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	// Itera hasta el valor de raiz cuadrada del numero para todos los impares.
	// Si encuentra un numero en que el resto es cero sale.
	for (i = 3; i * i <= primeProcess->number; i += 2)
	{
		if (primeProcess->number % i == 0)
		{
			getTime(primeProcess);
			primeProcess->divider = i;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
}

/*=============================================================================
* Funcion: Method6KPLUS1 -> Usa la propiedad 6K+/-1 de los primos mayores que 3.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t Method6KPLUS1(primepro_t *primeProcess)
{

	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;

	setTime(0);
	// Chequea si es dos o tres.
	if (primeProcess->number <= 3)
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par o múltiplo de tres
	if (primeProcess->number % 2 == 0 || primeProcess->number % 3 == 0)
	{
		getTime(primeProcess);
		if (primeProcess->number % 2 == 0)
			primeProcess->divider = 2;
		else
			primeProcess->divider = 3;
		return primeProcess->result;
	}
	// Itera para todos los 5k y saca el resto de ese numero y del ese numero mas 2.
	// Si encuentra un numero en que el resto es cero sale.
	for (i = 5; i * i <= primeProcess->number; i += 6)
	{
		if ((primeProcess->number % i == 0) || (primeProcess->number % (i + 2) == 0))
		{
			getTime(primeProcess);
			if (primeProcess->number % i == 0)
				primeProcess->divider = i;
			else
				primeProcess->divider = i + 2;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
}

/*=============================================================================
* Funcion: MethodERATO -> Construye todos los primos hasta la raiz cuadrada del
* numero a probar utilizando el telar de Eratosthenes.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodERATO(primepro_t *primeProcess)
{

	uint32_t i, j, sqrtNumber, iterationLimit;
	sqrtNumber = (uint32_t)(sqrt(primeProcess->number));

	primeProcess->result = FALSE;

	// Chequeo de cantidad de memoria.
	// Se podría hacer un algoritmo segmentado para salvar este problema.
	if (sqrtNumber / 2 > SEGMENT_SIZE)
	{
		primeProcess->memoryOV = TRUE;
		iterationLimit = SEGMENT_SIZE;
	}
	else
	{
		primeProcess->memoryOV = FALSE;
		iterationLimit = sqrtNumber / 2;
	}
	bool_t prime[SEGMENT_SIZE];
	primeProcess->memory = sizeof(primepro_t) + 4 * sizeof(uint32_t) + sqrtNumber / 2 * sizeof(bool_t);
	memset(prime, TRUE, sizeof(prime));

	setTime(0);
	// Chequea si es dos, tres o cinco.
	if ((primeProcess->number == 2) || (primeProcess->number == 3) || (primeProcess->number == 5))
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par
	else if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	else
	{
		//SIEVE de Eratosthenes para numeros impares.
		for (i = 3; i * i <= iterationLimit; i += 2)
		{
			if (prime[i / 2 - 1] == TRUE)
			{
				for (j = i * i; j <= iterationLimit; j += i * 2)
					prime[j / 2 - 1] = FALSE;
			}
		}
		// Chequeo de "primariedad"
		// Sale si encuentra un divisor.
		for (i = 0; i <= iterationLimit; i++)
		{
			if (prime[i] == TRUE)
			{
				if (primeProcess->number % (2 * (i + 1) + 1) == 0)
				{
					getTime(primeProcess);
					primeProcess->divider = (2 * (i + 1) + 1);
					return primeProcess->result;
				}
			}
		}
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
}

/*=============================================================================
* Funcion: MethodEuler -> Construye todos los primos hasta la raiz cuadrada del
* numero a probar utilizando el telar de Euler.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
* 							-> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodEuler(primepro_t *primeProcess)
{

	uint32_t i, p, q, sqrtNumber, iterationLimit, max_q;
	sqrtNumber = (uint32_t)(sqrt(primeProcess->number));

	primeProcess->result = FALSE;

	// Chequeo de cantidad de memoria.
	// Se podría hacer un algoritmo segmentado para salvar este problema.
	if (sqrtNumber / 2 > SEGMENT_SIZE)
	{
		primeProcess->memoryOV = TRUE;
		iterationLimit = SEGMENT_SIZE;
	}
	else
	{
		primeProcess->memoryOV = FALSE;
		iterationLimit = sqrtNumber;
	}
	bool_t prime[SEGMENT_SIZE];
	primeProcess->memory = sizeof(primepro_t) + 6 * sizeof(uint32_t) + sqrtNumber / 2 * sizeof(bool_t);
	memset(prime, TRUE, sizeof(prime));

	setTime(0);
	// Chequea si es dos
	if (primeProcess->number == 2)
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par
	else if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	else
	{
		//SIEVE de Euler para numeros impares
		for (p = 3; p <= iterationLimit; p += 2)
		{
			if (prime[p / 2 - 1])
			{
				max_q = (iterationLimit / p);
				if (max_q % 2 == 0)
					max_q--;
				for (q = max_q; q >= p; q -= 2)
				{
					if (prime[q / 2 - 1])
						prime[((p * q) / 2 - 1)] = FALSE;
				}
			}
		}
		// Chequeo de "primariedad"
		// Sale si encuentra un divisor.
		for (p = 3; p <= iterationLimit; p += 2)
		{
			if (prime[p / 2 - 1] == TRUE)
			{
				if (primeProcess->number % p == 0)
				{
					getTime(primeProcess);
					primeProcess->divider = p;
					return primeProcess->result;
				}
			}
		}
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
}

/*=============================================================================
* Funcion: Method30K -> Usa la propiedad 30K+/- de los primos mayores que 5.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t Method30K(primepro_t *primeProcess)
{

	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;

	setTime(0);
	// Metodo solo es válido para numeros mayores que 30
	// Se usa el MethodSQRT
	if (primeProcess->number <= 30)
	{
		return MethodSQRT(primeProcess);
	}
	// Chequeo si es divisible por 2,3 o 5.
	if (primeProcess->number % 2 == 0 || primeProcess->number % 3 == 0 || primeProcess->number % 5 == 0)
	{
		getTime(primeProcess);
		if (primeProcess->number % 2 == 0)
			primeProcess->divider = 2;
		else if (primeProcess->number % 3 == 0)
			primeProcess->divider = 3;
		else
			primeProcess->divider = 5;
		return primeProcess->result;
	}

	// Itera para todos los 30k y saca el resto segun condiciones de primariedad.
	// Si encuentra un numero en que el resto es cero sale
	for (i = 7; i * i <= primeProcess->number; i += 30)
	{
		if ((primeProcess->number % i == 0) || (primeProcess->number % (i + 4) == 0) || (primeProcess->number % (i + 6) == 0) || (primeProcess->number % (i + 10) == 0) || (primeProcess->number % (i + 12) == 0) || (primeProcess->number % (i + 16) == 0) || (primeProcess->number % (i + 22) == 0) || (primeProcess->number % (i + 24) == 0))
		{

			getTime(primeProcess);
			if (primeProcess->number % i == 0)
				primeProcess->divider = i;
			else if (primeProcess->number % (i + 4) == 0)
				primeProcess->divider = i + 4;
			else if (primeProcess->number % (i + 6) == 0)
				primeProcess->divider = i + 6;
			else if (primeProcess->number % (i + 10) == 0)
				primeProcess->divider = i + 10;
			else if (primeProcess->number % (i + 12) == 0)
				primeProcess->divider = i + 12;
			else if (primeProcess->number % (i + 16) == 0)
				primeProcess->divider = i + 16;
			else if (primeProcess->number % (i + 22) == 0)
				primeProcess->divider = i + 22;
			else
				primeProcess->divider = i + 24;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
}

/*=============================================================================
* Funcion: Method210K -> Usa la propiedad 210K+/- de los primos mayores que 7.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
* 							-> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t Method210K(primepro_t *primeProcess)
{

	uint64_t i;

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint64_t);
	primeProcess->result = FALSE;

	setTime(0);
	// Metodo solo es válido para numeros mayores que 210
	// Se usa el MethodSQRT
	if (primeProcess->number <= 210)
	{
		return MethodSQRT(primeProcess);
	}
	// Chequeo si es divisible por 2,3,5 o 7.
	if (primeProcess->number % 2 == 0 ||
		primeProcess->number % 3 == 0 ||
		primeProcess->number % 5 == 0 ||
		primeProcess->number % 7 == 0)
	{
		getTime(primeProcess);
		if (primeProcess->number % 2 == 0)
			primeProcess->divider = 2;
		else if (primeProcess->number % 3 == 0)
			primeProcess->divider = 3;
		else if (primeProcess->number % 5 == 0)
			primeProcess->divider = 5;
		else
			primeProcess->divider = 7;
		return primeProcess->result;
	}

	// Itera para todos los 30k y saca el resto segun condiciones de primariedad.
	// Si encuentra un numero en que el resto es cero sale
	for (i = 11; i * i <= primeProcess->number; i += 210)
	{
		if ((primeProcess->number % i == 0) || (primeProcess->number % (i + 2) == 0) || (primeProcess->number % (i + 6) == 0) || (primeProcess->number % (i + 8) == 0) || (primeProcess->number % (i + 12) == 0) || (primeProcess->number % (i + 18) == 0) || (primeProcess->number % (i + 20) == 0) || (primeProcess->number % (i + 26) == 0) || (primeProcess->number % (i + 30) == 0) || (primeProcess->number % (i + 32) == 0) || (primeProcess->number % (i + 36) == 0) || (primeProcess->number % (i + 42) == 0) || (primeProcess->number % (i + 48) == 0) || (primeProcess->number % (i + 50) == 0) || (primeProcess->number % (i + 56) == 0) || (primeProcess->number % (i + 60) == 0) || (primeProcess->number % (i + 62) == 0) || (primeProcess->number % (i + 68) == 0) || (primeProcess->number % (i + 72) == 0) || (primeProcess->number % (i + 78) == 0) || (primeProcess->number % (i + 86) == 0) || (primeProcess->number % (i + 90) == 0) || (primeProcess->number % (i + 92) == 0) || (primeProcess->number % (i + 96) == 0) || (primeProcess->number % (i + 98) == 0) || (primeProcess->number % (i + 102) == 0) || (primeProcess->number % (i + 110) == 0) || (primeProcess->number % (i + 116) == 0) || (primeProcess->number % (i + 120) == 0) || (primeProcess->number % (i + 126) == 0) || (primeProcess->number % (i + 128) == 0) || (primeProcess->number % (i + 132) == 0) || (primeProcess->number % (i + 138) == 0) || (primeProcess->number % (i + 140) == 0) || (primeProcess->number % (i + 146) == 0) || (primeProcess->number % (i + 152) == 0) || (primeProcess->number % (i + 156) == 0) || (primeProcess->number % (i + 158) == 0) || (primeProcess->number % (i + 162) == 0) || (primeProcess->number % (i + 168) == 0) || (primeProcess->number % (i + 170) == 0) || (primeProcess->number % (i + 176) == 0) || (primeProcess->number % (i + 180) == 0) || (primeProcess->number % (i + 182) == 0) || (primeProcess->number % (i + 186) == 0) || (primeProcess->number % (i + 188) == 0) || (primeProcess->number % (i + 198) == 0))
		{

			getTime(primeProcess);
			if (primeProcess->number % i == 0)
				primeProcess->divider = i;
			else if (primeProcess->number % (i + 2) == 0)
				primeProcess->divider = i + 2;
			else if (primeProcess->number % (i + 6) == 0)
				primeProcess->divider = i + 6;
			else if (primeProcess->number % (i + 8) == 0)
				primeProcess->divider = i + 8;
			else if (primeProcess->number % (i + 12) == 0)
				primeProcess->divider = i + 12;
			else if (primeProcess->number % (i + 18) == 0)
				primeProcess->divider = i + 18;
			else if (primeProcess->number % (i + 20) == 0)
				primeProcess->divider = i + 20;
			else if (primeProcess->number % (i + 26) == 0)
				primeProcess->divider = i + 26;
			else if (primeProcess->number % (i + 30) == 0)
				primeProcess->divider = i + 30;
			else if (primeProcess->number % (i + 32) == 0)
				primeProcess->divider = i + 32;
			else if (primeProcess->number % (i + 36) == 0)
				primeProcess->divider = i + 36;
			else if (primeProcess->number % (i + 42) == 0)
				primeProcess->divider = i + 42;
			else if (primeProcess->number % (i + 48) == 0)
				primeProcess->divider = i + 48;
			else if (primeProcess->number % (i + 50) == 0)
				primeProcess->divider = i + 50;
			else if (primeProcess->number % (i + 56) == 0)
				primeProcess->divider = i + 56;
			else if (primeProcess->number % (i + 60) == 0)
				primeProcess->divider = i + 60;
			else if (primeProcess->number % (i + 62) == 0)
				primeProcess->divider = i + 62;
			else if (primeProcess->number % (i + 68) == 0)
				primeProcess->divider = i + 68;
			else if (primeProcess->number % (i + 72) == 0)
				primeProcess->divider = i + 72;
			else if (primeProcess->number % (i + 78) == 0)
				primeProcess->divider = i + 78;
			else if (primeProcess->number % (i + 86) == 0)
				primeProcess->divider = i + 86;
			else if (primeProcess->number % (i + 90) == 0)
				primeProcess->divider = i + 90;
			else if (primeProcess->number % (i + 92) == 0)
				primeProcess->divider = i + 92;
			else if (primeProcess->number % (i + 96) == 0)
				primeProcess->divider = i + 96;
			else if (primeProcess->number % (i + 98) == 0)
				primeProcess->divider = i + 98;
			else if (primeProcess->number % (i + 102) == 0)
				primeProcess->divider = i + 102;
			else if (primeProcess->number % (i + 110) == 0)
				primeProcess->divider = i + 110;
			else if (primeProcess->number % (i + 116) == 0)
				primeProcess->divider = i + 116;
			else if (primeProcess->number % (i + 120) == 0)
				primeProcess->divider = i + 120;
			else if (primeProcess->number % (i + 126) == 0)
				primeProcess->divider = i + 126;
			else if (primeProcess->number % (i + 128) == 0)
				primeProcess->divider = i + 128;
			else if (primeProcess->number % (i + 132) == 0)
				primeProcess->divider = i + 132;
			else if (primeProcess->number % (i + 138) == 0)
				primeProcess->divider = i + 138;
			else if (primeProcess->number % (i + 140) == 0)
				primeProcess->divider = i + 140;
			else if (primeProcess->number % (i + 146) == 0)
				primeProcess->divider = i + 146;
			else if (primeProcess->number % (i + 152) == 0)
				primeProcess->divider = i + 152;
			else if (primeProcess->number % (i + 156) == 0)
				primeProcess->divider = i + 156;
			else if (primeProcess->number % (i + 158) == 0)
				primeProcess->divider = i + 158;
			else if (primeProcess->number % (i + 162) == 0)
				primeProcess->divider = i + 162;
			else if (primeProcess->number % (i + 168) == 0)
				primeProcess->divider = i + 168;
			else if (primeProcess->number % (i + 170) == 0)
				primeProcess->divider = i + 170;
			else if (primeProcess->number % (i + 176) == 0)
				primeProcess->divider = i + 176;
			else if (primeProcess->number % (i + 180) == 0)
				primeProcess->divider = i + 180;
			else if (primeProcess->number % (i + 182) == 0)
				primeProcess->divider = i + 182;
			else if (primeProcess->number % (i + 186) == 0)
				primeProcess->divider = i + 186;
			else if (primeProcess->number % (i + 188) == 0)
				primeProcess->divider = i + 188;
			else
				primeProcess->divider = i + 198;
			return primeProcess->result;
		}
	}
	getTime(primeProcess);
	primeProcess->divider = primeProcess->number;
	return primeProcess->result = TRUE;
}

/*=============================================================================
* Funcion: MethodSundaram -> Construye todos los primos hasta la raiz cuadrada del
* numero a probar utilizando el telar de Sundaram.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodSundaram(primepro_t *primeProcess)
{

	uint32_t i, j, sqrtNumber, iterationLimit;
	sqrtNumber = (uint32_t)(sqrt(primeProcess->number));

	primeProcess->result = FALSE;

	// Chequeo de cantidad de memoria.
	// Se podría hacer un algoritmo segmentado para salvar este problema.
	if ((sqrtNumber - 1) / 2 > SEGMENT_SIZE)
	{ //Chequeo de cantidad de memoria.
		primeProcess->memoryOV = TRUE;
		iterationLimit = SEGMENT_SIZE;
	}
	else
	{
		primeProcess->memoryOV = FALSE;
		iterationLimit = (sqrtNumber - 1) / 2;
	}
	bool_t prime[SEGMENT_SIZE];
	primeProcess->memory = sizeof(primepro_t) + 4 * sizeof(uint32_t) + iterationLimit * sizeof(bool_t);
	memset(prime, FALSE, sizeof(prime));

	setTime(0);
	// Chequea si es dos
	if (primeProcess->number == 2)
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequeo si es par
	else if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	else
	{
		//SIEVE de Sundaram
		for (i = 1; i <= iterationLimit; i++)
		{
			for (j = i; i + j + 2 * i * j <= iterationLimit; j++)
			{
				prime[i + j + 2 * i * j] = TRUE;
			}
		}
		// Chequeo de "primariedad"
		// Sale si encuentra un divisor.
		for (i = 1; i <= iterationLimit; i++)
		{
			if (prime[i] == FALSE)
			{
				if (primeProcess->number % (2 * i + 1) == 0)
				{
					getTime(primeProcess);
					primeProcess->divider = (2 * i + 1);
					return primeProcess->result;
				}
			}
		}
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
}

/*=============================================================================
* Funcion: MethodAtkin -> Construye todos los primos hasta la raiz cuadrada del
* numero a probar utilizando el telar de Atkin.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodAtkin(primepro_t *primeProcess)
{

	uint32_t a, x, y, i, r, n, sqrtNumber, iterationLimit;
	sqrtNumber = (uint32_t)(sqrt(primeProcess->number));

	primeProcess->result = FALSE;

	// Chequeo de cantidad de memoria.
	// Se podría hacer un algoritmo segmentado para salvar este problema.
	if (sqrtNumber > SEGMENT_SIZE)
	{
		primeProcess->memoryOV = TRUE;
		iterationLimit = SEGMENT_SIZE;
	}
	else
	{
		primeProcess->memoryOV = FALSE;
		iterationLimit = sqrtNumber;
	}
	bool_t prime[SEGMENT_SIZE];
	primeProcess->memory = sizeof(primepro_t) + 7 * sizeof(uint32_t) + iterationLimit * sizeof(bool_t);
	memset(prime, FALSE, sizeof(prime));

	setTime(0);
	// Chequeo si es dos o tres.
	if ((primeProcess->number == 2) || (primeProcess->number == 3))
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	// Chequea si es par
	else if (primeProcess->number % 2 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 2;
		return primeProcess->result;
	}
	// Chequea si es multiplo de tres.
	else if (primeProcess->number % 3 == 0)
	{
		getTime(primeProcess);
		primeProcess->divider = 3;
		return primeProcess->result;
	}
	else
	{
		//SIEVE of Atkin
		for (x = 1; x * x < iterationLimit; x++)
		{
			for (y = 1; y * y < iterationLimit; y++)
			{
				// Resolución de ecuaciones de primaridad
				n = (4 * x * x) + (y * y);
				if (n <= iterationLimit && (n % 12 == 1 || n % 12 == 5))
					prime[n] ^= TRUE;

				n = (3 * x * x) + (y * y);
				if (n <= iterationLimit && n % 12 == 7)
					prime[n] ^= TRUE;

				n = (3 * x * x) - (y * y);
				if (x > y && n <= iterationLimit && n % 12 == 11)
					prime[n] ^= TRUE;
			}
		}

		/* Se comentar porque hace más lento al metodo.
		 * Se testean alguno números de más pero es menos costoso
		//Eliminando los múltiples cuadrados de primos.
		for (int r = 5; r <= iterationLimit; r+=2)
			if (prime[r])
				for (int i = r*r; i < iterationLimit; i += r*r)
					prime[i] = false;*/

		// Chequeo de "primariedad"
		// Sale si encuentra un divisor.
		for (a = 5; a <= iterationLimit; a += 2)
		{
			if (prime[a])
			{
				if (primeProcess->number % a == 0)
				{
					getTime(primeProcess);
					primeProcess->divider = a;
					return primeProcess->result;
				}
			}
		}
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
}

// Calcula (a^n)%p sin utilizar POW
static uint64_t power(uint64_t a, uint64_t n, uint64_t p)
{
	uint64_t res = 1; // Inicializa el resultado
	//a = a % p;

	while (n > 0)
	{
		if (n % 2 == 1)
			res = mulmod(res, a, p);
		a = mulmod(a, a, p);
		n = n / 2;
	}
	return res;
}

// To compute (a * b) % mod
static uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod)
{
	uint64_t res = 0; // Initialize result
	//a = a % mod;

	while (b > 0)
	{
		if (b % 2 == 1)
			res = (res + a) % mod;
		a = (a * 2) % mod;
		b /= 2;
	}
	return res % mod;
}

//gdc entre a y b
static uint64_t gcd(uint64_t a, uint64_t b)
{
	if (a < b)
		return gcd(b, a);
	else if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}

/*=============================================================================
* Funcion: MethodFermat -> Metodo de chequeo de primariedad probabilistico,
* Si dice que es primo hay altas probabilidades de que lo sea salvo que estemos
* ante un numero de Carmichael.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* Valor de retorno:	ret_val -> TRUE (Numero es primo)
*                           -> FALSE (Numero no es primo)
*=============================================================================*/

static bool_t MethodFermat(primepro_t *primeProcess)
{
	uint8_t k = 10;
	uint8_t i;
	uint64_t a;

	uint8_t prime[] =
		{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
		 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
		 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};

	primeProcess->memory = sizeof(primepro_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(prime);
	primeProcess->result = FALSE;
	primeProcess->memoryOV = FALSE;
	primeProcess->divider = 0;

	setTime(0);
	// Chequea si es dos o tres.
	if ((primeProcess->number == 2) || (primeProcess->number == 3))
	{
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
	else
	{
		// Itera chequeando si es multiplo de los primos menores a 256
		// Para minimizar los falsos primos (Carmichael)
		for (i = 0; i <= sizeof(prime) / sizeof(uint8_t); i++)
		{
			if (primeProcess->number % prime[i] == 0)
			{
				getTime(primeProcess);
				primeProcess->divider = prime[i];
				return primeProcess->result;
			}
		}

		// itera k veces subir el k para bajar probabilidad de falso positivo.
		while (k > 0)
		{
			a = 2 + rand() % (primeProcess->number - 4);
			// Se chequea si a y el numero a chequear son coprimos
			// Si es coprimo sale como no primo.
			if (gcd(primeProcess->number, a) != 1)
			{
				getTime(primeProcess);
				return primeProcess->result;
			}
			// Fermat's little theorem
			// Si no cumple con el teorema sale.
			if (power(a, (primeProcess->number) - 1, primeProcess->number) != 1)
			{
				getTime(primeProcess);
				return primeProcess->result;
			}
			k--;
		}
		getTime(primeProcess);
		primeProcess->divider = primeProcess->number;
		return primeProcess->result = TRUE;
	}
}
