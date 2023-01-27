#define F_CPU 8000000UL
/*
 *   Ireina Hedad
 *   Ralph Aile
 *   
 *   Ce programme permet d'allumer la LED pendant 2 secondes après avoir cliquer sur le 
 *   bouton poussoir trois fois, puis pour la revoir s'allumer, il faudrait cliquer trois
 *   autre fois pour revoir la LED s'allumer. Nous avons utilisé un switchcase pour 
 *   pouvoir décrire les états un par un. Nos trois états sont nos 3 clicks avant que la
 *   LED s'allume. Évidemment, nous avons ajouté un délai au première état pour que la LED
 *   soit allumée le 2 secondes.
 *
 *   Table des états:
 *   +--------------+---+--------------+--------+
 *   | init         | 0 | init         | eteint |
 *   +--------------+---+--------------+--------+
 *   |              | 1 | SECOND_CLICK | eteint |
 *   +--------------+---+--------------+--------+
 *   | SECOND_CLICK | 0 | SECOND_CLICK | eteint |
 *   +--------------+---+--------------+--------+
 *   |              | 1 | THIRD_CLICK  | eteint |
 *   +--------------+---+--------------+--------+
 *   | THIRD_CLICK  | 0 | THIRD_CLICK  | eteint |
 *   +--------------+---+--------------+--------+
 *   |              | 1 | init         | init   |
 *   +--------------+---+--------------+--------+
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */

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


