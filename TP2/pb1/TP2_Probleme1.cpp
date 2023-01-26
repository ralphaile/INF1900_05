#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

enum class Etat{ INIT, SECOND_CLICK, TROISIEME_CLICK };
const int DELAI=20;
const int TEMPS_ALLUMER=2000;

Etat premierClick(){
    while(!(PIND & (1 << PIND2))){
        _delay_ms(DELAI);
    }
    while(PIND & (1 << PIND2)){
        _delay_ms(DELAI);
    }
    Etat nextEtat = Etat::SECOND_CLICK;
    return nextEtat;
}

Etat secondClick(){
    while(!(PIND & (1 << PIND2))){
        _delay_ms(DELAI);
    }
    while(PIND & (1 << PIND2)){
        _delay_ms(DELAI);
    }
    Etat nextEtat = Etat::TROISIEME_CLICK;
    return nextEtat;
}

Etat troisiemeClick(){
     while(!(PIND & (1 << PIND2))){
        _delay_ms(DELAI);
    }
    int compteur = 2;
        while (PIND & (1 << 2))
        {
            _delay_ms(DELAI);
            compteur++;
            if (compteur == 3)
            {
                PORTA |= (1 << PORTA0);
                _delay_ms(TEMPS_ALLUMER);
                PORTA &= ~(1 << PORTA0);
            }
        }
    Etat nextEtat= Etat::INIT;
    return nextEtat;
}
int main()
{
    DDRA |= (1 << DDA0);
    DDRD &= ~(1 << DDD2);
    Etat etat = Etat::INIT;
    PORTA &= ~(PORTA);

    for (;;) // boucle sans fin
    {

        switch (etat)
        {
        case Etat::INIT:
            PORTA &= ~(PORTA);
            etat=premierClick();
            break;
        case Etat::SECOND_CLICK:
            etat=secondClick();
            break;
        case Etat::TROISIEME_CLICK:
            etat=troisiemeClick();
            break;
        }
    }

    return 0;

}


