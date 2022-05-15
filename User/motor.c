#include "sys.h"
#include "motor.h"
/***********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File��TB6612��������
Author��pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 TB6612FNG��������
             
			 PC0~3��AIN1,AIN2,BIN1,BIN2;������ƶ˿�
			 PA6��PWMA;�ҵ����J1���ٶȿ���
			 PA7��PWMB;������J2���ٶȿ���
             
			 371�����������TB6612FNG���ӷ�ʽ			
	         �ҵ����J1������ɫ��AO1;��ɫ����AO2
             ������J2������ɫ��BO1;��ɫ����BO2
	         
			 ��ǰ�����Ҳ࿴�������˳ʱ�뷽��ת��  ��ת
	         ��󣺴��Ҳ࿴���������ʱ�뷽��ת��  ��ת  
***********************************************************/
//�����ת��������źŶ˿ڳ�ʼ��
//PC0~3��������������
/*
	�����ķ����������
*/

void M_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//RCC->APB2ENR|=1<<4;      //ʹ��PORTCʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7);

}

//��ʱ��TIM3��PWM���Ƴ�ʼ��,CH1��PA6����CH2(PA7)��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//����TIM3_PWM_Init(900,0); 
//�趨�Զ�װ��ֵΪ900������Ƶ��PWMƵ��=72000/900=80Khz
void TIM3_PWM_Init(u16 arr,u16 psc) //arr�趨�������Զ���װֵ   
                                    //pscԤ��Ƶ������Ƶ,psc=0
{
	/*GPIO_InitTypeDef  GPIO_InitStructure;
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��
	  	
	GPIOA->CRL&=0X00FFFFFF;//PA6,7���
	GPIOA->CRL|=0XBB000000;//���ù������ 	  
	GPIOA->ODR|=3<<6;//PA6.7����	

	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1ģʽ	�ߵ�ƽ��Ч	 
	TIM3->CCMR1|=1<<3; //CH1Ԥװ��ʹ��
	TIM3->CCMR1|=6<<12;  //CH2 PWM1ģʽ		 
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   

	TIM3->CCER|=1<<0;   //OC1 ���ʹ��
	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	   

	TIM3->CR1=0x0080;   //ARPEʹ�� 
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 
	*/
	/********************
	   PB0?PB1??PWM???
	**********************/
	GPIO_InitTypeDef GPIO_InitStruct;         
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
 
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;       
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;     
	TIM_TimeBaseInitStruct.TIM_Period=arr;         
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;      
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
 
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStruct );
	TIM_OC2Init(TIM3,&TIM_OCInitStruct );
	TIM_OC3Init(TIM3,&TIM_OCInitStruct );          
	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);		
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}

//���ҵ���������ٶȿ���
//motor1���ҵ����J1����motor2��������J2��
//С��0ʱ����ǰ������0ʱ�����    
//motor1/2��ȡֵ��Χ��-900~+900����ֵ�Ĵ�С����ռ�ձȵĴ�С
//��motor1ȡֵΪ90����ռ�ձ�Ϊ10%��

void Motor_Speed_Control(s16 motor1, s16 motor2, s16 motor3, s16 motor4)	 
{
    if(motor1>0) {
		M1_1 = 1;
		M1_2 = 0;
	}
	else
		if(motor1<0){
			M1_1 = 0;
			M1_2 = 1;
		}
		else
			if(motor1 == 0){
				M1_1 = 1;
				M1_2 = 1;
			}
	if(motor2>0) {
		M2_1 = 1;
		M2_2 = 0;
	}
	else
		if(motor2<0){
			M2_1 = 0;
			M2_2 = 1;
		}
		else
			if(motor2 == 0){
				M2_1 = 1;
				M2_2 = 1;
			}
	if(motor3>0) {
		M3_1 = 1;
		M3_2 = 0;
	}
	else
		if(motor3<0){
			M3_1 = 0;
			M3_2 = 1;
		}
		else
			if(motor3 == 0){
				M3_1 = 1;
				M3_2 = 1;
			}
	if(motor4>0) {
		M4_1 = 1;
		M4_2 = 0;
	}
	else
		if(motor4<0){
			M4_1 = 0;
			M4_2 = 1;
		}
		else
			if(motor4 == 0){
				M4_1 = 1;
				M4_2 = 1;
			}
}




