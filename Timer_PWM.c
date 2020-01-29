#include <msp430f5529.h>
void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;         
      P1DIR |= BIT2+BIT3;               
      P1SEL |= BIT2+BIT3;               // P1^2��P1^3���Ź���ѡΪ��ʱ�����
      
      TA0CCR0 = 512-1;                  // PWM���ڶ���
      TA0CCTL1 = OUTMOD_7;              // CCR1�Ƚ����ģʽ7����λ/��λ
      TA0CCR1 = 384;                    // CCR1 PWM ռ�ձȶ���
      // ��ģʽ��ռ�ձ� = TA0CCR1 / TA0CCR0          ��������>3/4
      
      TA0CTL = TASSEL_1 + ID_0 + MC_1 + TACLR;	
      // ����Timer_A�Ŀ��ƼĴ���TA_CTL
      //TASSEL��ѡ��ACLKʱ��Դ��ID��ѡ���Ƶ��MC��ѡ��������ģʽ��TACLR�����TAR������
      
      __bis_SR_register(LPM3_bits);    	// ����LPM3����ģʽ
}
