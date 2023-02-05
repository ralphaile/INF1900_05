#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int frequency=60;
int b=(1/frequency)*1000;
const int DELAI=2000;

void initialization(){
    DDRB |= (1<<DDB0) | (1<<DDbB1);
    PORTB |= (1<<PORTB1);
}
bool isButtonPressed(){
    if (PIND & (1 << PIND2)){
        _delay_ms(DEBOUNCE_DELAY);
        return (PIND & (1 << PIND2)); 
    }
    return false;
}

int main(){
    initialization();
    for(int a=0;a<=b; a=a+0.25*b;){
        for(int i=0;i<2000*frequency;i++){
            for(int j=0;i<a/DELAI;j++)
            {
                PORTB |= (1<<PORTB0);
                _delay_us(DELAI);
            }
            for(int k=0;i<(b-a)/DELAI;j++){
                PORTB &=~(PORTB);
                _delay_us(DELAI);
            }

        }
       
    }
}