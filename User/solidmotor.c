#include "stm32f10x.h"                  // Device header
#include "solidmotor.h"
#include "delay.h"//小写delay不一定好用
   
char table1[]={0x03,0x06,0x0c,0x09}; 
char table2[]={0x03,0x09,0x0c,0x06}; 
//u32 glo_motorangleon;已在头文件中声明


void SOLIDMOTOR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);	 //??GPIOB????

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;				 //BEEP-->PB.8 ????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //???50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 //???????GPIOE.11
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);//??0,???????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11  ;				 //BEEP-->PB.8 ????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //???50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //???????GPIOE.11
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11);
}

//void SOLIDMOTOR_Control(u8 motronumber,u8 motordirection,u32 motorangle)
//{
//	glo_motorangleon = motorangle*4096;
//	glo_motorangleon =glo_motorangleon/360;
//}
void MIX_MotorDrive_Foreward(void)
{
	static u8 j=0;
	if(j==0)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==1)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==2)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==3)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 0;					
	}
	else if(j==4)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 0;					
	}
	else if(j==5)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 1;					
	}
	else if(j==6)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 1;					
	}
	else if(j==7)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 1;					
	}
	j++;
	if(j>7) j=0;
}
void MIX_MotorDrive_Reverse(void)
{
	static u8 j=0;
	if(j==7)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==6)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==5)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 0;
	}
	else if(j==4)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 1;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 0;					
	}
	else if(j==3)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 0;					
	}
	else if(j==2)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 1;
		SOLIDMOTOR4_D_IN = 1;					
	}
	else if(j==1)
	{
		SOLIDMOTOR4_A_IN = 0;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 1;					
	}
	else if(j==0)
	{
		SOLIDMOTOR4_A_IN = 1;
		SOLIDMOTOR4_B_IN = 0;
		SOLIDMOTOR4_C_IN = 0;
		SOLIDMOTOR4_D_IN = 1;					
	}
	j++;
	if(j>7) j=0;
}
void MIX_MotorDrive_Off(void)
{
	SOLIDMOTOR4_A_IN = 0;
	SOLIDMOTOR4_B_IN = 0;
	SOLIDMOTOR4_C_IN = 0;
	SOLIDMOTOR4_D_IN = 0;
}
//void SOLID1_MotorDrive_Foreward(void)
//{
//	static u8 j=0;
//	if(j==0)
//	{
//		SOLIDMOTOR1_A_IN = 1;
//		SOLIDMOTOR1_B_IN = 0;
//		SOLIDMOTOR1_C_IN = 0;
//		SOLIDMOTOR1_D_IN = 0;
//	}
//	else if(j==1)
//	{
//		SOLIDMOTOR1_A_IN = 1;
//		SOLIDMOTOR1_B_IN = 1;
//		SOLIDMOTOR1_C_IN = 0;
//		SOLIDMOTOR1_D_IN = 0;
//	}
//	else if(j==2)
//	{
//		SOLIDMOTOR1_A_IN = 0;
//		SOLIDMOTOR1_B_IN = 1;
//		SOLIDMOTOR1_C_IN = 0;
//		SOLIDMOTOR1_D_IN = 0;
//	}
//	else if(j==3)
//	{
//		SOLIDMOTOR1_A_IN = 0;
//		SOLIDMOTOR1_B_IN = 1;
//		SOLIDMOTOR1_C_IN = 1;
//		SOLIDMOTOR1_D_IN = 0;					
//	}
//	else if(j==4)
//	{
//		SOLIDMOTOR1_A_IN = 0;
//		SOLIDMOTOR1_B_IN = 0;
//		SOLIDMOTOR1_C_IN = 1;
//		SOLIDMOTOR1_D_IN = 0;					
//	}
//	else if(j==5)
//	{
//		SOLIDMOTOR1_A_IN = 0;
//		SOLIDMOTOR1_B_IN = 0;
//		SOLIDMOTOR1_C_IN = 1;
//		SOLIDMOTOR1_D_IN = 1;					
//	}
//	else if(j==6)
//	{
//		SOLIDMOTOR1_A_IN = 0;
//		SOLIDMOTOR1_B_IN = 0;
//		SOLIDMOTOR1_C_IN = 0;
//		SOLIDMOTOR1_D_IN = 1;					
//	}
//	else if(j==7)
//	{
//		SOLIDMOTOR1_A_IN = 1;
//		SOLIDMOTOR1_B_IN = 0;
//		SOLIDMOTOR1_C_IN = 0;
//		SOLIDMOTOR1_D_IN = 1;					
//	}
//	j++;
//	if(j>7) j=0;
//}
void SOLID1_MotorDrive_Foreward(void)
{//????1????
	static u8 j=0;
	if(j==0)
				{
					SOLIDMOTOR1_A_IN = 0;
					SOLIDMOTOR1_B_IN = 1;
					SOLIDMOTOR1_C_IN = 1;
					SOLIDMOTOR1_D_IN = 1;
				}
				else if(j==1)
				{
					SOLIDMOTOR1_A_IN = 0;
					SOLIDMOTOR1_B_IN = 0;
					SOLIDMOTOR1_C_IN = 1;
					SOLIDMOTOR1_D_IN = 1;
				}
				else if(j==2)
				{
					SOLIDMOTOR1_A_IN = 1;
					SOLIDMOTOR1_B_IN = 0;
					SOLIDMOTOR1_C_IN = 1;
					SOLIDMOTOR1_D_IN = 1;
				}
				else if(j==3)
				{
					SOLIDMOTOR1_A_IN = 1;
					SOLIDMOTOR1_B_IN = 0;
					SOLIDMOTOR1_C_IN = 0;
					SOLIDMOTOR1_D_IN = 1;					
				}
				else if(j==4)
				{
					SOLIDMOTOR1_A_IN = 1;
					SOLIDMOTOR1_B_IN = 1;
					SOLIDMOTOR1_C_IN = 0;
					SOLIDMOTOR1_D_IN = 1;					
				}
				else if(j==5)
				{
					SOLIDMOTOR1_A_IN = 1;
					SOLIDMOTOR1_B_IN = 1;
					SOLIDMOTOR1_C_IN = 0;
					SOLIDMOTOR1_D_IN = 0;					
				}
				else if(j==6)
				{
					SOLIDMOTOR1_A_IN = 1;
					SOLIDMOTOR1_B_IN = 1;
					SOLIDMOTOR1_C_IN = 1;
					SOLIDMOTOR1_D_IN = 0;					
				}
				else if(j==7)
				{
					SOLIDMOTOR1_A_IN = 0;
					SOLIDMOTOR1_B_IN = 1;
					SOLIDMOTOR1_C_IN = 1;
					SOLIDMOTOR1_D_IN = 0;					
				}
	j++;
	if(j>7) j=0;
}
void SOLID1_MotorDrive_Reverse(void)
{
	static u8 j=0;
	if(j==7)
	{
		SOLIDMOTOR1_A_IN = 1;
		SOLIDMOTOR1_B_IN = 0;
		SOLIDMOTOR1_C_IN = 0;
		SOLIDMOTOR1_D_IN = 0;
	}
	else if(j==6)
	{
		SOLIDMOTOR1_A_IN = 1;
		SOLIDMOTOR1_B_IN = 1;
		SOLIDMOTOR1_C_IN = 0;
		SOLIDMOTOR1_D_IN = 0;
	}
	else if(j==5)
	{
		SOLIDMOTOR1_A_IN = 0;
		SOLIDMOTOR1_B_IN = 1;
		SOLIDMOTOR1_C_IN = 0;
		SOLIDMOTOR1_D_IN = 0;
	}
	else if(j==4)
	{
		SOLIDMOTOR1_A_IN = 0;
		SOLIDMOTOR1_B_IN = 1;
		SOLIDMOTOR1_C_IN = 1;
		SOLIDMOTOR1_D_IN = 0;					
	}
	else if(j==3)
	{
		SOLIDMOTOR1_A_IN = 0;
		SOLIDMOTOR1_B_IN = 0;
		SOLIDMOTOR1_C_IN = 1;
		SOLIDMOTOR1_D_IN = 0;					
	}
	else if(j==2)
	{
		SOLIDMOTOR1_A_IN = 0;
		SOLIDMOTOR1_B_IN = 0;
		SOLIDMOTOR1_C_IN = 1;
		SOLIDMOTOR1_D_IN = 1;					
	}
	else if(j==1)
	{
		SOLIDMOTOR1_A_IN = 0;
		SOLIDMOTOR1_B_IN = 0;
		SOLIDMOTOR1_C_IN = 0;
		SOLIDMOTOR1_D_IN = 1;					
	}
	else if(j==0)
	{
		SOLIDMOTOR1_A_IN = 1;
		SOLIDMOTOR1_B_IN = 0;
		SOLIDMOTOR1_C_IN = 0;
		SOLIDMOTOR1_D_IN = 1;					
	}
	j++;
	if(j>7) j=0;
}
void SOLID1_MotorDrive_Off(void)
{
	SOLIDMOTOR1_A_IN = 0;
	SOLIDMOTOR1_B_IN = 0;
	SOLIDMOTOR1_C_IN = 0;
	SOLIDMOTOR1_D_IN = 0;
}
void SOLID2_MotorDrive_Foreward(void)
{//????1????
	static u8 j=0;
	if(j==0)
				{
					SOLIDMOTOR2_A_IN = 0;
					SOLIDMOTOR2_B_IN = 1;
					SOLIDMOTOR2_C_IN = 1;
					SOLIDMOTOR2_D_IN = 1;
				}
				else if(j==1)
				{
					SOLIDMOTOR2_A_IN = 0;
					SOLIDMOTOR2_B_IN = 0;
					SOLIDMOTOR2_C_IN = 1;
					SOLIDMOTOR2_D_IN = 1;
				}
				else if(j==2)
				{
					SOLIDMOTOR2_A_IN = 1;
					SOLIDMOTOR2_B_IN = 0;
					SOLIDMOTOR2_C_IN = 1;
					SOLIDMOTOR2_D_IN = 1;
				}
				else if(j==3)
				{
					SOLIDMOTOR2_A_IN = 1;
					SOLIDMOTOR2_B_IN = 0;
					SOLIDMOTOR2_C_IN = 0;
					SOLIDMOTOR2_D_IN = 1;					
				}
				else if(j==4)
				{
					SOLIDMOTOR2_A_IN = 1;
					SOLIDMOTOR2_B_IN = 1;
					SOLIDMOTOR2_C_IN = 0;
					SOLIDMOTOR2_D_IN = 1;					
				}
				else if(j==5)
				{
					SOLIDMOTOR2_A_IN = 1;
					SOLIDMOTOR2_B_IN = 1;
					SOLIDMOTOR2_C_IN = 0;
					SOLIDMOTOR2_D_IN = 0;					
				}
				else if(j==6)
				{
					SOLIDMOTOR2_A_IN = 1;
					SOLIDMOTOR2_B_IN = 1;
					SOLIDMOTOR2_C_IN = 1;
					SOLIDMOTOR2_D_IN = 0;					
				}
				else if(j==7)
				{
					SOLIDMOTOR2_A_IN = 0;
					SOLIDMOTOR2_B_IN = 1;
					SOLIDMOTOR2_C_IN = 1;
					SOLIDMOTOR2_D_IN = 0;					
				}
	j++;
	if(j>7) j=0;
}
void SOLID2_MotorDrive_Reverse(void)
{
	static u8 j=0;
	if(j==7)
	{
		SOLIDMOTOR2_A_IN = 1;
		SOLIDMOTOR2_B_IN = 0;
		SOLIDMOTOR2_C_IN = 0;
		SOLIDMOTOR2_D_IN = 0;
	}
	else if(j==6)
	{
		SOLIDMOTOR2_A_IN = 1;
		SOLIDMOTOR2_B_IN = 1;
		SOLIDMOTOR2_C_IN = 0;
		SOLIDMOTOR2_D_IN = 0;
	}
	else if(j==5)
	{
		SOLIDMOTOR2_A_IN = 0;
		SOLIDMOTOR2_B_IN = 1;
		SOLIDMOTOR2_C_IN = 0;
		SOLIDMOTOR2_D_IN = 0;
	}
	else if(j==4)
	{
		SOLIDMOTOR2_A_IN = 0;
		SOLIDMOTOR2_B_IN = 1;
		SOLIDMOTOR2_C_IN = 1;
		SOLIDMOTOR2_D_IN = 0;					
	}
	else if(j==3)
	{
		SOLIDMOTOR2_A_IN = 0;
		SOLIDMOTOR2_B_IN = 0;
		SOLIDMOTOR2_C_IN = 1;
		SOLIDMOTOR2_D_IN = 0;					
	}
	else if(j==2)
	{
		SOLIDMOTOR2_A_IN = 0;
		SOLIDMOTOR2_B_IN = 0;
		SOLIDMOTOR2_C_IN = 1;
		SOLIDMOTOR2_D_IN = 1;					
	}
	else if(j==1)
	{
		SOLIDMOTOR2_A_IN = 0;
		SOLIDMOTOR2_B_IN = 0;
		SOLIDMOTOR2_C_IN = 0;
		SOLIDMOTOR2_D_IN = 1;					
	}
	else if(j==0)
	{
		SOLIDMOTOR2_A_IN = 1;
		SOLIDMOTOR2_B_IN = 0;
		SOLIDMOTOR2_C_IN = 0;
		SOLIDMOTOR2_D_IN = 1;					
	}
	j++;
	if(j>7) j=0;
}
void SOLID2_MotorDrive_Off(void)
{
	SOLIDMOTOR2_A_IN = 0;
	SOLIDMOTOR2_B_IN = 0;
	SOLIDMOTOR2_C_IN = 0;
	SOLIDMOTOR2_D_IN = 0;
}

