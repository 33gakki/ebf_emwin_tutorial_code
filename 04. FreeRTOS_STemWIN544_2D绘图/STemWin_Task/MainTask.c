/**
  *********************************************************************
  * @file    MainTask.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 ����ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "MainTask.h"

#include <stdlib.h>

/*
*************************************************************************
*                               ȫ�ֱ���
*************************************************************************
*/
GUI_RECT BasicRect = {10, 10, 100, 105};
static const float pi = 3.1415926L;
static const unsigned aValues[] = {100, 135, 190, 240, 340, 360};
static const GUI_COLOR aColor[] = {GUI_BLUE, GUI_GREEN, GUI_RED,
                            GUI_CYAN, GUI_MAGENTA, GUI_YELLOW};
static const char QR_TEXT[] = "http://www.firebbs.cn";
static const GUI_POINT _aPointArrow[] = {
  {  0,   0 },
  {-40, -30 },
  {-10, -20 },
  {-10, -70 },
  { 10, -70 },
  { 10, -20 },
  { 40, -30 },
};
GUI_POINT aArrowRotatedPoints[GUI_COUNTOF(_aPointArrow)];

static const GUI_POINT _aPointStar[] = {
  {  0, -36 },
  {  8,  -8 },
  { 36,   0 },
  {  8,   8 },
  {  0,  36 },
  { -8,   8 },
  {-36,   0 },
  { -8,  -8 }
};
GUI_POINT aStarRotatedPoints[GUI_COUNTOF(_aPointStar)];

static const GUI_POINT _aPointHexagon[] = {
  {  0, -30 },
  { 26, -15 },
  { 26,  15 },
  {  0,  30 },
  {-26,  15 },
  {-26, -15 },
};
GUI_POINT aHexagonRotatedPoints[GUI_COUNTOF(_aPointHexagon)];

/*
*************************************************************************
*                               ����
*************************************************************************
*/
/**
  * @brief ��ͼ��ͼ����
  * @note ��
  * @param x0����ͼԲ�ĵ�x����
  *        y0����ͼԲ�ĵ�y����
  *        r����ͼ�뾶
  * @retval ��
  */
static void Pie_Chart_Drawing(int x0, int y0, int r)
{
	int i, a0 = 0, a1 = 0;
	
	for(i = 0; i < GUI_COUNTOF(aValues); i++)
	{
		if(i == 0) a0 = 0;
		else a0 = aValues[i - 1];
		a1 = aValues[i];	
		GUI_SetColor(aColor[i]);
		GUI_DrawPie(x0, y0, r, a0, a1, 0);
	}
}

/**
  * @brief ��ά������
  * @note ��
  * @param pText����ά������
  *        PixelSize����ά�뵥�����صĴ�С
  *        EccLevel��������뼶��
  *        x0����ά��ͼ����LCD������x
  *        y0����ά��ͼ����LCD������y
  * @retval ��
  */
static void QR_Code_Drawing(const char *pText, int PixelSize, int EccLevel, int x0, int y0)
{
	GUI_HMEM hQR;
	
	/* ������ά����� */
	hQR = GUI_QR_Create(pText, PixelSize, EccLevel, 0);
	/* ���ƶ�ά�뵽LCD */
	GUI_QR_Draw(hQR, x0, y0);
	/* ɾ����ά����� */
	GUI_QR_Delete(hQR);
}

/**
  * @brief 2D��ͼ����
  * @note ��
  * @param ��
  * @retval ��
  */
static void _2D_Graph_Drawing(void)
{
	static int y = 120;
	I16 aY[125] = {0};
	int i;
	int a0 = 0, a1 = 0;
	float angle = 0.0;
	
	/* ���Ƹ��־��� */
	GUI_SetColor(GUI_RED);
	GUI_DrawRectEx(&BasicRect);
	BasicRect.x0 += 116;
	BasicRect.x1 += 116;
	GUI_FillRectEx(&BasicRect);
	GUI_DrawRoundedRect(240, 10, 330, 105, 10);
	GUI_DrawRoundedFrame(352, 10, 442, 105, 10, 10);
	GUI_FillRoundedRect(468, 10, 558, 105, 10);
	GUI_DrawGradientRoundedH(584, 10, 674, 105, 10, GUI_LIGHTMAGENTA, GUI_LIGHTCYAN);
	GUI_DrawGradientRoundedV(700, 10, 790, 105, 10, GUI_LIGHTMAGENTA, GUI_LIGHTCYAN);
	
	/* �������� */
	GUI_SetPenSize(10);
	GUI_SetColor(GUI_YELLOW);
	GUI_DrawLine(10, 140, 100, 240);
	
	/* ���ƶ���� */
	GUI_SetColor(GUI_RED);
	GUI_FillPolygon(&_aPointArrow[0], 7, 190, y + 85);
	GUI_SetColor(GUI_GREEN);
	GUI_FillPolygon(&_aPointStar[0], 8, 290, y + 45);
	GUI_SetColor(GUI_BLUE);
	GUI_FillPolygon(&_aPointHexagon[0], 6, 390, y + 45);
	
	/* ��ת����� */
	angle = pi / 2;
	GUI_RotatePolygon(aArrowRotatedPoints,
	                  _aPointArrow, 
                    (sizeof(_aPointArrow) / sizeof(_aPointArrow[0])),
										angle);
	GUI_SetColor(GUI_RED);
	GUI_FillPolygon(&aArrowRotatedPoints[0], 7, 220, y + 130);
	angle = pi / 4;
	GUI_RotatePolygon(aStarRotatedPoints,
	                  _aPointStar, 
                    (sizeof(_aPointStar) / sizeof(_aPointStar[0])),
										angle);
	GUI_SetColor(GUI_GREEN);
	GUI_FillPolygon(&aStarRotatedPoints[0], 8, 290, y + 120);
	angle = pi / 6;
	GUI_RotatePolygon(aHexagonRotatedPoints,
	                  _aPointHexagon, 
                    (sizeof(_aPointHexagon) / sizeof(_aPointHexagon[0])),
										angle);
	GUI_SetColor(GUI_BLUE);
	GUI_FillPolygon(&aHexagonRotatedPoints[0], 6, 390, y + 120);
	
	/* ����Բ */
	GUI_SetColor(GUI_LIGHTMAGENTA);
	for(i = 10; i <= 70; i += 10)
	{
		GUI_DrawCircle(560, 217, i);
	}
	GUI_SetColor(GUI_LIGHTCYAN);
	GUI_FillCircle(713, 217, 70);
	
	/* ������Բ */
	GUI_SetColor(GUI_BLUE);
	GUI_FillEllipse(80, 393, 50, 70);
	GUI_SetPenSize(2);
	GUI_SetColor(GUI_WHITE);
	GUI_DrawEllipse(80, 393, 50, 10);
	
	/* ����Բ�� */
	GUI_SetPenSize(10);
	GUI_SetColor(GUI_GRAY_3F);
	GUI_DrawArc(240, 393, 80, 80, -30, 210);
	
	/* ��������ͼ */
	for(i = 0; i< GUI_COUNTOF(aY); i++)
	{
		aY[i] = rand() % 100;
	}
	GUI_SetColor(GUI_BLACK);
	GUI_DrawGraph(aY, GUI_COUNTOF(aY), 350, 340);
	
	/* ���Ʊ�ͼ */
	Pie_Chart_Drawing(560, 393, 60);
	
	/* ���ƶ�ά�� */
	QR_Code_Drawing(QR_TEXT, 5, GUI_QR_ECLEVEL_M, 650, 330);
}

/**
  * @brief Alpha���
  * @note ��
  * @param ��
  * @retval ��
  */
static void Alpha_Blending(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_32B_ASCII);
	GUI_DispStringHCenterAt("Alpha blending", 223, 203);

	/* ��Alpha��ֵ��ӵ���ɫ�в���ʾ */
	GUI_SetAlpha(0x80);
	GUI_SetColor(GUI_RED | (0x80 << 24));
	GUI_FillRect(20, 20, 235, 235);
	GUI_SetAlpha(0x80);
	GUI_SetColor(GUI_GREEN | (0x80 << 24));
	GUI_FillRect(110, 110, 325, 325);
	GUI_SetAlpha(0x80);
	GUI_SetColor(GUI_BLUE | (0x80 << 24));
	GUI_FillRect(210, 210, 425, 425);
}

/**
  * @brief GUI������
  * @note ��
  * @param ��
  * @retval ��
  */
void MainTask(void)
{
	/* ���ñ���ɫ */
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	
	/* 2D��ͼ */
	_2D_Graph_Drawing();
	
	GUI_Delay(5000);
	GUI_Clear();
  
	/* Alpha��� */
	Alpha_Blending();
	
	while(1)
	{
		GUI_Delay(100);
	}
}
