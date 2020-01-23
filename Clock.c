#include <msp430f5529.h>
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;    

	P1DIR |= BIT0;               // ���õڶ����� ACLK 
	P1SEL |= BIT0;
        
	P2DIR |= BIT2;               // ���õڶ����� SMCLK 
	P2SEL |= BIT2;
        
	P7DIR |= BIT7;               // ���õڶ����� MCLK 
	P7SEL |= BIT7;

	P5SEL |= BIT2+BIT3;          // ���õڶ����� XT2 IN/OUT
        
	UCSCTL6 &= ~(XT1OFF + XT2OFF);  // ����UCSTRL ʹ��XT1 & XT2 
        
	UCSCTL6 |= XCAP_3;           // ���ø��ص���
        
// ѭ��ֱ��XT1 ,XT2 & DCO �Ĺ��ϱ�־�����
    do
    {
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);     // ��� XT2,��ƵXT1,DCO �� ���ϱ�־ ��fault flags��
    	
        SFRIFG1 &= ~OFIFG;       // ������ϱ�־
        
    }while (SFRIFG1 & OFIFG);      // ����������ϱ�־

    UCSCTL6 &= ~XT2DRIVE0;       // ����XT2 �����Ĺ���Ƶ�ʣ����ٵ�������
    
    UCSCTL4 |= SELA_0 + SELS_5;  // ѡ�� SMCLK, ACLK��ʱ��Դ 
 }
