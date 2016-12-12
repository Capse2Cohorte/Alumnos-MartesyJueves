#include "sAPI.h"         /* <= sAPI header */
#include "teclas.h"         /* <= own header */

bool_t teclaConfig( tecla_t * tecla, uint8_t digitalInput ){
   tecla->digitalInput = digitalInput;
   digitalConfig( tecla->digitalInput, INPUT );
}

bool_t teclaRead( tecla_t * tecla ){
   digitalRead( tecla->digitalInput );
   return tecla->state;
}






