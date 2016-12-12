#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

//bool_t estado = 0;
uint8_t flag = 1;

 /* 0x2a 0x000000A8 - Handler for ISR UART2 (IRQ 26) */
void UART2_IRQHandler(void){
	flag = uartReadByte( UART_USB )-48;
}
 
 
 
 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolución de 1ms */
   tickConfig(1,0);

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );

   /* Configuración de pines de entrada para
	   Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   /* Configuración de pines de salida para
	   Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );
   
   uartConfig( UART_USB, 9600 ); /* Inicializar la UART2 a 115200 baudios */
   /* Enable UART Rx Interrupt */
   //Chip_UART_IntEnable(UART_USB, (UART_IER_RBRINT | UART_IER_RLSINT) ); /* Receiver Buffer Register Interrupt */
   /* Enable UART line status interrupt */
   //Chip_UART_IntEnable(UART_USB, UART_IER_RLSINT ); /* LPC43xx User manual page 1118 */
   //NVIC_SetPriority(USART2_IRQn, 6);
   /* Enable Interrupt for UART channel */
   //NVIC_EnableIRQ(USART2_IRQn);

	
	/*
	Tiempo de verde 2s
	Tiempo de amarillo 0,5s
	Tiempo de rojo 3s
	*/
	
	digitalWrite( LEDG, OFF );
	digitalWrite( LED1, OFF );
	digitalWrite( LED2, OFF );
	
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		/*flag = uartReadByte ( UART_USB );
		
		if(flag==49){
			estado=!estado;
		}*/
		while(flag);
		flag=1;
		/* Prendo solo el led verde del semáforo, apago los demás */
		digitalWrite( LEDG, ON );
	   digitalWrite( LED1, OFF );
		digitalWrite( LED2, OFF );

		delay(2000);

		/* Prendo solo el led amrillo del semáforo, apago los demás */
		digitalWrite( LEDG, OFF );
		digitalWrite( LED1, ON );
		digitalWrite( LED2, OFF );

		delay(500);

		/* Prendo solo el led rojo del semáforo, apago los demás */
		digitalWrite( LEDG, OFF );
		digitalWrite( LED1, OFF );
		digitalWrite( LED2, ON );

		delay(3000);

		/* Prendo solo el led amrillo del semáforo, apago los demás */
		digitalWrite( LEDG, OFF );
		digitalWrite( LED1, ON );
		digitalWrite( LED2, OFF );

		delay(500);			
		
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
