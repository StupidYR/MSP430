#include <msp430f5529.h>
void main(void)
{
	WDTCTL = WDTPW + WDTCNTCL + WDTSSEL1 + WDTIS_4;
        //WDTCTL�����Ź����ƼĴ�����16λ
        //WDTPW��д������ʱ���߰�λ�̶�Ϊ 0x5A��WDTPW��
        //WDTCNTCL�����Ź���ʱ������
	//WDTSSEL1��ѡ��ACLK��32.768 KHZ����Ϊ�ο�ʱ��
        //WDTIS_4�����ʱ��ѡ�� ��go to definition�鿴��
        //��ʱʱ�� = �ο�ʱ��Դ���� / ���ʱ�� 
        
	P1DIR |= BIT0;      // ����P1.0�˿�Ϊ���
	P1OUT ^= BIT0;      // ��תP1.0�˿�״̬���� 1 ���
        
	__bis_SR_register(LPM3_bits + GIE);	// ����͹���ģʽ3���������ж�
}

