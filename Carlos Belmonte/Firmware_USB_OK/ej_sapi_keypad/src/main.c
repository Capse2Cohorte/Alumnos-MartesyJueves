/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
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

/*
 * Date: 2016-07-28
 */

/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

#include "display7segment.h"   /* <= 7-segment display header */
#include "keypad.h"            /* <= keypad header */

/*==================[macros and definitions]=================================*/

/* UART */
#define BAUD_RATE   115200

// GPIOs para el display 7 segmentos 1
#define GPIO1       DIO15
#define GPIO2       DIO31
#define GPIO3       DIO14
#define GPIO4       DIO30
#define GPIO5       DIO13
#define GPIO6       DIO29
#define GPIO7       DIO12
#define GPIO8       DIO11

// GPIOs para el teclado matricial 1
// Filas
#define RS232_TXD    DIO9  // R0
#define CAN_RD       DIO8  // R1
#define CAN_TD       DIO7  // R2
#define T_COL1       DIO6  // R3
// Columnas
#define T_FIL0       DIO5  // C0
#define T_FIL3       DIO4  // C1
#define T_FIL2       DIO3  // C2
#define T_COL0       DIO2  // C3

// GPIOs para el teclado matricial 2
// Filas
#define ENET_CRS_DV  DIO25 // R0 // No anda, revisar hardware

#define ENET_MDIO    DIO24 // R0
#define ENET_TXD0    DIO23 // R1
#define ENET_TXD1    DIO22 // R2
#define SPI_MISO     DIO21 // R3
// Columnas
#define LCDRS        DIO19 // C0
#define LCD3         DIO18 // C1
#define LCD2         DIO17 // C2
#define LCD1         DIO16 // C3



/*
   digitalConfig( RS232_TXD, OUTPUT );
   digitalConfig( CAN_RD, OUTPUT );
   digitalConfig( CAN_TD, OUTPUT );
   digitalConfig( T_COL1, OUTPUT );

   digitalConfig( T_FIL0, INPUT_PULLUP );
   digitalConfig( T_FIL3, INPUT_PULLUP );
   digitalConfig( T_FIL2, INPUT_PULLUP );
   digitalConfig( T_COL0, INPUT_PULLUP );

   uint16_t r = 0;
   uint16_t c = 0;
   uint16_t keypadKeys[16] = {
                                  1,    2,    3, 0x0a,
                                  4,    5,    6, 0x0b,
                                  7,    8,    9, 0x0c,
                               0x0e,    0, 0x0f, 0x0d
                             };

  for( r=0; r<4; r++ ){
     for( c=0; c<4; c++ ){
        display7SegmentWrite( display7Segment1Pins,
                              (uint8_t)keypadKeys[ r * 4 + c ] );
        delay(500);
     }
  }

*/

/*==================[internal data declaration]==============================*/

/* Buffers */
//static uint8_t uartBuff[10];

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolucion de 1ms, sin tickHook */
   tickConfig( 1, 0 );

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );

   /* Configuracion de pines de entrada para Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   /* Configuracion de pines de salida para Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );


   /* Configuracion de pines para el display 7 segmentos */
   /*
   --------------------------+------------+-----------+----------------
    Segmento encendido       | Valor BIN  | Valor HEX | GPIO resultado
   --------------------------+------------+-----------+----------------
    Enciende el segmento 'a' | 0b00000001 |   0x20    | GPIO5
    Enciende el segmento 'b' | 0b00000010 |   0x80    | GPIO7
    Enciende el segmento 'c' | 0b00000100 |   0x40    | GPIO6
    Enciende el segmento 'd' | 0b00001000 |   0x02    | GPIO1
    Enciende el segmento 'e' | 0b00010000 |   0x04    | GPIO2
    Enciende el segmento 'f' | 0b00100000 |   0x10    | GPIO4
    Enciende el segmento 'g' | 0b01000000 |   0x08    | GPIO3
    Enciende el segmento 'h' | 0b10000000 |   0x80    | GPIO8
   --------------------------+------------+-----------+----------------
                a
              -----
          f /     / b
           /  g  /
           -----
       e /     / c
        /  d  /
        -----    O h = dp (decimal pint).

   */
   uint8_t display7Segment1Pins[8] = {
      GPIO5, // a
      GPIO7, // b
      GPIO6, // c
      GPIO1, // d
      GPIO2, // e
      GPIO4, // f
      GPIO3, // g
      GPIO8  // h = dp
   };

   display7SegmentPinConfig( display7Segment1Pins );


   /* Configuracion de pines para el Teclado Matricial*/

   // Teclado 1
   keypad_t keypad1;

   // Filas --> Salidas
   uint8_t keypadRowPins1[4] = {
      RS232_TXD, // Row 0
      CAN_RD,    // R1
      CAN_TD,    // R2
      T_COL1     // R3
   };

   // Columnas --> Entradas con pull-up (MODO = INPUT_PULLUP)
   uint8_t keypadColPins1[4] = {
      T_FIL0,    // Column 0
      T_FIL3,    // C1
      T_FIL2,    // C2
      T_COL0     // C3
   };

   keypadConfig( &keypad1, keypadRowPins1, 4, keypadColPins1, 4 );


   // Vector de conversion entre indice de tecla presionada y
   // display 7 segmentos
   uint16_t keypadToDesplayKeys[16] = {
                                           1,    2,    3, 0x0a,
                                           4,    5,    6, 0x0b,
                                           7,    8,    9, 0x0c,
                                        0x0e,    0, 0x0f, 0x0d
                                      };

   // Variable para guardar la tecla leida
   uint16_t tecla = 0;


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      if( keypadRead( &keypad1, &tecla ) ){
         display7SegmentWrite( display7Segment1Pins,
                               keypadToDesplayKeys[ (uint8_t)tecla ] );
      } else{
         display7SegmentWrite( display7Segment1Pins, DISPLAY_OFF );
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
