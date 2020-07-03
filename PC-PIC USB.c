////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  COMUNICACI�N PC - PIC POR USB                             //
//       Clase de dispositivo CDC USB emulando dispositivo RS232              //
//                                                                            //
//                         RobotyPic (c)                                      //
////////////////////////////////////////////////////////////////////////////////

#include <18F2550.h>             //PIC a emplear

#fuses HSPLL,NOWDT,NOLVP,USBDIV,PLL5,CPUDIV1,VREGEN

#use delay(clock=4000000)       //Frecuencia del cristal oscilador externo

#include <usb_cdc.h>             //Librer�a de control USB

/******************************************************************************/
/*************************  FUNCI�N PRINCIPAL  ********************************/

void main() {

   char recepcion;               //Dato recibido del PC
   
   set_tris_a(0b0000000);
   output_a(0b0000000);
   usb_cdc_init();               //Inicializaci�n del modo CDC
   usb_init();                   //Inicializaci�n del control del USB
   
   do  {
      usb_task();                //Detecci�n de la conexi�n de dispositivo USB
      //Devuelve TRUE si dispositivo ha sido enumerado por el PC
      if (usb_enumerated()) {   
         //Si se ha recibido dato...
         if (usb_cdc_kbhit()){         
            recepcion=usb_cdc_getc();  //lo lee
            //si es caracter vacio(barra espaciadora)enciende o apaga visualizaci�n
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
