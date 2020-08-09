////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  COMUNICACIÓN PC - PIC POR USB                             //
//       Clase de dispositivo CDC USB emulando dispositivo RS232              //
//                                                                            //
//                         Neurona Servicios                                      //
////////////////////////////////////////////////////////////////////////////////

#include <18F2550.h>             //PIC a emplear

#fuses HSPLL,NOWDT,NOLVP,USBDIV,PLL1,CPUDIV1,VREGEN  //Registros para funcionamiento optimo del USB

#use delay(clock=48000000)       //Frecuencia de oscilacion

#include <usb_cdc.h>             //Librería de control USB

/******************************************************************************/
/*************************  FUNCIÓN PRINCIPAL  ********************************/

void main() {

   char recepcion;               //Dato recibido del PC
   
   set_tris_a(0b0000000);        //Se configuran los pines del puerto A como salidas
   output_a(0b0000000);          //Se establecen todas las salidas en cero
   
   
   // CONFIGURACIONES DEL PUERTO COM- USB CDC
   usb_cdc_line_coding.dwDTERrate = 115200;     //Tasa de baudios
   usb_cdc_line_coding.bCharFormat = 0;
   usb_cdc_line_coding.bParityType = 0;
   usb_cdc_line_coding.bDataBits = 8;
   (int8)usb_cdc_carrier = 0;
   usb_cdc_got_set_line_coding = FALSE;
   usb_cdc_break = 0;
   usb_cdc_put_buffer_nextin = 0;
   usb_cdc_get_buffer_status.got = 0;


   usb_init();                   //Inicialización del control del USB
   output_a(0b000001);           // Indicador de encendido, Pin A0
   do  {
      usb_task();                //Detección de la conexión de dispositivo USB
      //Devuelve TRUE si dispositivo ha sido enumerado por el PC
      if (usb_enumerated()) {   
         //Si se ha recibido dato...
         if (usb_cdc_kbhit()){         
            recepcion=usb_cdc_getc();  //lo lee
            //si es caracter vacio(barra espaciadora)enciende o apaga visualización
            
            switch (recepcion){
               
               case 'P':               // COMANDO DE PRUEBA DE PUERTO
                  usb_cdc_putc('P');
               break;
            
               case 'N':               // COMANDO DE ENCENDIDO
                  output_a(0b0010000);
               break;
               
               case 'F':              // COMANDO DE APAGADO
                 output_a(0b0000000);
               break;
            
            }
            
         }

         delay_ms(300);
      }
   } while (TRUE);
}
//                                                                            //
