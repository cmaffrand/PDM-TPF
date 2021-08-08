/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 * Date: 2021/08/08
 *===========================================================================*/

#include "sapi.h"
#include "process.h"

/*=============================================================================
* Funcion: proccesFB -> 
* Parametros de Entrada: 
* Valor de retorno:	ret_val -> TRUE 
* 							-> FALSE 
*=============================================================================*/

bool_t proccesFB(uint64_t number, mtd_t metodo)
{
   bool_t ret_val = 1;

   // Chequeo de los valores de LEDs presentes en la EDU CIAA.
   if (number >= 2)
   {
      for (i = 2; i <= number; ++i) {
        // condition for non-prime
        if (number % i == 0) {
        ret_val = 1;
        printf("Numero %d no es primo\r\n",number);
      break;
    }
    printf("Numero %d es primo\r\n",number);
   }
   else {
       printf("Numero %d no puede ser procesado\r\n",number);
   }
   // Este es un led inexistente en la placa, para generar un estado donde
   // todos los leds están apagados.
   else if (led == LED_OFF)
      ret_val = 1;
   else
   {
      // No se puede encender ningun led.
      ret_val = 0;
      printf("\n Error: Se intentó encender un led no permitido");
   }

   return ret_val;
}

