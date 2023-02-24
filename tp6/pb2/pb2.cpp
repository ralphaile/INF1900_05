#include <can.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
const int DELAI = 10;


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

}

int main() {
    initialisation();
    initialisationUART();
    Memoire24CXXX memoir;
    can CAN;
    while(true){
        uint8_t puissance = CAN.lecture(PA0)>>2;
        if (puissance < 35)
            allumerVert();
        if (35 < puissance && puissance < 50)
             allumerambre();
        if (puissance > 50)
            allumerRouge();
    }
}