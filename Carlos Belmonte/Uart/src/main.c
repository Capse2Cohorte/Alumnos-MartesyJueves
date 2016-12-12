#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h"  
#include "antirebote.h"
#include "Estados.h"

extern bool_t valorAntirebote;

uint8_t i=0;
uint8_t dato=0;
uint8_t buffer =0;

uint8_t TiempoTranscurrido=1; //
uint16_t red =1;              // Se inicia la variable con un estado distinto de cero, para poder 
uint16_t redyellow=1;         // hacer la carga despues del inicio, en cualquier momento. Si se deja
uint16_t green=1;             // las variables en cero, el programa no sabe donde ingresar en los estados
uint16_t yellow=1;            //


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


int main(void)
{
   boardConfig();
   tickConfig(1,0);
   digitalConfig( 0, ENABLE_DIGITAL_IO );
   ConfigLedTec();

   uartConfig( UART_USB, 9600 ); /* Inicializar la UART2 a 115200 baudios */ 
   
   /* Variables de Retardos no bloqueantes */
   delay_t delay1;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos 
      (500ms = 0,5s) */
   delayConfig( &delay1, 1000);
   
   
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		  AntireboteMEF();
		  UpdateMEF();
	      
		  if( delayRead( &delay1 )  ){//
			  TiempoTranscurrido++;   // Se utiliza retardo no bloqueante, para poder atender al pulsador en cualquier instante que se es presionado.
		  }		  		              //
		  /*
		  EncenderRojo();
		  delay(red);
		  EncenderRojoAmarillo();
		  delay(redyellow);
		  EncenderVerde();
		  delay(green);
		  EncenderAmarillo();
		  delay(yellow);*/	  
	      
            }
	return 0 ;
}