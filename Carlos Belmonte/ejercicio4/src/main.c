#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h"  

extern bool_t valorAntirebote;

int main(void)
{
   boardConfig();
   tickConfig(1,0);
   digitalConfig( 0, ENABLE_DIGITAL_IO );
   ConfigLedTec();
  
/*---------------Configuracion del servo y ADC-------------------*/  
   bool_t valor = 0;   
   uint8_t servoAngle = 0; /* 0 a 180 grados */
   uint16_t adc = 0; //lectura del CH1
   uint8_t angulo = 0; //ANGULO PARA SERVO

   valor = servoConfig( 0,      ENABLE_SERVO_TIMERS );
   valor = servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );

   valor = servoWrite( SERVO0, servoAngle );
   servoAngle = servoRead( SERVO0 );
   
   analogConfig( ENABLE_ANALOG_INPUTS );  /* ADC */

   /* Variables de delays no bloqueantes */
   delay_t delay1;
   delay_t delay2;

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig( &delay1, 1000 );
   delayConfig( &delay2, 500 );
   
   uartConfig( UART_USB, 9600 ); /* Inicializar la UART2 a 9600 baudios */
   uint8_t dato = 0;

   bool_t ledState1 = 0;
   bool_t ledState2 = 0;
   digitalWrite( LED1, ledState1 );
   digitalWrite( LED2, ledState2 );
   
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
	      ActualizarMEF();
		  
		  if(valorAntirebote==0){			  
			if(delayRead(&delay1)){ 
				digitalWrite( LED1, ledState1  );
				digitalWrite( LED2, 0  );
				ledState1 = !ledState1;}			
			  
			adc = analogRead( AI0 );
			angulo = (adc * 180)/1024;
			servoWrite( SERVO0, angulo );
		  }
		  
		  if(valorAntirebote==1){
			if(delayRead(&delay2)){ 
				digitalWrite( LED2, ledState2  );
				digitalWrite( LED1, 0  );
				ledState2 = !ledState2;}
			
			dato = uartReadByte( UART_USB ); /* Recibo de la UART2 */
			if(dato==48){ //dato=0
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );	
				servoWrite( SERVO0, 0 );
			}
			
			if(dato==49){ //dato=1
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );
				servoWrite( SERVO0, 20 );
			}	

			if(dato==50){ //dato=2
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );
				servoWrite( SERVO0, 40 );
			}		

			if(dato==51){ //dato=3
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );
				servoWrite( SERVO0, 60 );
			}				

			if(dato==52){ //dato=4
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );
				servoWrite( SERVO0, 80 );
			}

			if(dato==53){ //dato=5
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );	
				servoWrite( SERVO0, 100 );
			}
			
			if(dato==54){ //dato=6
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );	
				servoWrite( SERVO0, 120 );
			}	

			if(dato==55){ //dato=7
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );	
				servoWrite( SERVO0, 140 );
			}		

			if(dato==56){ //dato=8
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );		
				servoWrite( SERVO0, 160 );				
			}				

			if(dato==57){ //dato=9
				/*ubicar servo*/
				uartWriteString( UART_USB, "Ingreso el valor:" );
				uartWriteByte( UART_USB, dato );
				uartWriteString( UART_USB, ". Presione TEC1 para salir\r\n" );	
				servoWrite( SERVO0, 180 );				
			}					  
		  }
    }
	return 0 ;
}