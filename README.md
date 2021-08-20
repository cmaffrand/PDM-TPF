# PdM-TP Final - Detector de números primos en EDU-CIAA

Autor:

Carlos Maffrand (carlosmaffrand5@gmail.com)

Consola serie que permite seleccionar entre varios algoritmos para determinar primariedad y devuelve el resultado con el tiempo de procesamiento.

Información sobre la placa:

http://www.proyecto-ciaa.com.ar/devwiki/doku.php?id=desarrollo:edu-ciaa:edu-ciaa-nxp

El software fue realizado como trabajo final de la materia programación de micro controladores de la especialización en sistemas embebidos de la UBA.

http://laboratorios.fi.uba.ar/lse/especializacion.html

La información de algoritmos fue recavada de diferentes fuentes:

https://www.wolframalpha.com

https://en.wikipedia.org/

https://www.bigprimes.net

https://www.geeksforgeeks.org

https://stackoverflow.com

Los algortimos implementados son:

- Divisibilidad por Fueza Bruta iterando hasta n/2.
- Divisibilidad por Fuerza Bruta solo chequeando para n impares e iterando hasta n/2.
- Divisibilidad por Fuerza Bruta solo chequeando para n impares e iterando hasta SQRT(n).
- Divisibilidad por metodo 6K+1 solo chequeando para n impares e iterando hasta SQRT(n). Este método evita chequear numeros multimos de 2 y 3.
- Divisibilidad por metodo 30K+1 solo chequeando para n impares e iterando hasta SQRT(n). Este método evita chequear numeros multimos de 2, 3 y 5.
- Divisibilidad por metodo 210K+1 solo chequeando para n impares e iterando hasta SQRT(n). Este método evita chequear numeros multimos de 2, 3, 5 y 7.
- Divisibilidad por primos usando el Sieve de Eratosthenes para la construcción de primos e iterando hasta SQRT(n). Limitado por el uso de memoria, se puede segmentar el algirtmo.
- Divisibilidad por primos usando el Sieve de Euler para la construcción de primos e iterando hasta SQRT(n). Limitado por el uso de memoria, se puede segmentar el algirtmo.
- Divisibilidad por primos usando el Sieve de Sundaram para la construcción de primos e iterando hasta SQRT(n). Limitado por el uso de memoria, se puede segmentar el algirtmo.
- Divisibilidad por primos usando el Sieve de Atkin para la construcción de primos e iterando hasta SQRT(n).
- Probabilsitico basado en el Fermat’s Little Theorem, para evitar falsos positivos y subir la fiabilidad se usa divisibilidad por primos entre 2 y 251 como complemento.
- Probabilsitico basado en el algortimo de Miller-Rabin, para evitar falsos positivos y subir la fiabilidad se usa divisibilidad por primos entre 2 y 251 como complemento.
- Probabilsitico basado en el algortimo de Solovay-Strassen, para evitar falsos positivos y subir la fiabilidad se usa divisibilidad por primos entre 2 y 251 como complemento.
- Probabilsitico basado en el algortimo de Lehmann, para evitar falsos positivos y subir la fiabilidad se usa divisibilidad por primos entre 2 y 251 como complemento.
- Deterministico basado en el argoritmo de Wilson, el mismo sae centra en el calculo del factorial, es muy lento.

Se exploraron otros metodos determinisiticos:
- Lucas: muy costoso computacionalmente proque hay que calcular todos los factores primos de n-1. Lo que lleva mucho tiempo.
- AKS: muy costoso computacionalmente proque hay que calcular un vector de coeficientes de largo n. Lo que hace que have que en la EDU-CIAA no se pued calcular más que aproximadamente hasta 20k.
- Vantieghems: muy costoso computacionalmente proque hay que calcular (2^n)-1, lo que hace que el metodo sirva solo hasta n = 64.

Probables mejoras que se le pueden realizar al código:
- Generar una forma de escape del procesamiento (cancelarlo), ahora hay que esperar que termine.
- Calcluar el tiempo de procesamiento de manera diferente, dado que en el implementado se usa el sysTick y se puede contar hasta 2^32-1, lo cual da un tiempo máximo de 21 segundos.
- Se podría implementar un modo de uso que ejecute todos los metodos para un mismo número y de ese modo comparar los resultados.
- Se pueden explorar otros métodos.
