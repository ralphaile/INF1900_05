/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */
#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h> 

int main()
{

  
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits

  for(;;)  // boucle sans fin
  {
   PORTA = 0x0;
    if ( PIND & 0x04 )
      {

        PORTA =  compteur%2+ 0x1;
        compteur++;
        _delay_ms(1000);

      }
 
  }
  return 0; 
}
