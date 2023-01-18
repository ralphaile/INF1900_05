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
enum etat{INIT, SECOND_CLICK, THIRD_CLICK};
int main()
{
  DDRA |= (1 << DDA0) | (1 << DDA1); // PORT A est en mode sortie
  DDRD &= ~(1 << DDD2);              // PORT D est en mode entree
  etat state = etat::INIT;                                   // le compteur est initialise a 0.

    PORTA &= ~(PORTA);                       // c'est un compteur de 32 bits

  for (;;) // boucle sans fin
  {

    switch (state)
    {
    case etat::INIT: 
                        PORTA &= ~(PORTA);
                        while(PIND & 0x04)
                        {
                            _delay_ms(50);                            
                            state= etat::SECOND_CLICK;
                        }
                    break;
    case etat::SECOND_CLICK: while(PIND & 0x04)
                                {
                                _delay_ms(50);  
                                state=etat::THIRD_CLICK;
                                }
                            break;
    case etat::THIRD_CLICK: while(PIND & 0x04)
                               {
                                     _delay_ms(50);  
                                    PORTA |= (1<< PORTA0);
                                    _delay_ms(2000);
                                    state=etat::INIT;                                  
                                    }
                            break;
    }
 } 

  return 0;

  }

