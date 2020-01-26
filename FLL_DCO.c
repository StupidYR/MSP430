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

	UCSCTL6 &= ~(XT1OFF);         // ʹ�� XT1
	UCSCTL6 |= XCAP_3;            // ���ø��ص���
        
        UCSCTL3 = SELREF_2;           // ѡ��REFO����ΪFLL�Ĳο�ʱ��Դ
        
// ���ʱ��Դ�Ƿ��ȶ�
    do
    {
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // ��� XT2,XT1,DCO �� fault flags
                                 
    	SFRIFG1 &= ~OFIFG;        // ������ϱ�־
    }while (SFRIFG1 & OFIFG);       // ����������ϱ�־

// ����DCO��Ƶ��Ϊ 2.45MHz
    
    __bis_SR_register(SCG0);      // �ر�FLL���ƣ�   ������رյĻ���FLL�Ĵ�������ı�
    UCSCTL0 = 0x0000;             // ���� DCOx = 0 , MODx = 0  ��
    UCSCTL1 = DCORSEL_3;          // ����DCO��Ƶ�ʷ�Χ 1.51��������6.07 
    
    //  f_DCO(n, 0)_MAX �� f_DCO �� f_DCO(n, 31)_MIN
    // ��Χ�μ������ֲ� DCO Frequency
    
    UCSCTL2 = FLLD_1 + 74;        // ����FLL_D������Ƶ    ����FLL_N��74
    
    // (N + 1) * FLLRef = Fdco
    // (74 + 1) * 32768 = 2.45MHz
    
    __bic_SR_register(SCG0);      // ����FLL����
    
    // 32 x 32 x Fdco / f_FLL_reference = waitting_time
    // 32 x 32 x 2.45 MHz / 32.768 Hz = 76563 ---->  MCLK cycles for DCO to settle
    __delay_cycles(76563);
    
// ���ʱ��Դ�Ƿ��ȶ�
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + 0x0004 + DCOFFG); // ��� XT2,XT1,DCO �� fault flags
        SFRIFG1 &= ~OFIFG;         // ������ϱ�־
    }while (SFRIFG1 & OFIFG);        // ����������ϱ�־

    while(1);                      // Loop in place
}
