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
brief:初始化步进电机
*/
void SOLIDMOTOR_Init(void);	
//已被void Control(u32 motorangle);代替
void SOLIDMOTOR_Control(u8 motronumber,u8 motordirection,u32 motorangle);
void MIX_MotorDrive_Foreward(void);//MIX正向运动
void MIX_MotorDrive_Reverse(void);//MIX反向运动
void MIX_MotorDrive_Off(void);//MIX关机
void SOLID1_MotorDrive_Foreward(void);//SOLID1正向运动
void SOLID1_MotorDrive_Reverse(void);//SOLID1反向运动
void SOLID1_MotorDrive_Off(void);//SOLID1关机
void SOLID2_MotorDrive_Foreward(void);//SOLID2正向运动
void SOLID2_MotorDrive_Reverse(void);//SOLID2反向运动
void SOLID2_MotorDrive_Off(void);//SOLID2关机
void Control(u32 motorangle);
/*
ServoToCertainAngle
	brief：控制步进电机转特定角度
	prom:给定旋转角度，给定旋转方向0正转，非零反转
*/
void ServoToCertainAngle(u32 SEVO_Angle,u8 SEVO_Dir,u8 Typ);

#endif

