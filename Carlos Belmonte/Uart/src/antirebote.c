#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "ledsTeclas.h" 
#include "antirebote.h" 


typedef enum{UP, FALLING, RISING, DOWN} estadoMEF;
estadoMEF estadoActual;

bool_t valorAntirebote = 0;
extern uint8_t i;

extern uint8_t buffer;
extern uint8_t dato;

extern uint16_t red ;
extern uint16_t redyellow;
extern uint16_t green;
extern uint16_t yellow;



void InicializarMEF(void){
        estadoActual = UP;
        }

void AntireboteMEF(void){
      switch (estadoActual) {
            case UP:{
                  if(!digitalRead( TEC1 )){
                        estadoActual = FALLING;
                  }
            }
            break;
            
            case FALLING:{
				for ( buffer = 0; buffer < 4; buffer++ ){  ////////////////////////////////////////////////////////////////////////
					dato = uartReadByte ( UART_USB );	   //	
					dato = 0;							   //  Borra el buffer, debido a que si se presionaba mas
					red = 0;							   //  de 4 veces un tecla para seleccionar un estado, en la proxima					
					redyellow = 0;						   //  carga se almacenaba esa letra de mas apretada.
					green = 0;							   //
					yellow = 0;                            ////////////////////////////////////////////////////////////////////////
				}

				  i=0; // Cada vez que se presiona la tecla, se vuelve la variable i=0 para poder cargar los 4 estados
                  //delay(10);
                  if(!digitalRead( TEC1 )){
                        estadoActual = DOWN;
						uartWriteString( UART_USB, "ATENCION SE PEDIRA QUE INGRESE LOS TIEMPOS DE LOS ESTADOS\r\n\n" );
                        uartWriteString( UART_USB, "Para ingresar tiempo ROJO         presionar tecla 'a' (minuscula)\r\n" );
						uartWriteString( UART_USB, "Para ingresar tiempo ROJOAMARILLO presionar tecla 'b' (minuscula)\r\n" );
						uartWriteString( UART_USB, "Para ingresar tiempo VERDE        presionar tecla 'c' (minuscula)\r\n" );
						uartWriteString( UART_USB, "Para ingresar tiempo AMARILLO     presionar tecla 'd' (minuscula)\r\n\n" );
						
						while(i<4){ //Bucle while para que solo salga cuando se haya asignado satisfactoriamente los tiempos a los estados
							dato = uartReadByte ( UART_USB );
						//No se utilizo un Switch-Case, porque no se asignaban correctamente los valores, pedia constantemente volver a cargarlos	
							if(dato==97){
								dato = 0;
								uartWriteString( UART_USB, "Ingresar tiempo Rojo, tiempo comprendido solo entre 1 y 4 seg\r\n" );
								a:
								dato = uartReadByte ( UART_USB );
								if(dato == 49 || dato == 50 || dato == 51 || dato == 52){
									red = (dato - 48);// Formula para obtener el valor de la tecla numerica que se presiona
									uartWriteString( UART_USB, "Valor agregado...\r\n\n" );
								}else{
									goto a; //Funcion GoTo para asignar correctamente los tiempos, en caso de ser un valor
								}           //no definido o Nulo, vuelve al IF, para esperar el dato correcto
								i=i+1;//Incrementa la variable i para volver a cargar el proximo tiempo
							}
							
							if(dato==98){
								dato = 0;
								uartWriteString( UART_USB, "Ingresar tiempo RojoAmarillo, tiempo comprendido solo entre 1 y 4 seg\r\n" );
								b:
								dato = uartReadByte ( UART_USB );
								if(dato == 49 || dato == 50 || dato == 51 || dato == 52){
									redyellow = (dato - 48);
									uartWriteString( UART_USB, "Valor agregado...\r\n\n" );
								}else{
									goto b;
								}
								i=i+1;
							}
							
							if(dato==99){
								dato = 0;
								uartWriteString( UART_USB, "Ingresar tiempo Verde, tiempo comprendido solo entre 1 y 4 seg\r\n" );
								c:
								dato = uartReadByte ( UART_USB );
								if(dato == 49 || dato == 50 || dato == 51 || dato == 52){
									green = (dato - 48);
									uartWriteString( UART_USB, "Valor agregado...\r\n\n" );
								}else{
									goto c;
								}
								i=i+1;
							}
							
							if(dato==100){
								dato = 0;
								uartWriteString( UART_USB, "Ingresar tiempo Amarillo, tiempo comprendido solo entre 1 y 4 seg\r\n" );
								d:
								dato = uartReadByte ( UART_USB );
								if(dato == 49 || dato == 50 || dato == 51 || dato == 52){
									yellow = (dato - 48);
									uartWriteString( UART_USB, "Valor agregado...\r\n\n" );
								}else{
									goto d;
								}
								i=i+1;
							}							
						}
						uartWriteString( UART_USB, "Tiempos cargados exitosamente, para cargar nuevos tiempos presionar TEC1\r\n\n" );									
                  }else estadoActual = UP;			  
            }
            break;
            
            case DOWN:{
                  if(digitalRead( TEC1 )){
                        estadoActual = RISING;
                  }
            }
            break;
            
            case RISING:{
                  //delay(10);
                  if(digitalRead( TEC1 )){
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