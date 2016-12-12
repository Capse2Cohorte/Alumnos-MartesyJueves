#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "teclas.h"


typedef enum{UP, FALLING, RISING, DOWN} estadoMEF;
estadoMEF estadoActual;
bool_t valorAntirebote1 = 0;
bool_t valorAntirebote2 = 0;
bool_t valorAntirebote3 = 0;

/* Variables globales privadas del módulo */
static tecla_t debounce1;
static tecla_t debounce2;
static tecla_t debounce3;

/* Variable de Retardo no bloqueante */
static delay_t delayBase;
//static uint8_t i = 0;

void antireboteConfig( uint8_t tecla1, uint8_t tecla2, uint8_t tecla3 ){
   delayConfig( &delayBase, 40 );
   teclaConfig( &debounce1, tecla1 );
   teclaConfig( &debounce2, tecla2 );
   teclaConfig( &debounce3, tecla3 );
}


void InicializarMEF(void){
        estadoActual = UP;
        }

void antireboteMef(void){
      switch (estadoActual) {
            case UP:{
                  if( !digitalRead(TEC1) ||  !digitalRead(TEC2) || !digitalRead(TEC3) ){
                        estadoActual = FALLING;
                  }
            }
            break;
            
            case FALLING:{		  
				  if(delayRead(&delayBase)){ 
				  
					if( !digitalRead(TEC1) ){
							estadoActual = DOWN;
							valorAntirebote1 = !valorAntirebote1;
					}else estadoActual = UP;
				  
					if( !digitalRead(TEC2) ){
							estadoActual = DOWN;
							valorAntirebote2 = !valorAntirebote2;
					}else estadoActual = UP;				  
				  
					if( !digitalRead(TEC3) ){
							estadoActual = DOWN;
							valorAntirebote3 = ++valorAntirebote3;					
							if(valorAntirebote3 == 4){
								valorAntirebote3 = 1;
							}
					}else estadoActual = UP;			  
				  }					
            }
            break;
            
            case DOWN:{
                  if( digitalRead(TEC1) ||  digitalRead(TEC2) || digitalRead(TEC3) ){
                        estadoActual = RISING;
                  }
            }
            break;
            
            case RISING:{
				  if(delayRead(&delayBase)){ 			  
					if( digitalRead(TEC1) ||  digitalRead(TEC2) || digitalRead(TEC3) ){
							estadoActual = UP;
					}else estadoActual = DOWN;				  
				  }
			}
            break;
            
            default:{
                  InicializarMEF();
            }
            break;
      }
}






/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
