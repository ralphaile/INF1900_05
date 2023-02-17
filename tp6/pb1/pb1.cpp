
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const int DELAI=30;
volatile uint8_t counter = 0;
volatile uint8_t compteurEtat = 0;
volatile uint8_t gMinuterieExpire = 0;
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
    gMinuterieExpiree = 1;
}

ISR(INT0_vect) {
    gBoutonPoussoir = 1;
    // anti-rebond
    _delay_ms(DELAI);
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
enum class Etat { INIT, GREEN, PAUSE, RED, END };
int main()
{ 
    initialisation();
    switch (etat) {
    case Etat::INIT: { //ETAT INIT commence si bouton acctionner, peut diviser dernier etat
        while (gBoutonPoussoir == 1) {
            for (int counter = 0, counter < 120, counter++) {
                partirMinuterie(7813);
                if (gMinuterieExpire == 1);
                counter += 10
            }
            compteurEtat++
        }
        compteurÉtat++    
        break;
    case Etat::GREEN:
         partirMinuterie(7813/2)
            while(gMinuterieExpire==0)
            {

            //lumiere clignote vert
            }
             compteur++;
             break;
    case Etat::PAUSE:
        partirMinuterie(7813*2);
            if( gMinuterieExpire==1)
                compteur++;
    case Etat::RED:
        partirMinuterie( counter/(2*2))
            while(gMinuterieExpire==0)
            {
                //lumiere clignote rouge
            }
            compteur++
                
            break;
    case END:
        partirMinuterie(7813)
            while (gMinuterieExpire == 0) {
                allumerVert();
            }
        if (gboutonpoussoir == 1)
            compteurEtat = 0
        else
            eteindre();
                break;
    }

}

