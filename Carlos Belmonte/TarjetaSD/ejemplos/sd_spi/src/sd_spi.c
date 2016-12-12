/* Copyright 2014, ChaN
 * Copyright 2016, Matias Marando
 * All rights reserved.
 *
 * This file is part of Workspace.
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

/** @brief This is an SD card write example using the FatFs library
 */

/** \addtogroup spi SD card write via SPI
 ** @{ */

/*==================[inclusions]=============================================*/

#include "board.h"
#include "ff.h"
#include "sapi.h"

/*==================[macros and definitions]=================================*/

#define FILENAME "capse.txt"

/*==================[internal data declaration]==============================*/

static uint32_t ms_ticks;  /**< 1ms timeticks counter */
static FATFS fs;           /**< FatFs work area needed for each volume */
static FIL fp;             /**< File object needed for each open file */

/*==================[internal functions declaration]=========================*/

/** @brief Hardware initialization function
 *  @return none
 */
static void initHardware(void);

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
    Board_Init();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    /* SPI configuration */
    Board_SSP_Init(LPC_SSP1);
    Chip_SSP_Init(LPC_SSP1);
    Chip_SSP_Enable(LPC_SSP1);
}

/*==================[external functions definition]==========================*/

int main(void)
{
    UINT nbytes;

    initHardware();

    tickConfig(1,0);

    delay_t delayB;

    delayConfig(&delayB,1000);

    uint8_t led = OFF;

    digitalConfig( 0, ENABLE_DIGITAL_IO );

    /* Configuración de pines de entrada para Teclas de la CIAA-NXP */
    digitalConfig( TEC1, INPUT );
    digitalConfig( TEC2, INPUT );
    digitalConfig( TEC3, INPUT );
    digitalConfig( TEC4, INPUT );

    /* Configuración de pines de salida para Leds de la CIAA-NXP */
    digitalConfig( LEDR, OUTPUT );
    digitalConfig( LEDG, OUTPUT );
    digitalConfig( LEDB, OUTPUT );
    digitalConfig( LED1, OUTPUT );
    digitalConfig( LED2, OUTPUT );
    digitalConfig( LED3, OUTPUT );

    /* Give a work area to the default drive */
    if (f_mount(&fs, "", 0) != FR_OK) {
        /* If this fails, it means that the function could
         * not register a file system object.
         * Check whether the SD card is correctly connected */
    }

    /* Create/open a file, then write a string and close it */
    if (f_open(&fp, FILENAME, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK) {
        f_write( &fp,
        		 "CAPSE: Carlos Mariano Belmonte\r\n",
				 30,
				 &nbytes
			   );

        f_close(&fp);

        if (nbytes == 68) {
            /* Toggle a LEDG if the write operation was successful */
            Board_LED_Toggle(1);
        }
    } else{
        /* Toggle a LEDR if fails */
        Board_LED_Toggle(0);
    }

    while (1) {

    	if ( delayRead( &delayB ) ){
    		if( !led )
    			led = ON;
    		else
    			led = OFF;
    		digitalWrite( LEDB, led );
    	}
    }

    return 0;
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
