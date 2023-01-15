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
  DDRA |= (1 << DDA0) | (1 << DDA1); // PORT A est en mode sortie
  DDRD &= ~(1 << DDD2);              // PORT D est en mode entree
                                     // le compteur est initialise a 0.
                                     // c'est un compteur de 32 bits

  for (;;) // boucle sans fin
  {

  //  

  // PORTA |= (1 << PA0);
  // _delay_ms(1000);
  // PORTA &= ~(PORTA);

  // PORTA|=(1<<PORTA1);
  // _delay_ms(1000);
  // PORTA &= ~(PORTA);
    if (PIND & 0x04)
    {
      PORTA |= (1 << PA0);
  _delay_ms(1000);
  PORTA &= ~(PORTA);

  PORTA|=(1<<PORTA1);
  _delay_ms(1000);
  PORTA &= ~(PORTA);
    }
  }
  return 0;

  }
