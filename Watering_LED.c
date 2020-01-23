#include<msp430f5529.h>

void watering_LED(void);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= BIT0;
    P8DIR |= BIT1 + BIT2;
    P1DIR |= BIT1 + BIT2+ BIT3 + BIT4 + BIT5;
    while(1)
    {
      P1OUT |= BIT0;
      __delay_cycles(3000);
      P1OUT &= ~BIT0;
      
      P8OUT |= BIT1;
      __delay_cycles(3000);
      P8OUT &= ~BIT1;
      
      P8OUT |= BIT2;
      __delay_cycles(3000);
      P8OUT &= ~BIT2;
      
      void watering_LED(void);
    }
}
void watering_LED(void)
{
    int i;
    for(i=BIT1;i<=BIT5;i++)
    {
      P1OUT |= i;
      __delay_cycles(3000);
      P1OUT &= ~i;
    }
}