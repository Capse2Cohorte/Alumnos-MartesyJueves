/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Main example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Main example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 2016-04-26   v0.0.1   First version
 */

/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
 
 uint8_t x=0;
 uint8_t i=0;
 
 void enviarSegmentos(uint8_t x){
	 uint8_t segmento[9];
	 segmento[0]= 0b01111110;// | 0x7E | 0
	 segmento[1]= 0b00010010;// | 0x12 | 1
	 segmento[2]= 0b10111100;// | 0xBC | 2
	 segmento[3]= 0b10110110;// | 0xB6 | 3
	 segmento[4]= 0b11010010;// | 0xD2 | 4
	 segmento[5]= 0b11100110;// | 0xE6 | 5
	 segmento[6]= 0b11101110;// | 0xEE | 6
	 segmento[7]= 0b00110010;// | 0x32 | 7
	 segmento[8]= 0b11111110;// | 0xFE | 8
	 segmento[9]= 0b11110110;// | 0xF6 | 9
	 
     digitalWrite( DIO32, (segmento[x] & 0b00000001)); //GPIO0   
	 digitalWrite( DIO15, (segmento[x] & 0b00000010)); //GPIO1
	 digitalWrite( DIO31, (segmento[x] & 0b00000100)); //GPIO2
	 digitalWrite( DIO14, (segmento[x] & 0b00001000)); //GPIO3
	 digitalWrite( DIO30, (segmento[x] & 0b00010000)); //GPIO4
	 digitalWrite( DIO13, (segmento[x] & 0b00100000)); //GPIO5
	 digitalWrite( DIO29, (segmento[x] & 0b01000000)); //GPIO6
	 digitalWrite( DIO12, (segmento[x] & 0b10000000)); //GPIO7
 }
 
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
   digitalConfig( DIO32, OUTPUT ); //GPIO0 - segmento 'h'	   
   digitalConfig( DIO15, OUTPUT ); //GPIO1 - segmento 'c'
   digitalConfig( DIO31, OUTPUT ); //GPIO2 - segmento 'd'
   digitalConfig( DIO14, OUTPUT ); //GPIO3 - segmento 'e'
   digitalConfig( DIO30, OUTPUT ); //GPIO4 - segmento 'b'
   digitalConfig( DIO13, OUTPUT ); //GPIO5 - segmento 'a'
   digitalConfig( DIO29, OUTPUT ); //GPIO6 - segmento 'f'
   digitalConfig( DIO12, OUTPUT ); //GPIO7 - segmento 'g'

   digitalWrite( DIO32, 0 ); //GPIO0   
   digitalWrite( DIO15, 0 ); //GPIO1
   digitalWrite( DIO31, 0 ); //GPIO2
   digitalWrite( DIO14, 0 ); //GPIO3
   digitalWrite( DIO30, 0 ); //GPIO4
   digitalWrite( DIO13, 0 ); //GPIO5
   digitalWrite( DIO29, 0 ); //GPIO6
   digitalWrite( DIO12, 0 ); //GPIO7

   

   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		for(i=0;i<10;i++){
			enviarSegmentos(i);
			delay(1000);
		}
		/* Prendo el led azul */
		//digitalWrite( DIO32, 1 );

		//delay(500);

		/* Apago el led azul */
		//digitalWrite( LEDB, OFF );

		//delay(500);

	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
