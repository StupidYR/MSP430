/************** DCO：内部数字控制振荡源***************

  f_DCOCLK = D * (N + 1) * f_REFCLK / n

  f_DCOCLKDIV = (N + 1) * f_REFCLK / n

  t_delay = n x 32 x 32 x f_MCLK / f_REFCLK

注：D：FLLD 默认为FLLD_1，此时为二分频，D = 2
    N：FLLN 默认为FLLN = 31

    FLL的时钟是由REFCLK提供的
    f_REFCLK：REFCLK的参考时钟源的频率 默认为 XT1
    n：FLLREFDIV 默认为FLLREFDIV_0,此时为一分频，n = 1

*************************END**************************/

#include <msp430f5529.h>

void clock_check();
void IO_Init();

void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;
// 配置DCO 为 2.45MHz
      UCSCTL3 = SELREF_2;           //选择REFO来作为FLL的参考时钟源（REFCLK）
      clock_check();                //检测时钟源是否稳定
      __bis_SR_register(SCG0);      // 关闭FLL控制；   如果不关闭的话，FLL寄存器不会改变
      UCSCTL0 = 0;                  // 配置 DCOx = 0 , MODx = 0 ；
      UCSCTL1 = DCORSEL_3;          // 配置DCO的频率范围 1.51————6.07 
      UCSCTL2 = FLLD_0 + 74;        // 配置FLL_D：一分频    配置FLL_N：74
      __bic_SR_register(SCG0);      // 开启FLL控制
      __delay_cycles(76563);        //
      clock_check();
      
      while(1)
      {
        //do do do something
      }
}   
void clock_check()
{
    while (SFRIFG1 & OFIFG);        // 监测振荡器故障标志
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 的 fault flags
        SFRIFG1 &= ~OFIFG;         // 清除故障标志
    }
}

void IO_Init()
{
      P1DIR |= BIT0;                // ACLK 
      P1SEL |= BIT0;
      P2DIR |= BIT2;                // SMCLK 
      P2SEL |= BIT2;
      P7DIR |= BIT7;               // MCLK 
      P7SEL |= BIT7;
}
