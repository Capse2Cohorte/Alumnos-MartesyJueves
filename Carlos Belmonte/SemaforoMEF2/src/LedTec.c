#include "sAPI.h"         /* <= sAPI header */
#include "LedTec.h"		  /*Led y Tec utilizados*/

void ConfigLedTec(void){
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
}

void EncenderRojo(void){
	digitalWrite( LED1 , ON );
	digitalWrite( LED2 , OFF );
	digitalWrite( LED3 , OFF );
}

void EncenderRojoAmarillo(void){
	digitalWrite( LED1 , ON );
	digitalWrite( LED2 , ON );
	digitalWrite( LED3 , OFF );
}

void EncenderVerde(void){
	digitalWrite( LED1 , OFF );
	digitalWrite( LED2 , OFF );
	digitalWrite( LED3 , ON );
}

void EncenderAmarillo(void){
	digitalWrite( LED1 , OFF );
	digitalWrite( LED2 , ON );
	digitalWrite( LED3 , OFF );
}