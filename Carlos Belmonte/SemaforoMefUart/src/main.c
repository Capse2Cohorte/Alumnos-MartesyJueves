#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

typedef enum{ ROJO, ROJOAMARILLO, VERDE, AMARILLO } estadoMEF;
estadoMEF estadoActual;

uint8_t TiempoTranscurrido = 48;
uint8_t dato = 0;
uint8_t v[4];
uint8_t i = 0;


void cargarVector(void){
	i = 0;
	while(i<4){
		switch(i){
		  case 0:
			uartWriteString( UART_USB, "Ingresar tiempo Rojo:\r\n" );
		    validacion();		  
		  case 1:
		    uartWriteString( UART_USB, "Ingresar tiempo RojoAmarillo:\r\n" );
		    validacion();
		  case 2:
		    uartWriteString( UART_USB, "Ingresar tiempo Verde:\r\n" );
		    validacion();
		  case 3:
		    uartWriteString( UART_USB, "Ingresar tiempo Amarillo:\r\n" );
		    validacion();
		 
		}
    }
	dato = 0;
}

void validacion(){
    delay(1000);
	dato = uartReadByte ( UART_USB );
	if(dato == 49 || dato == 50 || dato == 51 || dato == 52){	  
	  v[i] =  dato;
	  i++;
	  //dato = 0;
	  uartWriteString( UART_USB, "Valor agregado...\r\n" );
	  delay(2000);
	  
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
				TiempoTranscurrido = 47;
			}
		break;
		
		case ROJOAMARILLO:
			EncenderRojoAmarillo();
			if(TiempoTranscurrido == v[1]){
				estadoActual = VERDE;
				TiempoTranscurrido = 47;
			}
		break;
		
		case VERDE:
			EncenderVerde();
			if(TiempoTranscurrido == v[2]){
				estadoActual = AMARILLO;
				TiempoTranscurrido = 47;
			}
		break;
		
		case AMARILLO:
			EncenderAmarillo();
			if(TiempoTranscurrido == v[3]){
				estadoActual = ROJO;
				TiempoTranscurrido = 47;
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
		uartWriteString( UART_USB, "Ingrese la tecla A para configurar el tiempo\r\n" );
		delay(1000);
		
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
