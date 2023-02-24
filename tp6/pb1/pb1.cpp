#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define MINUTERIE_1S 7813
const int DELAI=30;
volatile uint8_t gBoutonPoussoir=0;
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
    return (PIND & (1 << PIND2)); 
}
void partirMinuterie ( uint16_t  duree ) {

// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
gMinuterieExpiree=0;
TCNT1 = 0 ;
OCR1A = duree;
TCCR1A = 0 ;
TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10) ;
TCCR1C = 0;
TIMSK1 = (1<<OCIE1A) ;
}


ISR(TIMER1_COMPA_vect) {
    gMinuterieExpiree = 1;
    _delay_ms(DELAI);
}

ISR(INT0_vect) {
    _delay_ms(DELAI);
    if(PIND & (1<<PIND2))
        gBoutonPoussoir = 1;
    else
        gBoutonPoussoir = 0;
    EIFR |= (1 << INTF0) ;
}


void initialisation()
{
    cli();
    DDRB |= (1 << DDB0) | (1 << DDB1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00);
    sei();
}
void attendreMinuterie(){
    while(gMinuterieExpiree==0){}
}

int main() {
    initialisation();
    while (true) {
        int counter=0;
        // Attente de l'appui sur le bouton-poussoir
        while (gBoutonPoussoir==0) {}

        // Compteur qui incrémente 10 fois par seconde
        while (counter < 120 && gBoutonPoussoir==1) {
            partirMinuterie(MINUTERIE_1S / 10);
            attendreMinuterie();
            counter++;
        }
        // Clignotement vert pendant 1/2 seconde
        for(int i=0; i<10; i++) {
            allumerVert();
            partirMinuterie(MINUTERIE_1S / 25);
            attendreMinuterie();
            eteindre();
            partirMinuterie(MINUTERIE_1S / 25);
            attendreMinuterie();
        }  

        // Attente de 2 secondes
        partirMinuterie(7813 * 2);
        attendreMinuterie();

        // Clignotement rouge (compteur / 2) fois au rythme de 2 fois par seconde
        for (int i = 0; i < counter / 2; ++i) {
            allumerRouge();
            partirMinuterie(MINUTERIE_1S / 4);
            attendreMinuterie();
            eteindre();
            partirMinuterie(MINUTERIE_1S / 4);
            attendreMinuterie();
        }

        // Lumière verte pendant 1 seconde
        allumerVert();
        partirMinuterie(MINUTERIE_1S);
        attendreMinuterie();
        eteindre();
        gMinuterieExpiree=0;
    }

        return 0;
}
