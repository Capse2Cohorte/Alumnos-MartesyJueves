#include "Estados.h"      /*Diferentes estados del semaforo*/
#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

uint8_t TiempoTranscurrido=0;

int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */
   boardConfig();//Inicializar la placa
   tickConfig(1,0);//Inicializar el conteo de Ticks con resolución de 1ms
   digitalConfig( 0, ENABLE_DIGITAL_IO );//Inicializar DigitalIO   
   ConfigLedTec();//Configuración de pines para Teclas y Leds de la CIAA-NXP

   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		ActualizarMEF();
		delay(1000);
		TiempoTranscurrido++;
	}
	return 0 ;
}

