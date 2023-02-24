#include <can.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

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




int main() {
    initialisation();
    can CAN;
    while(true){
        uint8_t puissance = CAN.lecture(PA0)>>2;
        if (puissance < 25)
            allumerVert();
        if (25 < puissance && puissance < 70)
             allumerambre();
        if (puissance > 70)
            allumerRouge();
    }

}