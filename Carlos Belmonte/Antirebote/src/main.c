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

   digitalWrite( LED1, 0 );
   
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
	      ActualizarMEF();
	      digitalWrite( LED1, valorAntirebote );
            }
	return 0 ;
}