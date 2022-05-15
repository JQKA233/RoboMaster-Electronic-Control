#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
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
	         
			 ��ǰ�����Ҳ࿴�������˳ʱ�뷽��ת��
	         ��󣺴��Ҳ࿴���������ʱ�뷽��ת��	  
***********************************************************/

#define M1_1 PAout(0)
#define M1_2 PAout(1)
#define M2_1 PAout(2)
#define M2_2 PAout(3)
#define M3_1 PAout(4)
#define M3_2 PAout(5)
#define M4_1 PAout(6)
#define M4_2 PAout(7)


void M_Init(void);	   //�����ת��������źŶ˿ڳ�ʼ��

void TIM3_PWM_Init(u16 arr,u16 psc); //arr�趨�������Զ���װֵ,pscԤ��Ƶ������Ƶ,psc=0

void Motor_Speed_Control(s16 motor1, s16 motor2, s16 motor3, s16 motor4);  //���ҵ���������ٶȿ���	

#endif