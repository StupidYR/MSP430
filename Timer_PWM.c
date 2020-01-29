#include <msp430f5529.h>
void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;         
      P1DIR |= BIT2+BIT3;               
      P1SEL |= BIT2+BIT3;               // P1^2和P1^3引脚功能选为定时器输出
      
      TA0CCR0 = 512-1;                  // PWM周期定义
      TA0CCTL1 = OUTMOD_7;              // CCR1比较输出模式7：复位/置位
      TA0CCR1 = 384;                    // CCR1 PWM 占空比定义
      // 此模式下占空比 = TA0CCR1 / TA0CCR0          ————>3/4
      
      TA0CTL = TASSEL_1 + ID_0 + MC_1 + TACLR;	
      // 配置Timer_A的控制寄存器TA_CTL
      //TASSEL：选择ACLK时钟源；ID：选择分频；MC：选择增计数模式；TACLR：清除TAR计数器
      
      __bis_SR_register(LPM3_bits);    	// 进入LPM3功耗模式
}
