/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int main()
{
  DDRA |= (1 << DDA0); // PORT A est en mode sortie
  DDRD &= ~(1 << DDD2);              // PORT D est en mode entree
  const int DELAI =10;
  // while(1) // boucle sans fin
  // {
    int a=1000;
    int b=1000;
      for(int j=0;j<3000;j++){
        PORTA |= (1 << PORTA0);
        for(int i=0;i<a-DELAI;i++)
          _delay_us(DELAI);
        PORTA &= ~(PORTA);
        for(int i=0;i<b-a-DELAI;i++)
          _delay_us(DELAI);
        a-=DELAI;
      //}
  }
  return 0;

  }
