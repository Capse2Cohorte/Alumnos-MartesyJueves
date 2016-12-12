#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

void UART2_IRQHandler(void){}

int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();
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
   
   digitalWrite( LED1, 0 );
   digitalWrite( LED2, 0 );
   digitalWrite( LED3, 0 );
   digitalWrite( LEDR, 0 );
   digitalWrite( LEDG, 0 );
   digitalWrite( LEDB, 0 );
   
   uartConfig( UART_232, 9600 ); /* Inicializar la UART232 a 9600 baudios */  
   uint8_t dato = 0;
   
   uartWriteString( UART_232, "AT+NAME=EDU-CIAA\r\n" ); //Coloco nombre de identificacion al modulo
   delay(100);
   uartWriteString( UART_232, "AT+PSWD=1234\r\n" );//Coloco contraseña de vinculacion
   delay(100); 
   /*uartWriteString( UART_232, "AT+UART=9600,0,0\r\n" ); Por default el modulo viene configurado a 9600baudios
   delay(100);*/   
   
   
   bool_t A = 0;
   bool_t B = 0;
   bool_t C = 0;
   bool_t D = 0;
   bool_t E = 0;
   bool_t F = 0;
   
   
	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		dato = uartReadByte( UART_232 ); /* Recibo de la UART2 */
				
		if( dato == 65 ){
			A = !A;
			digitalWrite( LEDR, A );}			

		if( dato == 66 ){
			B = !B;
			digitalWrite( LEDB, B );}			
		
		if( dato == 67 ){
			C = !C;
			digitalWrite( LEDG, C );}
			
		if( dato == 68 ){
			D = !D;
			digitalWrite( LED1, D );}			

		if( dato == 69 ){
			E = !E;
			digitalWrite( LED2, E );}			
		
		if( dato == 70 ){
			F = !F;
			digitalWrite( LED3, F );}
								
	}
	
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
