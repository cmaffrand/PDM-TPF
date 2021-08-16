/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/09
 *===========================================================================*/

#include "sapi.h"
#include "led.h"

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: encenderLed -> Utilizada para encender leds en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t led, tipo de datos de sapi.h
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente.
* 							-> FALSE si no se pudo encender el led.
*=============================================================================*/

bool_t encenderLed(gpioMap_t led)
{
   bool_t ret_val = 1;

   // Chequeo de los valores de LEDs presentes en la EDU CIAA.
   if ((led == LEDR) || (led == LEDG) || (led == LEDB) || (led == LED1) || (led == LED2) || (led == LED3))
   {
      gpioWrite(led, 1);
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

/*=============================================================================
* Funcion: apagarLeds -> Utilizada para apagar todos los leds de la placa EDU CIAA.
* Parametros de Entrada:  void
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente
*=============================================================================*/

bool_t apagarLeds(void)
{
   bool_t ret_val = 1;

   gpioWrite(LED1, 0);
   gpioWrite(LED2, 0);
   gpioWrite(LED3, 0);
   gpioWrite(LEDR, 0);
   gpioWrite(LEDG, 0);
   gpioWrite(LEDB, 0);

   return ret_val;
}

/*=============================================================================
* Funcion: RGBtoggle -> Utilizada para cambiar el led RGB en la placa EDU CIAA.
*=============================================================================*/

bool_t RGBtoggle(void)
{
   bool_t ret_val = 1;
   static uint8_t RGBState = 0;
   uint8_t select = 0;

   select = RGBState % 8;
   gpioWrite(LEDR, select % 2);
   gpioWrite(LEDG, (select / 2) % 2);
   gpioWrite(LEDB, select / 4);
   RGBState++;
   return ret_val;
}

/*=============================================================================
* Funcion: ledManage -> Maneja los leds de la placa el detector de primos.
* Parametros de Entrada: 
* primepro_t *primeProcess -> Puntero a estructura de procesamiento "process.h".
* menu_t *menu -> Puntero a estructura de menu "menu.h".
*=============================================================================*/

void ledManage(primepro_t *primeProcess, menu_t *menu)
{
   static primepro_t lastPrimePro;
   static menu_t lastMenu;

   if ((primeProcess->number != lastPrimePro.number) ||
       (primeProcess->time != lastPrimePro.time) ||
       (primeProcess->method != lastPrimePro.method) ||
       (primeProcess->memory != lastPrimePro.memory) ||
       (primeProcess->memoryOV != lastPrimePro.memoryOV) ||
       (primeProcess->result != lastPrimePro.result) ||
       (primeProcess->divider != lastPrimePro.divider) ||
       (menu->state != lastMenu.state))
   {

      lastPrimePro.number = primeProcess->number;
      lastPrimePro.time = primeProcess->time;
      lastPrimePro.method = primeProcess->method;
      lastPrimePro.memory = primeProcess->memory;
      lastPrimePro.memoryOV = primeProcess->memoryOV;
      lastPrimePro.result = primeProcess->result;
      lastPrimePro.divider = primeProcess->divider;
      lastMenu.state = menu->state;

      apagarLeds();
      RGBtoggle();
      if ((lastMenu.state == RESULT_STATE) && (lastPrimePro.result))
         encenderLed(LED3);
      else if ((lastMenu.state == RESULT_STATE) && (!lastPrimePro.result))
         encenderLed(LED2);
      else if (lastMenu.state == PROCESS_STATE)
         encenderLed(LED1);
   }
}
