#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h" 
#include "antirebote.h" 


typedef enum{UP, FALLING, RISING, DOWN} estadoMEF;
estadoMEF estadoActual;

bool_t valorAntirebote = 0;


void InicializarMEF(void){
        estadoActual = UP;
        }

void ActualizarMEF(void){
      switch (estadoActual) {
            case UP:{
                  if(!digitalRead( TEC2 )){
                        estadoActual = FALLING;
                  }
            }
            break;
            
            case FALLING:{
                  delay(40);
                  if(!digitalRead( TEC2 )){
                        estadoActual = DOWN;
                        valorAntirebote = !valorAntirebote;
                  }else estadoActual = UP;
            }
            break;
            
            case DOWN:{
                  if(digitalRead( TEC2 )){
                        estadoActual = RISING;
                  }
            }
            break;
            
            case RISING:{
                  delay(40);
                  if(digitalRead( TEC2 )){
                        estadoActual = UP;
                  }else estadoActual = DOWN;
            }
            break;
            
            default:{
                  InicializarMEF();
            }
            break;
      }
}