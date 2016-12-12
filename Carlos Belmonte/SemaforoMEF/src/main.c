#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

typedef enum{ ROJO, ROJOAMARILLO, VERDE, AMARILLO } estadoMEF;
estadoMEF estadoActual;

uint8_t TiempoTranscurrido=0;

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

void IniciarMEF(void){
	estadoActual = ROJO;
}

void ActualizarMEF(void){
	switch(estadoActual){
		case ROJO:
			EncenderRojo();
			if(TiempoTranscurrido == 2){
				estadoActual = ROJOAMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case ROJOAMARILLO:
			EncenderRojoAmarillo();
			if(TiempoTranscurrido == 1){
				estadoActual = VERDE;
				TiempoTranscurrido = 0;
			}
		break;
		
		case VERDE:
			EncenderVerde();
			if(TiempoTranscurrido == 3){
				estadoActual = AMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case AMARILLO:
			EncenderAmarillo();
			if(TiempoTranscurrido == 3){
				estadoActual = ROJO;
				TiempoTranscurrido = 0;
			}
		break;
		
		default:
			IniciarMEF();
		break;
	}
}

int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();  
   /* Inicializar el conteo de Ticks con resolución de 1ms */
   tickConfig(1,0);
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


   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		ActualizarMEF();
		delay(1000);
		TiempoTranscurrido++;
	}
	return 0 ;
}

