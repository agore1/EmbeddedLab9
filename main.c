#include <msp430.h> 
#include "useful.h"

#define SI	 		BIT1
#define SO	 		BIT2
#define SCK			BIT4
#define	CE			BIT5
#define GREEN_LED	BIT6
#define	RED_LED		BIT0

//Declared Functions
void InitializeVariables(void);
void InitializePorts(void);
void InitializeClocks(void);
char SPI_bit_bang(char byte_to_send);

int main(void) {
	InitializePorts();
	InitializeClocks();

	while(1){

	}
	return 0;
}

void InitializePorts(void){
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR |= SI + CE + SCK + GREEN_LED + RED_LED; 		//Set these as outputs
	P1DIR &= ~SO;

	P1SEL |= BIT4;					//Set pin4 to output the smclk to check frequency
	P1SEL2 &= ~BIT4;				//Set pin4 to output the smclk to check frequency
}

void InitializeClocks(void){
	BCSCTL1 = CALBC1_16MHZ;		//select range of DCO
	DCOCTL =CALDCO_16MHZ;		//calibrate DCO to 16MHz - In reality closer to 7.8 MHz.
	BCSCTL2 &= ~(SELS);			//source the SMCLK from the DCO
	BCSCTL2 |= SELM_0;			//source the MCLK from the DCO
}

//BCSCTL1 = CALBC1_16MHZ + DIVA0;
//DCOCTL = CALDCO_16MHZ;

char SPI_bit_bang(char byte_to_send){
	P1OUT &= ~CE;
	P1OUT &=~SCK;
	__delay_cycles(4000);
	int i;
	for ( i=0; i<8; i++){
		if((byte_to_send & 1) && 1){
			P1OUT |= SI;
		}
		else{
			P1OUT &= ~SI;
		}
		byte_to_send>>1;
		__delay_cycles(50);
	}
	P1OUT |= SCK;
	__delay_cycles(50);
}

