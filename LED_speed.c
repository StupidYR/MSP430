#include<msp430f5529.h>
int flag=1;
void choose_delay();
void LED();
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
    P8DIR |= BIT1 + BIT2;
    P8OUT &= ~(BIT1 + BIT2);    //��ʼ��LED��I/O��
    
    P1DIR &= ~BIT7;     //����P1^7��Ϊ����״̬
    P1OUT |= BIT7;      //�Ϻ�·
    P1REN |= BIT7;      //��P1^7�ڽ���������
    P1IE |= BIT7;       //�ж�ʹ��
    P1IFG &= ~BIT7;     //����жϱ�־λ
    P1IES |= BIT7;      //��1�������½��ش���
    __enable_interrupt();       //���ж�ʹ��
    
    while(1)
      LED();    //LED��˸����
}

#pragma vector = PORT1_VECTOR   //P1ϵ�ж˿ڵ����жϺ���
__interrupt void port_1(void)   //����һ����Ϊport_1���жϺ���
{
  if(P1IFG & BIT7)      //�ж��Ƿ�ΪP1^7�ڲ����ж�
  {
    
    while((P1IN & BIT7)==0);      //�ȴ������ͷ�
    flag=~flag;
    
  }
  P1IFG &= ~BIT7;       //����жϱ�־λ
}

void choose_delay()
{
   if(flag==0)
    __delay_cycles(100000);
  else
    __delay_cycles(200000);
}
void LED()
{
  P1OUT |= BIT0;
  P1OUT &= ~BIT5;
  choose_delay();
  
  P8OUT |= BIT1;
  P1OUT &= ~BIT0;
  choose_delay();
  
  P8OUT |= BIT2;
  P8OUT &= ~BIT1; 
  choose_delay();
  
  P1OUT |= BIT1;
  P8OUT &= ~BIT2;
  choose_delay();
  
  P1OUT |= BIT2;
  P1OUT &= ~BIT1;
  choose_delay();
  
  P1OUT |= BIT3;
  P1OUT &= ~BIT2;
  choose_delay();
  
  P1OUT |= BIT4;
  P1OUT &= ~BIT3; 
  choose_delay();
  
  P1OUT |= BIT5;
  P1OUT &= ~BIT4;
  choose_delay();
}