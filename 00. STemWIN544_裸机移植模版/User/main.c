/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   STemWIN �������ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*******************************************************************************
 * ������ͷ�ļ�
 ******************************************************************************/
/* ������Ӳ��bspͷ�ļ� */
#include "./led/bsp_led.h" 
#include "./beep/bsp_beep.h" 
#include "./usart/bsp_debug_usart.h"
#include "./TouchPad/bsp_touchpad.h"
#include "./lcd/bsp_lcd.h"
#include "./touch/bsp_i2c_touch.h"
#include "./touch/gt9xx.h"
#include "./key/bsp_key.h"
#include "./sdram/bsp_sdram.h"
#include "./systick/bsp_Systick.h"
/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"
#include "ScreenShot.h"
#include "MainTask.h"

 /*
 *************************************************************************
 *                             ȫ�ֱ�������
 *************************************************************************
 */
KEY Key1,Key2;

/*
*************************************************************************
*                             ��������
*************************************************************************
*/

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  /* CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı���������
   * ����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ�
   */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	
  /*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��ͬһ�����ȼ����飬ǧ��Ҫ�ٷ��飬�мǡ�
	 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* ����ϵͳ�δ�ʱ�� */
  SysTick_Init();
	/* LED ��ʼ�� */
	LED_GPIO_Config();
	/* ���ڳ�ʼ��	*/
	Debug_USART_Config();
	/* ��������ʼ�� */
	Beep_GPIO_Config();
	/* ������ʼ�� */
	Key1_GPIO_Config();
	Key2_GPIO_Config();
	KeyCreate(&Key1,GetPinStateOfKey1);
	KeyCreate(&Key2,GetPinStateOfKey2);
	/* ��������ʼ�� */
	GTP_Init_Panel();	
	/* SDRAM��ʼ�� */
	SDRAM_Init();
	/* LCD��ʼ�� */
	LCD_Init();
  
  /* ��ʼ��GUI */
	GUI_Init();
	/* ���������� */
	WM_MULTIBUF_Enable(1);
  
  while(1)
  {
    MainTask();
  }
}

///**
//  * @brief ������������
//  * @note ��
//  * @param ��
//  * @retval ��
//  */
//static void Key_Task(void* parameter)
//{
//	while(1)
//	{
//		Key_RefreshState(&Key1);//ˢ�°���״̬
//		Key_RefreshState(&Key2);//ˢ�°���״̬
//		if(Key_AccessTimes(&Key1,KEY_ACCESS_READ)!=0)//���������¹�
//		{
//			LED2_TOGGLE;
//			Key_AccessTimes(&Key1,KEY_ACCESS_WRITE_CLEAR);
//		}
//		if(Key_AccessTimes(&Key2,KEY_ACCESS_READ)!=0)//���������¹�
//		{
//			LED1_TOGGLE;
//			Key_AccessTimes(&Key2,KEY_ACCESS_WRITE_CLEAR);
//		}
//		vTaskDelay(50);
//	}
//}


/*********************************************END OF FILE**********************/

