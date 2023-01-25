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
#include <time.h>

int main()
{
  DDRA |= (1 << DDA0) | (1 << DDA1); // PORT A est en mode sortie
  DDRD &= ~(1 << DDD2);              // PORT D est en mode entree
                                     // le compteur est initialise a 0.
                                     // c'est un compteur de 32 bits
  int a=500;
  int b=1000;
  while(true) // boucle sans fin
  {
    time_t start_time = time(NULL);
    while (difftime(time(NULL), start_time) < 3){
      if (PIND & 0x04)
      {
      PORTA |= (1 << PORTA0);
      while(...) {
        _delay_us(a);
      }
      PORTA &= ~(PORTA);
      while(){
        _delay_us(b-a);
      }
      a--;
      a-=0.01;
      if(a==0)
        break;
 
    }
  }
  }
  return 0;

  }
