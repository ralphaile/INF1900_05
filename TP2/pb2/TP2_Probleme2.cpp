
/*
 *   +--------+---+--------+--------+
 *   |   COULEUR_ROUGE     | 0 |   COULEUR_ROUGE | rouge |
 *   +--------+---+--------+--------+
 *   |                     | 1 |   COULEUR_VERT  | ambre |
 *   +--------+---+--------+--------+
 *   |    COULEUR_VERT     | 0 |   COULEUR_VERT  | vert  |
 *   +--------+---+--------+--------+
 *   |                     | 1 | COULEUR_ ETEINT | rouge |
 *   +--------+---+--------+--------+
 *   |   COULEUR_ ETEINT   | 0 | COULEUR_ ETEINT | éteint|
 *   +--------+---+--------+--------+
 *   |                     | 1 |   COULEUR_ROUGE | vert  |
 *
 *
 *
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

void allumerRouge(){
    PORTA &= ~(PORTA); //Eteindre la DEL
    PORTA |= (1 << PORTA1);//Allumer en couleur Rouge
}

void allumerVert() {
    PORTA &= ~(PORTA);//Eteindre la DEL
    PORTA |= (1 << PORTA0);//Allumer en couleur Vert
}
enum State { COULEUR_ETEINT, COULEUR_ROUGE, COULEUR_VERT };//Les differents etats de notre systeme
int main()
{

    DDRA |= (1 << DDA0) | (1 << DDA1); //Les PORT A0 et A1 sont en sorties
    DDRD &= ~(1 << DDD2);//Le PORT D2 est en entree
    State state = State::COULEUR_ROUGE; 
    allumerRouge();

    for (;;)
    {

        switch (state) {
            case State::COULEUR_ROUGE:
                allumerRouge();
                while (PIND & 0x04)
                {
                    _delay_ms(10);//On fait un delai pour ignorer les rebonds
                    allumerVert();//On allumer le vert puis le rouge pour avoir la couleur ambre
                    _delay_ms(20);
                    allumerRouge();
                    if (!(PIND & 0x04))
                        state = State::COULEUR_VERT;
                }
                break;
            case State::COULEUR_VERT:
                allumerVert();
                while (PIND & 0x04)
                {
                    _delay_ms(20);
                    allumerRouge();
                    if (!(PIND & 0x04))
                        state = State::COULEUR_ETEINT;
                }
                break;
            case State::COULEUR_ETEINT:
                PORTA &= ~(PORTA);
                while (PIND & 0x04)
                {
                    _delay_ms(20);
                    allumerVert();
                    if (!(PIND & 0x04))
                        state = State::COULEUR_ROUGE;
                }
                break;
        }
    }
    return 0;

}
