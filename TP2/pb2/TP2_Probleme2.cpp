
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
enum etat{COULEUR_ETEINT,COULEUR_ROUGE,COULEUR_VERT};
int main()
{
  
  DDRA |= (1 << DDA0) | (1 << DDA1); // PORT A est en mode sortie
  DDRD &= ~(1 << DDD2);              // PORT D est en mode entree
q etat state =etat::COULEUR_ROUGE;                          // le compteur est initialise a 0.
  PORTA |=(1<<PA1)        ;                          // c'est un compteur de 32 bits

  for (;;) // boucle sans fin
  {

  switch(state){
    case etat::COULEUR_ROUGE:
                    PORTA &= ~(PORTA);  
                    PORTA |=(1<<PA1);
                    while(PIND & 0x04)
                       {
                        _delay_ms(10); 
                         PORTA &= ~(PORTA);  
                         PORTA |= (1<<PORTA0);
                         _delay_ms(20); 
                         PORTA &= ~(PORTA);  
                         PORTA |= (1<<PORTA1);
                         if(!(PIND & 0x04))
                            state=etat::COULEUR_VERT;
                       }
                       break;
    case etat::COULEUR_VERT:
                    PORTA &= ~(PORTA);  
                    PORTA |= (1<<PORTA0);
                    while(PIND & 0x04)
                       {
                        _delay_ms(20); 
                        PORTA &= ~(PORTA); 
                         PORTA |= (1<<PORTA1);
                         if(!(PIND & 0x04))
                            state=etat::COULEUR_ETEINT;
                       }
                        break;
    case etat::COULEUR_ETEINT:
                    PORTA &= ~(PORTA);
                     while(PIND & 0x04)
                       {
                        _delay_ms(20); 
                        PORTA &= ~(PORTA); 
                        PORTA |= (1<<PORTA0);
                         if(!(PIND & 0x04))
                            state=etat::COULEUR_ROUGE;
                       }
  }  
  }
  return 0;

  }