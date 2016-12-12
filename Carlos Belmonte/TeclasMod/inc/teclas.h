#ifndef _TECLAS_H_
#define _TECLAS_H_

typedef struct{
   uint8_t digitalInput;
   bool_t state;
} tecla_t;

bool_t teclaConfig( tecla_t * tecla, uint8_t digitalInput );
bool_t teclaRead( tecla_t * tecla );

#endif
