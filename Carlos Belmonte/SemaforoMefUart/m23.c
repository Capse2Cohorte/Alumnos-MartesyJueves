#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

typedef enum{ ROJO, ROJOAMARILLO, VERDE, AMARILLO } estadoMEF;
estadoMEF estadoActual;

uint8_t TiempoTranscurrido=0;
uint8_t dato = 0;
int8_t v[4];
int8_t i = 0;
uint16_t tiempo = 0;

void cargarVector(void){
	while(i<4){
		dato = uartReadByte ( UART_USB );
		if(dato == 49 || dato == 50 || dato == 51 || dato == 52){
			tiempo = dato - 48;
			v[i] = tiempo;
			i++;
		}
	}
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

void IniciarMEF(void){
	estadoActual = ROJO;
}

void ActualizarMEF(void){
	switch(estadoActual){
		case ROJO:
			EncenderRojo();
			if(TiempoTranscurrido == v[0]){
				estadoActual = ROJOAMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case ROJOAMARILLO:
			EncenderRojoAmarillo();
			if(TiempoTranscurrido == v[1]){
				estadoActual = VERDE;
				TiempoTranscurrido = 0;
			}
		break;
		
		case VERDE:
			EncenderVerde();
			if(TiempoTranscurrido == v[2]){
				estadoActual = AMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case AMARILLO:
			EncenderAmarillo();
			if(TiempoTranscurrido == v[3]){
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
   
   uartConfig( UART_USB, 115200 ); /* Inicializar la UART2 a 115200 baudios */

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
		
		
		dato = uartReadByte( UART_USB ); /* Recibo de la UART2 */
		//Cargar vector solo con la tecla A
		if (dato == 97){
		   cargarVector();
	       //dato = 0;
		}
		
		
		ActualizarMEF();
		delay(1000);
		TiempoTranscurrido++;
	}
	return 0 ;
}
