#include <msp430.h>

void setup() {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P1DIR = 62;	// equal to 0x00111110


	P1DIR &= ~BIT7; // enable S1 button
	P1REN = BIT7;
	P1OUT = BIT7;

	P2DIR &= ~BIT2; // enable S1 button
	P2REN = BIT2;
	P2OUT = BIT2;
}



int main(void) {
	setup();

	while(1) {
		int shift = BIT1;

		if( !(P1IN & BIT7) ){
			while(shift < BIT6) {
				P1OUT += shift;
				shift <<= 1;
				__delay_cycles(100000);
			}
		} else if ( !(P2IN & BIT2) ) {
			shift = BIT1;
			while(shift < BIT6) {
				P1OUT -= shift;
				shift <<= 1;
				__delay_cycles(100000);
			}
		}
	}
}


