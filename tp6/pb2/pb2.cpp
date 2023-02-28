/*
Travail : TP6_PROBLEME_2
Section # : SECTION 5
Équipe # : 121
Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau
Auteurs: Ralph Alaile et Ireina Hedad

Description programme:Ce programme utilise un capteur de lumière pour déterminer la quantité de lumière ambiante.
Il actionnera une lumière verte lorsque la quantité de lumiere est basse, rouge lorsqu'elle est particulièrement haute 
et ambre le reste du temps.

Nous avons eu besoin d'un breadboard pour ce programme sur lequel était connecté le capteur ainsi qu'un condensateur, 
une résistance et finalement plusieurs cables de métal permettant la transmission.
Deux cables reliaient le breadboard à la carte mère, le premier (rouge) jusqu'à VCC et ground d'un de nos ports, 
puis l'autre (bleu) était relié à A0 pour capté les messages du capteurs. 
Finalement un cable connectait la DEL libre à notre port B2 pour voir la DEL s'allumer en fonction du programme.

Broches I/O:
    IN <- Port D2
    OUT <- Port B0 et Port B1

*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <can.h>
#include <memoire_24.h>
const int DELAI = 50;


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

void allumerambre(){
        _delay_ms(DELAI);
        allumerVert();
        _delay_ms(DELAI);
        allumerRouge();
}

void initialisation(){
    DDRA &= ~ (1<<DDA0);
    DDRB |= (1<<DDB0) | (1<<DDB1);
}
void initialisationUART ( void ) {
// 2400 bauds. Nous vous donnons la valeur des deux
// premiers registres pour vous éviter des complications.
UBRR0H = 0;
UBRR0L = 0xCF;
// permettre la réception et la transmission par le UART0
UCSR0A = 0 ;
UCSR0B = (1<< RXEN0)| (1<< TXEN0) ;
// Format des trames: 8 bits, 1 stop bits, sans parité
UCSR0C = (1<< UCSZ00)|(1<<UCSZ01) ;
}
void transmissionUART ( uint8_t donnee ) {

/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)))
        ;
/* Copy 9th bit to TXB8 */
UCSR0B &= ~(1<<TXB80);
if ( donnee & 0x0100 )
    UCSR0B |= (1<<TXB80);
/* Put data into buffer, sends the data */
UDR0 = donnee;
UDR0 = '\n';
}

int main() {
    initialisation();
    initialisationUART();
    can CAN;
    uint8_t faibleLumiere=200;
    uint8_t forteLumiere=240;
    while(true){
        uint8_t puissance = CAN.lecture(PA0)>>2;
        transmissionUART(puissance);
        if (puissance < faibleLumiere)
            allumerVert();
        if (faibleLumiere < puissance && puissance < forteLumiere)
             allumerambre();
        if (puissance > forteLumiere)
            allumerRouge();
    }
}