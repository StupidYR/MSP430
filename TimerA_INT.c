#include <msp430f5529.h>

void clock_check();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    
    P1DIR |= BIT0;      
    P1OUT &= ~BIT0;      //P1.0端口输出模式
    
    TA0CCR0 = 62500;    //SMCLK -->DCOCLKDIV（1.048576MHZ） ; 
                       //定时周期500ms： 62500 = 500ms / (1 /（f_SMCLK / ID）) 
                       // TA0CCR0 最大值为 0xFF（65535）
    
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR + TAIE;
                      //SMCLK作为时钟源；ID：8分频；增模式；清除TAR计数器；TAIFG中断使能
    
    clock_check();      //检查时钟源是否稳定
    
    _EINT();    //开启总中断
}

#pragma vector=TIMER0_A1_VECTOR        //TIMER0_A1含有CCR1、CCR2和 TAIFG 中断
                                       //TIMER0_A0仅含有CCR0
__interrupt void TIMER0_A1(void)       //定义一个名叫TIMER0_A1的中断函数
{
    TA0CTL &= ~TAIFG;   //清除中断标志位
    P1OUT ^= BIT0;      //LED闪烁
}
void clock_check()
{
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
      SFRIFG1 &= ~OFIFG;        
    }while (SFRIFG1 & OFIFG);     
}