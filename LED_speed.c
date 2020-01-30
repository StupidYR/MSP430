#include<msp430f5529.h>
int flag=1;
void choose_delay();
void LED();
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
    P8DIR |= BIT1 + BIT2;
    P8OUT &= ~(BIT1 + BIT2);    //初始化LED的I/O口
    
    P1DIR &= ~BIT7;     //设置P1^7口为输入状态
    P1OUT |= BIT7;      //断后路
    P1REN |= BIT7;      //将P1^7口接上拉电阻
    P1IE |= BIT7;       //中断使能
    P1IFG &= ~BIT7;     //清除中断标志位
    P1IES |= BIT7;      //置1；设置下降沿触发
    __enable_interrupt();       //总中断使能
    
    while(1)
      LED();    //LED闪烁函数
}

#pragma vector = PORT1_VECTOR   //P1系列端口的总中断函数
__interrupt void port_1(void)   //定义一个名为port_1的中断函数
{
    while((P1IN & BIT7)==0);      //等待按键释放
    flag=~flag;
    P1IFG &= ~BIT7;       //清除中断标志位
}

void choose_delay()
{
   if(flag==0)
    __delay_cycles(100000);
  else
    __delay_cycles(200000);
}
void LED()
{
  P1OUT |= BIT0;
  P1OUT &= ~BIT5;
  choose_delay();
  
  P8OUT |= BIT1;
  P1OUT &= ~BIT0;
  choose_delay();
  
  P8OUT |= BIT2;
  P8OUT &= ~BIT1; 
  choose_delay();
  
  P1OUT |= BIT1;
  P8OUT &= ~BIT2;
  choose_delay();
  
  P1OUT |= BIT2;
  P1OUT &= ~BIT1;
  choose_delay();
  
  P1OUT |= BIT3;
  P1OUT &= ~BIT2;
  choose_delay();
  
  P1OUT |= BIT4;
  P1OUT &= ~BIT3; 
  choose_delay();
  
  P1OUT |= BIT5;
  P1OUT &= ~BIT4;
  choose_delay();
}
