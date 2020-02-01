/*********************Timer_A0****************************

P1.2引脚：输出Timer_A0_CCR1方波
P1.3引脚：输出Timer_A0_CCR2方波

TA0CTL：Timer_A0的控制寄存器

TA0CCTLn：Timer_A0的捕获 /比较控制 n寄存器（默认为比较模式）

TA0CCRn：Timer_A0的捕获 /比较 n寄存器        

************************END****************************/

#include <msp430f5529.h>

void clock_check();

void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;
      P1DIR |= BIT2+BIT3;               
      P1SEL |= BIT2+BIT3;               // P1.2和P1.3引脚功能选为定时器输出
      
      clock_check();
      
      TA0CCR0 = 512-1;                  // 控制PWM周期
      //PWM周期 = (TA0CCR0 + 1) / f_TASSEL
      //此时    = 512 / 32.768K = 15.625us
      
      TA0CCTL1 = OUTMOD_7;              // CCR1比较输出模式7：复位/置位
      TA0CCR1 = 384;                    // CCR1：控制PWM占空比
      // 此模式下占空比 = TA0CCR1 / TA0CCR0  
      //此时            = 75%
      
      TA0CCTL2 = OUTMOD_7;              // CCR2 比较输出模式7：复位/置位
      TA0CCR2 = 128;                    // CCR2：控制PWM占空比
      //占空比为 25%
      
      TA0CTL = TASSEL_1 + MC_1 + TACLR;	
      //TASSEL：选择ACLK时钟源；MC：选择增计数模式；TACLR：清除TAR计数器
      
      __bis_SR_register(LPM3_bits);    	// 进入LPM3功耗模式
}
void clock_check()
{    
      do 
        {
          UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
          SFRIFG1 &= ~OFIFG; 
        }
      while (SFRIFG1 & OFIFG);           
}
