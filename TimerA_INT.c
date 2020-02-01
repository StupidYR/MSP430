#include <msp430f5529.h>

void clock_check();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    
    P1DIR |= BIT0;      
    P1OUT &= ~BIT0;      //P1.0�˿����ģʽ
    
    TA0CCR0 = 62500;    //SMCLK -->DCOCLKDIV��1.048576MHZ�� ; 
                       //��ʱ����500ms�� 62500 = 500ms / (1 /��f_SMCLK / ID��) 
                       // TA0CCR0 ���ֵΪ 0xFF��65535��
    
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR + TAIE;
                      //SMCLK��Ϊʱ��Դ��ID��8��Ƶ����ģʽ�����TAR��������TAIFG�ж�ʹ��
    
    clock_check();      //���ʱ��Դ�Ƿ��ȶ�
    
    _EINT();    //�������ж�
}

#pragma vector=TIMER0_A1_VECTOR        //TIMER0_A1����CCR1��CCR2�� TAIFG �ж�
                                       //TIMER0_A0������CCR0
__interrupt void TIMER0_A1(void)       //����һ������TIMER0_A1���жϺ���
{
    TA0CTL &= ~TAIFG;   //����жϱ�־λ
    P1OUT ^= BIT0;      //LED��˸
}
void clock_check()
{
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
      SFRIFG1 &= ~OFIFG;        
    }while (SFRIFG1 & OFIFG);     
}