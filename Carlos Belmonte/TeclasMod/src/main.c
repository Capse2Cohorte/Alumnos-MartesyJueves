#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "teclas.h"
#include "antirebote.h"

extern bool_t valorAntirebote1;
extern bool_t valorAntirebote2;
extern bool_t valorAntirebote3;

static uint8_t angulo = 0;
static uint8_t cantidad = 1; // Para que el servo se mueva 1º sin presionar TEC3

int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolución de 1ms, sin tickHook */
   tickConfig( 1, 0 );

   /* Habilitar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );

   /* Inicializar el semáforo */
   antireboteConfig( TEC1, TEC2, TEC3 );

   bool_t valor = 0; 
   uint8_t servoAngle = 0; /* 0 a 180 grados */   
   valor = servoConfig( 0,      ENABLE_SERVO_TIMERS );
   valor = servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );

   valor = servoWrite( SERVO0, servoAngle );
   servoAngle = servoRead( SERVO0 );
   
   uartConfig( UART_USB, 9600 ); /* Inicializar la UART2 a 9600 baudios */

   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
      antireboteMef();
	  
	  if(valorAntirebote1==1){
		  if(cantidad<180){		  
			angulo= angulo + cantidad;
			servoWrite( SERVO0, angulo );
			valorAntirebote1=0;
		  }		  
	  }
	  
	  if(valorAntirebote2==1){
		  if(cantidad>0){		  
			angulo= angulo - cantidad;
			servoWrite( SERVO0, angulo );
			valorAntirebote2=0;
		  }	
	  }
	  
	  if(valorAntirebote3==1){
		  cantidad =  15;
		  uartWriteString( UART_USB, "El servo se mueve cada 15 grados\n\r" );
	  }	  
	  
	  if(valorAntirebote3==2){
		  cantidad =  30;
		  uartWriteString( UART_USB, "El servo se mueve cada 30 grados\n\r" );
	  }	

	  if(valorAntirebote3==3){
		  cantidad =  45;
		  uartWriteString( UART_USB, "El servo se mueve cada 45 grados\n\r" );
	  }	  
	  
	  

   }

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
