#include<msp430f5529.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P8DIR |= BIT1;
    P8OUT &= ~BIT1;
    
    P1REN |= BIT2;      //配置上拉电阻
    P1OUT |= BIT2;      //初始化端口电平
    P1IES &= ~BIT2;     //配置下降沿触发
    P1IFG &= ~BIT2;     //清除中断标志位
    P1IE |= BIT2;       //使能端口中断
    
    __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P8OUT |= BIT1;
    P1IFG &= ~BIT2;
}
