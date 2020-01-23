#include <msp430f5529.h>
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;    

	P1DIR |= BIT0;               // 启用第二功能 ACLK 
	P1SEL |= BIT0;
        
	P2DIR |= BIT2;               // 启用第二功能 SMCLK 
	P2SEL |= BIT2;
        
	P7DIR |= BIT7;               // 启用第二功能 MCLK 
	P7SEL |= BIT7;

	P5SEL |= BIT2+BIT3;          // 启用第二功能 XT2 IN/OUT
        
	UCSCTL6 &= ~(XT1OFF + XT2OFF);  // 配置UCSTRL 使能XT1 & XT2 
        
	UCSCTL6 |= XCAP_3;           // 配置负载电容
        
// 循环直到XT1 ,XT2 & DCO 的故障标志被清除
    do
    {
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);     // 清除 XT2,低频XT1,DCO 的 故障标志 （fault flags）
    	
        SFRIFG1 &= ~OFIFG;       // 清除故障标志
        
    }while (SFRIFG1 & OFIFG);      // 监测振荡器故障标志

    UCSCTL6 &= ~XT2DRIVE0;       // 降低XT2 振荡器的工作频率，减少电流消耗
    
    UCSCTL4 |= SELA_0 + SELS_5;  // 选择 SMCLK, ACLK的时钟源 
 }
