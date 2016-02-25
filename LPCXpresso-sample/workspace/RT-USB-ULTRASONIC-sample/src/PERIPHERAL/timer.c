/* ------------------------------------------------------------ *
File Timer.c

32bitタイマーの初期化関数群
タイマ割り込みの割り込み関数はmain.cに記述
* ------------------------------------------------------------ */
#include "timer.h"
#include "LPC13xx.h"			// LPC13xx Peripheral Registers

/*----------------------------------------------------------------------------
  Input  void
  Output void

  32bitタイマー0の割り込みの設定
     対応する割り込み関数:void TIMER32_0_IRQHandler(void)
 *---------------------------------------------------------------------------*/
void initTimer32_0 (void)
{
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	NVIC_SetPriority(TIMER_32_0_IRQn, 4);

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
    LPC_TMR32B0->PR =7200-1;    // 7200-1 = 10kHzでカウント
	LPC_TMR32B0->MCR =0x600;
	LPC_TMR32B0->MR3 = 10;      // 10kHzカウントでMR3=10:割り込み周期は1000Hzに設定
	LPC_TMR32B0->TCR =2;        // TCR Reset
}

/*----------------------------------------------------------------------------
  Input  void
  Output void

 32bitタイマー0のカウントスタート
 *---------------------------------------------------------------------------*/
void startTimer32_0(void)
{
	LPC_TMR32B0->TCR = 1;
}

/*----------------------------------------------------------------------------
  Input  void
  Output void

  32bitタイマー0のカウントストップ
 *---------------------------------------------------------------------------*/
void stopTimer32_0(void)
{
	LPC_TMR32B0->TCR = 0;
}

/*----------------------------------------------------------------------------
  Input  void
  Output void

  32bitタイマー1の割り込みの設定
  対応する割り込み関数:void TIMER32_1_IRQHandler(void)
 *---------------------------------------------------------------------------*/
void initTimer32_1 (void)
{
	NVIC_EnableIRQ(TIMER_32_1_IRQn);
	NVIC_SetPriority(TIMER_32_1_IRQn, 5);

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
	LPC_TMR32B1->PR  = 7200-1; // 7200-1 = 10kHzでカウント
	LPC_TMR32B1->MCR = 0x600;
	LPC_TMR32B1->MR3 = 1000;    // 10kHzカウントでMR3=1000: 割り込み周期は10Hzに設定
	LPC_TMR32B1->TCR = 2;      // TCR Reset
}

/*----------------------------------------------------------------------------
  Input  void
  Output void

 32bitタイマー1のカウントスタート
 *---------------------------------------------------------------------------*/
void startTimer32_1(void)
{
	LPC_TMR32B1->TCR = 1;
}

/*----------------------------------------------------------------------------
  Input  void
  Output void

  32bitタイマー1のカウントストップ
 *---------------------------------------------------------------------------*/
void stopTimer32_1(void)
{
	LPC_TMR32B1->TCR = 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/