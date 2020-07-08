////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  COMUNICACIÓN PC - PIC POR USB                             //
//       Clase de dispositivo CDC USB emulando dispositivo RS232              //
//                                                                            //
//                         RobotyPic (c)                                      //
////////////////////////////////////////////////////////////////////////////////

#include <18F2550.h>             //PIC a emplear

#fuses HSPLL,NOWDT,NOLVP,USBDIV,PLL5,CPUDIV1,VREGEN

#use delay(clock=4000000)       //Frecuencia del cristal oscilador externo

#include <usb_cdc.h>             //Librería de control USB

/******************************************************************************/
/*************************  FUNCIÓN PRINCIPAL  ********************************/

void main() {

   char recepcion;               //Dato recibido del PC
   
   set_tris_a(0b0000000);
   output_a(0b0000000);
   
   usb_cdc_line_coding.dwDTERrate = 9600;
   usb_cdc_line_coding.bCharFormat = 0;
   usb_cdc_line_coding.bParityType = 0;
   usb_cdc_line_coding.bDataBits = 8;
   (int8)usb_cdc_carrier = 0;
   usb_cdc_got_set_line_coding = FALSE;
   usb_cdc_break = 0;
   usb_cdc_put_buffer_nextin = 0;
   usb_cdc_get_buffer_status.got = 0;

   //usb_cdc_init();               //Inicialización del modo CDC
   usb_init();                   //Inicialización del control del USB
   output_a(0b000001);
   do  {
      usb_task();                //Detección de la conexión de dispositivo USB
      //Devuelve TRUE si dispositivo ha sido enumerado por el PC
      if (usb_enumerated()) {   
         //Si se ha recibido dato...
         if (usb_cdc_kbhit()){         
            recepcion=usb_cdc_getc();  //lo lee
            //si es caracter vacio(barra espaciadora)enciende o apaga visualización
            if (recepcion=='N')  {
            output_a(0b0010000);
            usb_cdc_putc('n');
            }
            if (recepcion=='F') {
            usb_cdc_putc('f');
            output_a(0b0000000);
            } 
         }

         delay_ms(300);
      }
   } while (TRUE);
}
//                                                                            //
