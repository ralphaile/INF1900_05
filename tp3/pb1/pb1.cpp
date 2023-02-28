#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int main()
{
  DDRA = (1 << DDA0) | (1 << DDA1);
  PORTA = (1 << PORTA0);
  DDRD &= ~(1 << DDD2);
  while(true) // boucle sans fin
  {
    double a=250;
    double b=250;
      for(int j=0;j<3000;j++)
      {
        PORTA |= (1 << PORTA1);
        for(int i=0;i<a;i++)
          _delay_us(1);
        PORTA &= ~(PORTA);
        for(int i=0;i<(b-a);i++)
          _delay_us(1);
        a--;
      }
  }
  return 0;

  }