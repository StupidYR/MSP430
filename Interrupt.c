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
    
    _ENIT();    //为__enable_interrupt()的宏定义；总中断使能
}

#pragma vector=PORT1_VECTOR     //使能P1端口的中断
__interrupt void Port_1(void)   //将中断函数命名为Port_1
{
    P8OUT |= BIT1;
    P1IFG &= ~BIT2;
}
