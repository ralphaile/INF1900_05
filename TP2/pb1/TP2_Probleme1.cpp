/*
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

#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h>
enum State { INIT, SECOND_CLICK, THIRD_CLICK };
int main()
{
    DDRA |= (1 << DDA0);
    DDRD &= ~(1 << DDD2);
    State state = State::INIT;
    PORTA &= ~(PORTA);
    int compteur;

    for (;;) // boucle sans fin
    {

        switch (state)
        {
        case State::INIT:
            PORTA &= ~(PORTA);
            while (PIND & 0x04)
            {
                _delay_ms(50);
                state = State::SECOND_CLICK;
            }
            break;
        case State::SECOND_CLICK:
            while (PIND & 0x04)
            {
                _delay_ms(50);
                state = State::THIRD_CLICK;
            }
            compteur=2;
            break;
        case State::THIRD_CLICK:
            while (PIND & 0x04)
            {
                _delay_ms(50);
                compteur++;
                if (compteur == 3) 
                {
                    PORTA |= (1 << PORTA0);
                    _delay_ms(2000);
                    PORTA &= ~(PORTA);
                    state = State::INIT;
                }
            }
            break;
        }
    }

    return 0;

}

