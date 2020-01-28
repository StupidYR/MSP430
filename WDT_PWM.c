#include <msp430f5529.h>
void main(void)
{
	WDTCTL = WDTPW + WDTCNTCL + WDTSSEL1 + WDTIS_4;
        //WDTCTL：看门狗控制寄存器：16位
        //WDTPW：写入命令时，高八位固定为 0x5A（WDTPW）
        //WDTCNTCL：看门狗计时器清零
	//WDTSSEL1：选择ACLK（32.768 KHZ）作为参考时钟
        //WDTIS_4：间隔时间选择 （go to definition查看）
        //定时时间 = 参考时钟源周期 / 间隔时间 
        
	P1DIR |= BIT0;      // 设置P1.0端口为输出
	P1OUT ^= BIT0;      // 反转P1.0端口状态（与 1 异或）
        
	__bis_SR_register(LPM3_bits + GIE);	// 进入低功耗模式3，并启用中断
}

