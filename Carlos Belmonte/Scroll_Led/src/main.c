#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h"  

extern int8_t  valorAntirebote;

int main(void)
{
   boardConfig();
   tickConfig(1,0);
   digitalConfig( 0, ENABLE_DIGITAL_IO );
   ConfigLedTec();

   digitalWrite( LEDR, 0 );
   digitalWrite( LEDG, 0 );
   digitalWrite( LEDB, 0 );
   
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
	      ActualizarMEF1();
		  ActualizarMEF2();
		  if(valorAntirebote == 1){
			digitalWrite( LEDR, 1 );
			digitalWrite( LEDG, 1 );
			digitalWrite( LEDB, 1 );
			
			digitalWrite( LED1, 0 );
			digitalWrite( LED2, 0 );
			digitalWrite( LED3, 0 );			
		  }
		  
		  if(valorAntirebote == 2){
			digitalWrite( LEDR, 0 );
			digitalWrite( LEDG, 0 );
			digitalWrite( LEDB, 0 );
			
			digitalWrite( LED1, 1 );
			digitalWrite( LED2, 0 );
			digitalWrite( LED3, 0 );			
		  }
		  
		  if(valorAntirebote == 3){
			digitalWrite( LEDR, 0 );
			digitalWrite( LEDG, 0 );
			digitalWrite( LEDB, 0 );  
			
			digitalWrite( LED1, 0 );
			digitalWrite( LED2, 1 );
			digitalWrite( LED3, 0 );
		  }
		  
		  if(valorAntirebote == 4){
			digitalWrite( LEDR, 0 );
			digitalWrite( LEDG, 0 );
			digitalWrite( LEDB, 0 );  
			
			digitalWrite( LED1, 0 );
			digitalWrite( LED2, 0 );
			digitalWrite( LED3, 1 );
		  }
	      
            }
	return 0 ;
}