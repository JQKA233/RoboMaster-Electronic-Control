#include "stm32f10x.h"                  // Device header
#include "sys.h"
//#include "usart.h"		
#include "delay.h"
#include "led.h"	
#include "pstwo.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"
#include "solidmotor.h"
#include "serial.h"

s16 MWmotor1=0;
s16 MWmotor2=0;
s16 MWmotor3=0;
s16 MWmotor4=0;
const s16 K=1;
u32 glo_motorangleon;
char RE[8];
int t=0;
u8 read=1;
unsigned char SenMass[8]={'%','0','0','a','b','c','d','\0'};//数据包
unsigned char Aiming[8]={'%','1','0','a','b','c','d','\0'};
unsigned char AimingAKF[8]={'%','1','1','a','b','c','d','\0'};
float yaw=0;
float pich =0;

void Control(u32 motorangle)
{
	glo_motorangleon = motorangle*4096;
	glo_motorangleon =glo_motorangleon/360;
}
/*
ServoToCertainAngle
	brief：控制步进电机转特定角度
	prom:给定旋转角度，给定旋转方向0正转，非零反转
*/
void ServoToCertainAngle(u32 SEVO_Angle,u8 SEVO_Dir,u8 Typ){
	Control(SEVO_Angle);
	if(Typ==1)
	{
		if(SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				SOLID1_MotorDrive_Reverse();
				delay_us(2000);//保证电机不失步
			}
			SOLID1_MotorDrive_Off();
		}
		if(!SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				SOLID1_MotorDrive_Foreward();
				delay_us(2000);//保证电机不失步
			}
			SOLID1_MotorDrive_Off();
		}
	}
	if(Typ==2){
		if(SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				SOLID2_MotorDrive_Reverse();
				delay_us(2000);//保证电机不失步
			}
			SOLID2_MotorDrive_Off();
		}
		if(!SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				SOLID2_MotorDrive_Foreward();
				delay_us(2000);//保证电机不失步
			}
			SOLID2_MotorDrive_Off();
		}
	}
	if(Typ==4){
		if(SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				MIX_MotorDrive_Reverse();
				delay_us(2000);//保证电机不失步
			}
			MIX_MotorDrive_Off();
		}
		if(!SEVO_Dir)
		{
			for(u32 i = 0;i <= glo_motorangleon;i++)
			{
				MIX_MotorDrive_Foreward();
				delay_us(2000);//保证电机不失步
			}
			MIX_MotorDrive_Off();
		}
	}
	
}

void MecanumWheel(s16 speedx,s16 speedy,s16 omega){
	MWmotor1=speedx-speedy-K*omega;
	MWmotor2=speedx+speedy-K*omega;
	MWmotor3=speedx-speedy+K*omega;
	MWmotor4=speedx+speedy+K*omega;
}

int main(void)
{								    
	Stm32_Clock_Init(9);
	delay_init(72);
	//uart_init(72,9600);
	//TIM3_PWM_Init(900,0);

	LED_Init();
	PS2_Init();
	M_Init();
	SOLIDMOTOR_Init();
	u8 key;
	while(1)
	{
		delay_ms(50);	 //很重要不可以删除
		LED = !LED;
		key = PS2_DataKey();	 //手柄按键捕获处理
		if(key!=0){
			if(key == PSB_R2||key == PSB_R1){//fire
				ServoToCertainAngle(30,1,2);
			}
			if(key == PSB_PAD_UP) MecanumWheel(500,0,0);
			if(key == PSB_PAD_DOWN) MecanumWheel(-500,0,0);
			if(key == PSB_PAD_RIGHT) MecanumWheel(0,500,0);
			if(key == PSB_PAD_LEFT) MecanumWheel(0,-500,0);
			if(key == PSB_PINK) MecanumWheel(0,0,500);
			if(key == PSB_RED) MecanumWheel(0,0,-500);
			if(key == PSB_GREEN) {
				for(u8 i=0;i<10;i++){
					MIX_MotorDrive_Foreward();
					delay_us(2000);
				}
			}
			if(key == PSB_BLUE){
				for(u8 i=0;i<10;i++){
					MIX_MotorDrive_Reverse();
					delay_us(2000);
				}
			}
			if(key == PSB_L3) Usart_SendString(USART1, SenMass, 7);
		}
		if(read==0){
			for(u8 i=0;i<8;i++){
				if(RE[i]=='@') yaw = RE[i+1]*10+RE[i+2]+RE[i+3]*0.1+RE[i+4]*0.01;
				if(RE[i]=='!') pich = RE[i+1]*10+RE[i+2]+RE[i+3]*0.1+RE[i+4]*0.01;
			}
			if(yaw>0)
				ServoToCertainAngle(yaw,1,4);
			if(yaw<0)
				ServoToCertainAngle(-yaw,0,4);
			if(pich>0)
				ServoToCertainAngle(pich,1,1);
			if(pich<0)
				ServoToCertainAngle(-pich,0,1);
		}
	}	 
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
	{ 
		RE[t]=USART_ReceiveData(USART1);//读取接收到的数据
		t++;
		if(t>=7){ t=0;read=0;}
	}
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
}
