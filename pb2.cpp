#include <can.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int DELAI = 30;


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
        _delay_ms(DELAI +5);
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
        uint16_t puissance = CAN.lecture(0x00);
        puissance = puissance << 8;
        puissance = puissance >> 8;
        if (puissance < 85)
            allumerVert();
        if (85 < puissance && puissance < 170)
             allumerambre();
        if (puissance > 170)
            allumerRouge();
    }

}