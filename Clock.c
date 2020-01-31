/*****************Clock********************
            上电时的默认状态

MCLK：主系统时钟；DCOCLKDIV

SMCLK：子系统时钟；DCOCLKDIV

ACLK：辅助系统时钟；XT1（若XT1无效，则为REFO；其他情况切换为DCO）

系统稳定后，DCOCLK默认为 2.097152MHZ，
FLL默认2分频，则MCLK和SMCLK的频率都为1.048576MHZ。

此外FLL默认参照源为XT1

如果连接XT1和XT2的引脚不进行PxSEL的设置，那么这两个时钟源都是无效的；

REFOCLK、VLOCLK、DCOCLK默认状态下是可用的；


*******************END**********************/
#include <msp430f5529.h>

void clock_check();

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
    UCSCTL6 &= ~(XT1OFF + XT2OFF);  // 使能XT1 & XT2 
    UCSCTL6 |= XCAP_3;           // 配置负载电容
        
    clock_check();

    UCSCTL6 &= ~XT2DRIVE0;       // 降低XT2 振荡器的工作频率，减少电流消耗
    UCSCTL4 |= SELA_0 + SELS_5;  // 选择 SMCLK, ACLK的时钟源 
    
    while(1)
    {
        //do do do something
    }
 }
void clock_check()
{
    while (SFRIFG1 & OFIFG)     // 监测振荡器故障标志
    {
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);     // 清除 XT2,低频XT1,DCO 的故障标志 （fault flags）
    	
        SFRIFG1 &= ~OFIFG;       // 清除故障标志 
    }
}

