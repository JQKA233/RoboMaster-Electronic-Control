#ifndef __SOLIDMOTOR_H
#define __SOLIDMOTOR_H	 
#include "stm32f10x.h"                  // Device header
#include "sys.h"

#define SOLIDMOTOR1_A_IN    PBout(8)	//use sys.h	
#define SOLIDMOTOR1_B_IN    PBout(9)	//pich
#define SOLIDMOTOR1_C_IN    PBout(10)	
#define SOLIDMOTOR1_D_IN    PBout(11)	

#define SOLIDMOTOR2_A_IN    PBout(0)		//fire
#define SOLIDMOTOR2_B_IN    PBout(1)	
#define SOLIDMOTOR2_C_IN    PAout(11)	
#define SOLIDMOTOR2_D_IN    PAout(12)

#define SOLIDMOTOR3_A_IN    PCout(12)		
#define SOLIDMOTOR3_B_IN    PCout(11)	
#define SOLIDMOTOR3_C_IN    PCout(10)	
#define SOLIDMOTOR3_D_IN    PAout(9)

#define SOLIDMOTOR4_A_IN    PBout(5)		//MIXyaw
#define SOLIDMOTOR4_B_IN    PBout(6)	
#define SOLIDMOTOR4_C_IN    PBout(7)	
#define SOLIDMOTOR4_D_IN    PAout(8)

/*
brief:��ʼ���������
*/
void SOLIDMOTOR_Init(void);	
//�ѱ�void Control(u32 motorangle);����
void SOLIDMOTOR_Control(u8 motronumber,u8 motordirection,u32 motorangle);
void MIX_MotorDrive_Foreward(void);//MIX�����˶�
void MIX_MotorDrive_Reverse(void);//MIX�����˶�
void MIX_MotorDrive_Off(void);//MIX�ػ�
void SOLID1_MotorDrive_Foreward(void);//SOLID1�����˶�
void SOLID1_MotorDrive_Reverse(void);//SOLID1�����˶�
void SOLID1_MotorDrive_Off(void);//SOLID1�ػ�
void SOLID2_MotorDrive_Foreward(void);//SOLID2�����˶�
void SOLID2_MotorDrive_Reverse(void);//SOLID2�����˶�
void SOLID2_MotorDrive_Off(void);//SOLID2�ػ�
void Control(u32 motorangle);
/*
ServoToCertainAngle
	brief�����Ʋ������ת�ض��Ƕ�
	prom:������ת�Ƕȣ�������ת����0��ת�����㷴ת
*/
void ServoToCertainAngle(u32 SEVO_Angle,u8 SEVO_Dir,u8 Typ);

#endif

