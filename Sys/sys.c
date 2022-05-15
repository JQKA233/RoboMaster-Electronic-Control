#include "stm32f10x.h"                  // Device header	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//???????????????��????????????????????????��????
//Mini STM32??????
//?????????		   
//???????@ALIENTEK
//???????:www.openedv.com
//???????:2010/5/27
//?��??V1.4
//??????��?????????
//Copyright(C) ??????? 2009-2019
//All rights reserved
//********************************************************************************
//V1.4??????
//??NVIC KO??,???????�ʦ�????!
//??????JTAG_Set????
////////////////////////////////////////////////////////////////////////////////// 	  

//???????????????
//NVIC_VectTab:???
//Offset:?????
//CHECK OK
//091207
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 
  	//???????????
	assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
	assert_param(IS_NVIC_OFFSET(Offset));  	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//????NVIC???????????????
	//????????????????CODE????????RAM??
}
//????NVIC????
//NVIC_Group:NVIC???? 0~4 ???5?? 
//CHECK OK
//091209
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//?????��
	temp1<<=8;
	temp=SCB->AIRCR;  //????????????
	temp&=0X0000F8FF; //??????????
	temp|=0X05FA0000; //��?????
	temp|=temp1;	   
	SCB->AIRCR=temp;  //???��???	    	  				   
}
//????NVIC 
//NVIC_PreemptionPriority:????????
//NVIC_SubPriority       :????????
//NVIC_Channel           :?��???
//NVIC_Group             :?��???? 0~4
//????????????????څ??????��!??????????????????
//?�l??:
//??0:0��????????,4��????????
//??1:1��????????,3��????????
//??2:2��????????,2��????????
//??3:3��????????,1��????????
//??4:4��????????,0��????????
//NVIC_SubPriority??NVIC_PreemptionPriority???????,????��,?????
//CHECK OK
//100329
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	u8 IPRADDR=NVIC_Channel/4;  //???????4??,??????? 
	u8 IPROFFSET=NVIC_Channel%4;//??????????
	IPROFFSET=IPROFFSET*8+4;    //??????????��??
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//???��???
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//?????��

	if(NVIC_Channel<32)NVIC->ISER[0]|=1<<NVIC_Channel;//????��?��(???????,????????OK)
	else NVIC->ISER[1]|=1<<(NVIC_Channel-32);    
	NVIC->IP[IPRADDR]|=temp<<IPROFFSET;//???????????????????????   	
}

//???��????��???
//????GPIOA~G;??????PVD,RTC??USB??????????
//????:GPIOx:0~6,????GPIOA~G;BITx:???????��;TRIM:??????,1,??????;2,?????;3????????????
//?��?????????????1??IO??,???IO??,???��???
//?��????????????????��?,?????????   
//??????...
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM) 
{
	u8 EXTADDR;
	u8 EXTOFFSET;
	EXTADDR=BITx/4;//????��??????????
	EXTOFFSET=(BITx%4)*4;

	RCC->APB2ENR|=0x01;//???io???????

	AFIO->EXTICR[EXTADDR]&=~(0x000F<<EXTOFFSET);//???????????????
	AFIO->EXTICR[EXTADDR]|=GPIOx<<EXTOFFSET;//EXTI.BITx???GPIOx.BITx
	
	//???????
	EXTI->IMR|=1<<BITx;//  ????line BITx????��?
	//EXTI->EMR|=1<<BITx;//??????line BITx?????? (????????????,?????????????,??????????????????????????��?!)
 	if(TRIM&0x01)EXTI->FTSR|=1<<BITx;//line BITx?????????????
	if(TRIM&0x02)EXTI->RTSR|=1<<BITx;//line BITx????????????????
} 


//????????????????????�x��!??????????????????.		    
//???????????????��
//CHECK OK
//091209
void MYRCC_DeInit(void)
{										  					   
	RCC->APB1RSTR = 0x00000000;//??��????			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR = 0x00000014;  //??????????SRAM??????.???????.	  
  	RCC->APB2ENR = 0x00000000; //?????????.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //?????????????HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //??��SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //??��HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //??��HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //??��PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //????????��?
	//??????????				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else   
	MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}
//THUMB????????????
//???????��????????��?????WFI
//CHECK OK
//091209
__asm void WFI_SET(void)
{
	WFI;    
}
//?????????	 
//check ok 
//091202
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//???SLEEPDEEP�� (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //????????	    
 	PWR->CSR|=1<<8;          //????WKUP???????
	PWR->CR|=1<<2;           //???Wake-up ???
	PWR->CR|=1<<1;           //PDDS??��		  
	WFI_SET();				 //???WFI???		 
}	  
//??????��?????
//reg:????????
//reg:?��?????? 
////check ok
////091202
//void BKP_Write(u8 reg,u16 dat)
//{
//  RCC->APB1ENR|=1<<28;     //????????	    
//	RCC->APB1ENR|=1<<27;     //?????????	    
//	PWR->CR|=1<<8;           //?????????��???? 
//	switch(reg)
//	{
//		case 1:
//			BKP->DR1=dat;
//			break;
//		case 2:
//			BKP->DR2=dat;
//			break;
//		case 3:
//			BKP->DR3=dat;
//			break; 
//		case 4:
//			BKP->DR4=dat;
//			break;
//		case 5:
//			BKP->DR5=dat;
//			break;
//		case 6:
//			BKP->DR6=dat;
//			break;
//		case 7:
//			BKP->DR7=dat;
//			break;
//		case 8:
//			BKP->DR8=dat;
//			break;
//		case 9:
//			BKP->DR9=dat;
//			break;
//		case 10:
//			BKP->DR10=dat;
//			break;
//	} 
//}	    
//??????��
//CHECK OK
//091209
void Sys_Soft_Reset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 

//JTAG??????,????????JTAG????
//mode:jtag,swd??????;00,????;01,???SWD;10,????;
//CHECK OK	
//100818		  
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //???????????	   
	AFIO->MAPR&=0XF8FFFFFF; //???MAPR??[26:24]
	AFIO->MAPR|=temp;       //????jtag??
} 
//?????????????
//pll:????????????2??????????16	
//CHECK OK
//091209
void Stm32_Clock_Init(u8 PLL)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  //??��????????????
	RCC->CR|=0x00010000;  //????????????HSEON
	while(!(RCC->CR>>17));//???????????
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//????2????��
	RCC->CFGR|=PLL<<18;   //????PLL? 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2?????????

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//???PLL????
	RCC->CFGR|=0x00000002;//PLL????????	 
	while(temp!=0x02)     //???PLL???????????��??
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    




























