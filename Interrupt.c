#include<msp430f5529.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P8DIR |= BIT1;
    P8OUT &= ~BIT1;
    
    P1REN |= BIT2;      //������������
    P1OUT |= BIT2;      //��ʼ���˿ڵ�ƽ
    P1IES &= ~BIT2;     //�����½��ش���
    P1IFG &= ~BIT2;     //����жϱ�־λ
    P1IE |= BIT2;       //ʹ�ܶ˿��ж�
    
    __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P8OUT |= BIT1;
    P1IFG &= ~BIT2;
}
