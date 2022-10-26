/* 
//
//
//                   MSP430FR2311
//                 -----------------
//             /|\|                 |
//              | |                 |
//              --|RST              |
//                |                 |
//                |             P1.7|-> Data OUT (UCA0SIMO)
//                |                 |
//                |             P1.6|<- Data IN  (UCA0SOMI)
//                |                 |
//                |             P1.5|-> Serial Clock Out (UCA0CLK)
//
*/

#include "msp430fr2311.h"
#include <msp430.h>

unsigned char RXData = 0;
unsigned char TXData;

unsigned char SPIread() {
    while (UCA0STATW & UCBUSY);
    RXData = UCA0RXBUF;
    return RXData;
}

void SPIwrite(unsigned char TXData) {
    UCA0TXBUF = TXData;             // Transmit characters
    while (UCA0STATW & UCBUSY);
}

void initSPI() {
    P1SEL0 |= BIT5 | BIT6 | BIT7;             // set 3-SPI pin as second function


    UCA0CTLW0 |= UCSWRST;                     // **Put state machine in reset**
    UCA0CTLW0 |= UCMST|UCSYNC|UCCKPL|UCMSB;   // 3-pin, 8-bit SPI master
                                              // Clock polarity high, MSB
    UCA0CTLW0 |= UCSSEL__ACLK;                // Select ACLK
    UCA0BR0 = 0x02;                           // BRCLK = ACLK/2
    UCA0BR1 = 0;                              //
    UCA0MCTLW = 0;                            // No modulation
    UCA0CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
    PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode
                                              // to activate previously configured port settings
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer

    initSPI();
    SPIwrite(0x80);
    __delay_cycles(20);    
    SPIwrite(0x00);
    //unsigned char temphigh=SPIread();
    //unsigned char templow=SPIread();

    while(1)
    {
        
        
        
        /*
        __bis_SR_register(LPM0_bits | GIE);   // enable global interrupts, enter LPM0
        __no_operation();                     // For debug,Remain in LPM0
        __delay_cycles(2000);                 // Delay before next transmission
        TXData++;                             // Increment transmit data
        */
    }
}
