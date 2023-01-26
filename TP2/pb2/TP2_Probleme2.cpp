
/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>


void eteindre() {
    PORTA &= ~(PORTA);
}
void allumerRouge(){
    eteindre();
    PORTA |= (1 << PORTA1);
}

void allumerVert() {
    eteindre();
    PORTA |= (1 << PORTA0);
}
const int DELAI=10;
enum class Etat { COULEUR_ETEINT, COULEUR_ROUGE, COULEUR_VERT };
int main()
{

    DDRA |= (1 << DDA0) | (1 << DDA1); 
    DDRD &= ~(1 << DDD2);
    Etat etat = Etat::COULEUR_ROUGE; 
    allumerRouge();

    for (;;)
    {

        switch (etat) {
            case Etat::COULEUR_ROUGE:
                allumerRouge();
                while (PIND & 0x04)
                {
                    _delay_ms(DELAI);
                    allumerVert();
                    _delay_ms(DELAI);
                    allumerRouge();
                    if (!(PIND & 0x04))
                        etat = Etat::COULEUR_VERT;
                }
                break;
            case Etat::COULEUR_VERT:
                allumerVert();
                while (PIND & 0x04)
                {
                    _delay_ms(DELAI);
                    allumerRouge();
                    if (!(PIND & 0x04))
                        etat = Etat::COULEUR_ETEINT;
                }
                break;
            case Etat::COULEUR_ETEINT:
                eteindre();
                while (PIND & 0x04)
                {
                    _delay_ms(DELAI);
                    allumerVert();
                    if (!(PIND & 0x04))
                        etat = Etat::COULEUR_ROUGE;
                }
                break;
        }
    }
    return 0;

}

