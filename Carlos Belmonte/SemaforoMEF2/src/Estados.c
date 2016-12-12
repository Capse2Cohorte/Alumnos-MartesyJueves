#include "LedTec.h"		  /*Led y Tec utilizados*/
#include "Estados.h"	  /*Diferentes estados del semaforo*/
#include "sAPI.h"         /* <= sAPI header */

typedef enum{ ROJO, ROJOAMARILLO, VERDE, AMARILLO } estadoMEF;
estadoMEF estadoActual;

extern uint8_t TiempoTranscurrido;

void IniciarMEF(void){
	estadoActual = ROJO;
}

void ActualizarMEF(void){
	switch(estadoActual){
		case ROJO:
			EncenderRojo();
			if(TiempoTranscurrido == 4){
				estadoActual = ROJOAMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case ROJOAMARILLO:
			EncenderRojoAmarillo();
			if(TiempoTranscurrido == 2){
				estadoActual = VERDE;
				TiempoTranscurrido = 0;
			}
		break;
		
		case VERDE:
			EncenderVerde();
			if(TiempoTranscurrido == 5){
				estadoActual = AMARILLO;
				TiempoTranscurrido = 0;
			}
		break;
		
		case AMARILLO:
			EncenderAmarillo();
			if(TiempoTranscurrido == 2){
				estadoActual = ROJO;
				TiempoTranscurrido = 0;
			}
		break;
		
		default:
			IniciarMEF();
		break;
	}
}