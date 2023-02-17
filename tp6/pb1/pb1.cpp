#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const int DELAI=30;
volatile uint8_t gBoutonPoussoir=0;
volatile uint8_t counter = 0;
volatile uint8_t compteurEtat = 0;
volatile uint8_t gMinuterieExpiree = 0;

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

bool isButtonPressed(){
    if (PIND & (1 << PIND2)){
        _delay_ms(DELAI);
        return (PIND & (1 << PIND2)); 
    }
    return false;
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
    counter+=10;
}

ISR(INT0_vect) {
    _delay_ms(DELAI);
    if(isButtonPressed())
        gBoutonPoussoir = 1;
    else
        gBoutonPoussoir=0;
}


void initialisation()
{
    cli();
    DDRB |= (1 << DDB0) | (1 << DDB1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) ;
    sei();
}
enum class Etat { INIT, GREEN, PAUSE, RED, END };
int main()
{ 
    int compteurFinal=0;
    Etat etat = Etat::INIT;
    initialisation();
    while(true){
        switch (etat) {
        case Etat::INIT: { //ETAT INIT commence si bouton acctionner, peut diviser dernier etat
            while(gBoutonPoussoir==0){;}
            while (gBoutonPoussoir == 1 && counter<120) {
                partirMinuterie(7813);
                while(gMinuterieExpiree==0){;}
                gMinuterieExpiree=0;
            }      
            compteurFinal=counter;
            etat=Etat::GREEN;
            break;
        case Etat::GREEN:
            for(int i=0;i<10;i++){
                    partirMinuterie( 7813/25);
                    while(gMinuterieExpiree==0)
                        allumerVert();
                    gMinuterieExpiree=0;
                    partirMinuterie( 7813/25);
                    while(gMinuterieExpiree==0)
                        eteindre();
                    gMinuterieExpiree=0;
                }
                etat=Etat::PAUSE;
                gMinuterieExpiree=0;
                break;
        case Etat::PAUSE:
            partirMinuterie(7813*2);
            while(gMinuterieExpiree==0){;}
                if( gMinuterieExpiree==1){
                    etat=Etat::RED;
                    gMinuterieExpiree=0;
                    }
            break;
        case Etat::RED:
        for(int i=0;i<compteurFinal/2;i++){
            partirMinuterie( 7813/4);
            while(gMinuterieExpiree==0)
                allumerRouge();
            gMinuterieExpiree=0;
            partirMinuterie(7813/4);
            while(gMinuterieExpiree==0)
                eteindre();
            gMinuterieExpiree=0;
        }
        etat=Etat::END;
                break;
        case Etat::END:
            partirMinuterie(7813);
            while (gMinuterieExpiree == 0)
                    allumerVert();
            eteindre();
            gMinuterieExpiree=0;
            gBoutonPoussoir=0;
            counter=0;
            etat=Etat::INIT;
            break;
        }

    }
    }
}
