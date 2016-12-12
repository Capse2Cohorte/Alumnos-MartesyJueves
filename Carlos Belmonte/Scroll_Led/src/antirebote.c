#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h" 
#include "antirebote.h" 


typedef enum{UP1, FALLING1, RISING1, DOWN1} estadoMEF1;
estadoMEF1 estadoActual1;

typedef enum{UP2, FALLING2, RISING2, DOWN2} estadoMEF2;
estadoMEF2 estadoActual2;

int8_t valorAntirebote = 0;


void InicializarMEF1(void){
        estadoActual1 = UP1;
        }

void InicializarMEF2(void){
        estadoActual2 = UP2;
        }		
		
void ActualizarMEF1(void){
      switch (estadoActual1) {
            case UP1:{
                  if( (!digitalRead( TEC1 )) ){
                        estadoActual1 = FALLING1;
                  }
            }break;
            
            case FALLING1:{
                  delay(40);				  
                  if(!digitalRead( TEC1 )){
                        estadoActual1 = DOWN1;
                        valorAntirebote = ++valorAntirebote;
						if(valorAntirebote == 5){
							valorAntirebote = 1;
						}
                  }else estadoActual1 = UP1;				  
            }break;
            
            case DOWN1:{
                  if( (digitalRead( TEC1 )) ){
                        estadoActual1 = RISING1;
                  }
            }break;
            
            case RISING1:{
                  delay(40);
                  if( (digitalRead( TEC1 )) ){
                        estadoActual1 = UP1;
                  }else estadoActual1 = DOWN1;
            }break;
            
            default:{
                  InicializarMEF1();
            }break;
      }
}

void ActualizarMEF2(void){
      switch (estadoActual2) {
            case UP2:{
                  if( (!digitalRead( TEC2 )) ){
                        estadoActual2 = FALLING2;
                  }
            }break;
            
            case FALLING2:{
                  delay(40);			  
                  if(!digitalRead( TEC2 )){
                        estadoActual2 = DOWN2;
                        valorAntirebote = --valorAntirebote;
						if(valorAntirebote == 0){
							valorAntirebote = 4;
						}
                  }else estadoActual2 = UP2;
				  
				  
            }break;
            
            case DOWN2:{
                  if( (digitalRead( TEC2 )) ){
                        estadoActual2 = RISING2;
                  }
            }break;
            
            case RISING2:{
                  delay(40);
                  if( (digitalRead( TEC2 )) ){
                        estadoActual2 = UP2;
                  }else estadoActual2 = DOWN2;
            }break;
            
            default:{
                  InicializarMEF2();
            }break;
      }
}