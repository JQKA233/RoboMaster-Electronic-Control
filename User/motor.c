#include "sys.h"
#include "motor.h"
/***********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：TB6612驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 TB6612FNG驱动代码
             
			 PC0~3接AIN1,AIN2,BIN1,BIN2;方向控制端口
			 PA6接PWMA;右电机（J1）速度控制
			 PA7接PWMB;左电机（J2）速度控制
             
			 371电机与电机驱动TB6612FNG连接方式			
	         右电机（J1）：黄色连AO1;橙色连接AO2
             左电机（J2）：黄色连BO1;橙色连接BO2
	         
			 向前：从右侧看，两电机顺时针方向转动  正转
	         向后：从右侧看，两电机逆时针方向转动  反转  
***********************************************************/
//电机旋转方向控制信号端口初始化
//PC0~3推挽输出，输出高
/*
	麦克纳姆轮驱动函数
*/

void M_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//RCC->APB2ENR|=1<<4;      //使能PORTC时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7);

}

//定时器TIM3，PWM控制初始化,CH1（PA6）、CH2(PA7)。
//arr：自动重装值
//psc：时钟预分频数
//设置TIM3_PWM_Init(900,0); 
//设定自动装载值为900，不分频。PWM频率=72000/900=80Khz
void TIM3_PWM_Init(u16 arr,u16 psc) //arr设定计数器自动重装值   
                                    //psc预分频器不分频,psc=0
{
	/*GPIO_InitTypeDef  GPIO_InitStructure;
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能
	  	
	GPIOA->CRL&=0X00FFFFFF;//PA6,7输出
	GPIOA->CRL|=0XBB000000;//复用功能输出 	  
	GPIOA->ODR|=3<<6;//PA6.7上拉	

	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM1模式	高电平有效	 
	TIM3->CCMR1|=1<<3; //CH1预装载使能
	TIM3->CCMR1|=6<<12;  //CH2 PWM1模式		 
	TIM3->CCMR1|=1<<11; //CH2预装载使能	   

	TIM3->CCER|=1<<0;   //OC1 输出使能
	TIM3->CCER|=1<<4;   //OC2 输出使能	   

	TIM3->CR1=0x0080;   //ARPE使能 
	TIM3->CR1|=0x01;    //使能定时器3 
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

//左右电机方向与速度控制
//motor1：右电机（J1）；motor2：左电机（J2）
//小于0时，向前，大于0时，向后    
//motor1/2的取值范围（-900~+900）；值的大小决定占空比的大小
//例motor1取值为90，则占空比为10%。

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




