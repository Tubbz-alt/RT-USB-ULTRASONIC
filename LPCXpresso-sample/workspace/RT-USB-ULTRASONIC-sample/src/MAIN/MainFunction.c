/**
 * @file   MainFunction.c
 * @brief  データの送信を行う<br>
 *         10msec毎に割り込み関数で処理を実行
 *
 * @author RTCorp. Ryota Takahashi
 */


#include "LPC13xx.h"
#include "core_cm3.h"
#include "type.h"

#include "timer.h"
#include "pwm.h"
#include "MainFunction.h"
#include "UserInterface.h"

#include "debug.h"
#include "uart.h"

#include "usbTransmission.h"

#include "srf02.h"

volatile static uint8_t flag_send_data_enable = 0;

/**
 * MainFunction.c内の関数を使用できるようにする
 *
 * @param void
 * @return void
 */
void initMainFunction(void)
{
	startTimer32_1();
}

/**
 * 機体データの送信をするかどうかを選択
 *
 * @param en 1:送信 0:送信じ禁止
 * @return void
 */
void setSendDataEnable(uint8_t en)
{
	flag_send_data_enable = en;
}

/**
 * 100msec毎に行われる処理 <br>
 * 各種情報をUART,USBで送信
 *
 * @param  void
 * @return void
 */
void TIMER32_1_IRQHandler(void)
{
	static uint32_t timestamp;
	uint16_t range_data;

	LPC_TMR32B1->IR=0x08; //clear interrupt flag

	range_data = getRangeData();

	//10Hzの周期でデータを送る
	if(flag_send_data_enable == 1)
	{
		//UART経由でデータを送信
		myPrintfUART("%d,%d \n", timestamp,range_data);

		if(isUSBConfig() == 1) //USB接続確立
		{
			//USB経由でデータを送信
			myPrintfUSB("%d,%d \n", timestamp,range_data);
		}
	}

	timestamp = timestamp + 100;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
