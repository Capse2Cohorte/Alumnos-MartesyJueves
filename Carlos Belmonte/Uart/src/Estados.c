#include "Estados.h"	  /*Diferentes estados del semaforo*/
#include "sAPI.h"         /* <= sAPI header */
#include "antirebote.h"
#include "main.h" 

typedef enum{ ROJO, ROJOAMARILLO, VERDE, AMARILLO } stateMEF;
stateMEF statePresent;

extern uint8_t TiempoTranscurrido;
extern uint8_t red;
extern uint8_t redyellow;
extern uint8_t green;
extern uint8_t yellow;

void StartMEF(void){
	statePresent = ROJO;
}

void UpdateMEF(void){
	switch(statePresent){
		case ROJO:
			EncenderRojo();
			if(TiempoTranscurrido == red){ // Se compara el tiempo transcurrido con el valor almacenado de la lectura del uart
				statePresent = ROJOAMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case ROJOAMARILLO:
			EncenderRojoAmarillo();
			if(TiempoTranscurrido == redyellow){
				statePresent = VERDE;
				TiempoTranscurrido = 0;
			}
		break;
		
		case VERDE:
			EncenderVerde();
			if(TiempoTranscurrido == green){
				statePresent = AMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case AMARILLO:
			EncenderAmarillo();
			if(TiempoTranscurrido == yellow){
				statePresent = ROJO;
				TiempoTranscurrido = 0;
			}
		break;
		
		default:
			StartMEF();
		break;
	}
}