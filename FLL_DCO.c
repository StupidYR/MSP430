#include <msp430f5529.h>
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;     
	P1DIR |= BIT0;                // ACLK 
	P1SEL |= BIT0;
	P2DIR |= BIT2;                // SMCLK 
	P2SEL |= BIT2;
        P7DIR |= BIT7;               // MCLK 
	P7SEL |= BIT7;

	UCSCTL6 &= ~(XT1OFF);         // 使能 XT1
	UCSCTL6 |= XCAP_3;            // 配置负载电容
        
        UCSCTL3 = SELREF_2;           // 选择REFO来作为FLL的参考时钟源
        
// 检测时钟源是否稳定
    do
    {
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 的 fault flags
                                 
    	SFRIFG1 &= ~OFIFG;        // 清除故障标志
    }while (SFRIFG1 & OFIFG);       // 监测振荡器故障标志

// 配置DCO的频率为 2.45MHz
    
    __bis_SR_register(SCG0);      // 关闭FLL控制；   如果不关闭的话，FLL寄存器不会改变
    UCSCTL0 = 0x0000;             // 配置 DCOx = 0 , MODx = 0  ；
    UCSCTL1 = DCORSEL_3;          // 配置DCO的频率范围 1.51————6.07 
    
    //  f_DCO(n, 0)_MAX ≤ f_DCO ≤ f_DCO(n, 31)_MIN
    // 范围参见数据手册 DCO Frequency
    
    UCSCTL2 = FLLD_1 + 74;        // 配置FLL_D：二分频    配置FLL_N：74
    
    // (N + 1) * FLLRef = Fdco
    // (74 + 1) * 32768 = 2.45MHz
    
    __bic_SR_register(SCG0);      // 开启FLL控制
    
    // 32 x 32 x Fdco / f_FLL_reference = waitting_time
    // 32 x 32 x 2.45 MHz / 32.768 Hz = 76563 ---->  MCLK cycles for DCO to settle
    __delay_cycles(76563);
    
// 检测时钟源是否稳定
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + 0x0004 + DCOFFG); // 清除 XT2,XT1,DCO 的 fault flags
        SFRIFG1 &= ~OFIFG;         // 清除故障标志
    }while (SFRIFG1 & OFIFG);        // 监测振荡器故障标志

    while(1);                      // Loop in place
}
