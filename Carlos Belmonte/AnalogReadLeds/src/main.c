#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */


uint16_t lectura = 0;
   
/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolución de 1ms, sin tickHook */
   tickConfig( 1, 0 );

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );
   
   /* Configuración de pines de entrada para Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );
   /* Configuración de pines de salida para Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );
   
   digitalWrite( LEDR, 0 );
   digitalWrite( LEDG, 0 );
   digitalWrite( LEDB, 0 );
   digitalWrite( LED1, 0 );
   digitalWrite( LED2, 0 );
   digitalWrite( LED3, 0 );	

   analogConfig( ENABLE_ANALOG_INPUTS );  /* ADC */
   analogConfig( ENABLE_ANALOG_OUTPUTS ); /* DAC */


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
	   lectura = analogRead( AI0 );
	   
	   if ( (lectura >= 0) && (lectura < 256) ){
		   digitalWrite( LEDR, 1 );
		   digitalWrite( LEDG, 1 );
		   digitalWrite( LEDB, 1 );
		   digitalWrite( LED1, 0 );
		   digitalWrite( LED2, 0 );
		   digitalWrite( LED3, 0 );
	   }
	   
	   if ( (lectura >= 256) && (lectura < 512) ){
		   digitalWrite( LEDR, 0 );
		   digitalWrite( LEDG, 0 );
		   digitalWrite( LEDB, 0 );
		   digitalWrite( LED1, 1 );
		   digitalWrite( LED2, 0 );
		   digitalWrite( LED3, 0 );	   
	   }
	   
	   if ( (lectura >= 512) && (lectura < 768) ){
		   digitalWrite( LEDR, 0 );
		   digitalWrite( LEDG, 0 );
		   digitalWrite( LEDB, 0 );
		   digitalWrite( LED1, 0 );
		   digitalWrite( LED2, 1 );
		   digitalWrite( LED3, 0 );		   
	   } 
	   
	   if ( (lectura >= 768) && (lectura < 1023) ){
		   digitalWrite( LEDR, 0 );
		   digitalWrite( LEDG, 0 );
		   digitalWrite( LEDB, 0 );
		   digitalWrite( LED1, 0 );
		   digitalWrite( LED2, 0 );
		   digitalWrite( LED3, 1 );		   
	   }
	   analogWrite( AO, lectura );
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
