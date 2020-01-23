#include<msp430f5529.h>

int key_flag=0;

void key_check(void);      //������������debounce

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    
    P1DIR &= ~BIT7;
    P1REN |= BIT7;       //����P1^7�ڣ�����������
    
    while(1)
    {
      key_check();
      
      if(key_flag == 1)
        P1OUT |= BIT0;
      else
        P1OUT |= BIT0;    
    }
}

void key_check(void)
{
    if(P1IN & BIT7 == 0)
    {
        __delay_cycles(1000);
        if(P1IN & BIT7 == 0)
        {
           key_flag = ~key_flag; 
        }
    }
}