#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const int DELAI=30;
volatile uint8_t compteur=0;
volatile uint8_t etat=0;
void eteindre() 
{
    PORTB &= ~(PORTB);
}
void allumerRouge()
{
    eteindre();
    PORTB |= (1 << PORTB1);
}

void allumerVert() 
{
    eteindre();
    PORTB |= (1 << PORTB0);
}
void partirMinuterie ( uint16_t  duree ) {

// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1 = 0 ;
OCR1A = duree;
TCCR1A = 0 ;
TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10) ;
TCCR1C = 0;
TIMSK1 = (1<<OCIE1A) ;
}

ISR(TIMER1_COMPA_vect) {
    compteur+=10;
}


ISR (INT0_vect ) {
   // anti-rebond
   _delay_ms(DELAI);
   etat++;
}
void initialisation()
{
    cli();
    DDRB |= (1 << DDB0) | (1 << DDB1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) | (1<<ISC01);
    sei();
}

int main()
{ 
    initialisation();
    allumerRouge();
    if (etat==1){
     for(int i=0;i<12;i+=1)
        partirMinuterie(7813);
    }
    if(compteur==120)
        eteindre();
    for(;;){

    }
return 0;

}