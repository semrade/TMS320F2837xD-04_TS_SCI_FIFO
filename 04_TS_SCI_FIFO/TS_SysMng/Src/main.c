/***********************************************************************************
 * File                     :main.c
 *
 * Title                    :
 *
 * Author                   :Tarik SEMRADE
 *
 * Description              :Serial Communication Interface tutorial
 *
 * Version                  :
 *
 * Copyright (c) 2020 Tarik SEMRADE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *********************************************************************************/

/**********************************************************************************
 *  Included Files
 *
 *********************************************************************************/
#include "TS_DspDrv_SCI_X.h"
#include "TS_DspDrv_GPIO_X.h"
#include "F28x_Project.h"
#include "main.h"
#include "device.h"
#include "gpio.h"

/**********************************************************************************
 *  Defines
 *
 *********************************************************************************/
#define FIFO_SIZE       16U

/**********************************************************************************
 *  Global Variables
 *
 *********************************************************************************/
/* Send data for SCI-A */
Uint16 t_u16SendData[FIFO_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0 };

/* Received data for SCI-A */
Uint16 t_u16RcvData[FIFO_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0 };

/* Used for checking the received data */
Uint16 rdata_pointA;
Uint16 u16Index;
static bool bSendData = false;


/**********************************************************************************
 * \function:       main
 * \brief           main `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void main(void)
{

    /* Set up system flash and turn peripheral clocks */
    InitSysCtrl();

    /* Init all gpio to input */
    InitGpio();

    /* Globally disable maskable CPU interrupts */
    DINT;

    /* Clear and disable all PIE interrupts */
    InitPieCtrl();

    /* Individually disable maskable CPU interrupts */
    IER = 0x0000;

    /* Clear all CPU interrupt flags */
    IFR = 0x0000;

    /* Populate the PIE interrupt vector table */
    InitPieVectTable();

    /***********************Interrupt linking functions*****************************/
    EALLOW;

    /* Interrupt for RX interrupt service routine */
    PieVectTable.SCIA_RX_INT = &Scia_Rx_Fifo_ISR;

    /* Interrupt for TX interrupt service routine */
    //PieVectTable.SCIA_TX_INT = &Scia_Tx_Fifo_ISR;
	
	/* Timer0 ISR function linking */
	PieVectTable.TIMER0_INT = &Timer0_ISR;

    EDIS;
    /************************Peripheral Initialization*****************************/

    /* PIE Group 9, INT1 */
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;

    /* PIE Group 9, INT2 */
    //PieCtrlRegs.PIEIER9.bit.INTx2 = 1;

    /* Enable TINT0 in the PIE: Group 1 interrupt 7 */
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	
	/* Enable group 1 interrupts */
    IER |= M_INT1;
	
    /* Enable CPU INT */
    IER |= M_INT9;

    /* Enable the PIE block */
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

    EINT;

    /* FIFO configuration */
    TS_DspDrv_SciFifoConfig();

    /* GPIO configuration for SCI */
    TS_DspDrv_SciPinsConfig();

    /* GPIO Led init */
    TS_DspDrv_GpioLedInit();

    /* Initialize all timer with default values */
    InitCpuTimers();

    /* 200MHz CPU Freq, 50 uSeconds Period (in uSeconds) */
    ConfigCpuTimer(&CpuTimer0, 200, 100);
	
    /* Start Timer0 */
    StartCpuTimer0();
	
	
    /* Infinite led loop */
    while (1)
    {

    }

}
/**********************************************************************************
 * \function:       Scia_Tx_Fifo_ISR
 * \brief           Scia_Tx_Fifo_ISR `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
interrupt void Scia_Tx_Fifo_ISR(void)
{
    Uint16 l_u16Index;

    for (l_u16Index = 0; l_u16Index < FIFO_SIZE; l_u16Index++)
    {
        /* Send data */
        SciaRegs.SCITXBUF.all = t_u16SendData[l_u16Index];
    }

    /* Clear SCI Interrupt flag */
    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;

    /*  Issue PIE ACK */
    PieCtrlRegs.PIEACK.bit.ACK9 = 0x1;
}
/**********************************************************************************
 * \function:       Scia_Rx_Fifo_ISR
 * \brief           Scia_Rx_Fifo_ISR `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
interrupt void Scia_Rx_Fifo_ISR(void)
{
    Uint16 l_u16Index;

    for (l_u16Index = 0; l_u16Index < FIFO_SIZE; l_u16Index++)
    {
        /* Read data */
        t_u16RcvData[l_u16Index] = (SciaRegs.SCIRXBUF.all & 0x00FF);
    }

    bSendData = true;

    /* Clear Overflow flag */
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;

    /* Clear Interrupt flag */
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;

    /*  Issue PIE ACK */
    PieCtrlRegs.PIEACK.bit.ACK9 = 0x1;
}
/**********************************************************************************
 * \function:       Timer0_ISR
 * \brief           `0` Param
 * \param[in]       void
 * \return          void
 **********************************************************************************/
interrupt void Timer0_ISR(void)
{

    /* Clear Timer interrupt flag */
    CpuTimer0Regs.TCR.bit.TIF = 0;

    /* Increment timer0 interrupt counter */
    CpuTimer0.InterruptCount++;

    /* led blinking with =! frequency */
    if ( 5000UL == CpuTimer0.InterruptCount )
    {
        /* Toggle Red Led with 250ms = 5 000 * 50us*/
        GPIO_togglePin(RED_LED);

    }
    if ( 10000UL == CpuTimer0.InterruptCount  )
    {
        /* Toggle Blue Led with 500ms = 10000 * 50us*/
        GPIO_togglePin(BLUE_LED);

        /* restart interrupt counter here please */
        CpuTimer0.InterruptCount = 0;
     }

    /* Send data to replay if asked */
    if (true == bSendData)
    {
        /* Send the received table */
        for (u16Index = 0; u16Index < FIFO_SIZE; u16Index++)
        {
            /* Send data */
            SciaRegs.SCITXBUF.all = t_u16RcvData[u16Index];
        }

        /* Disable Sending data */
        bSendData = false;
    }

    /* Acknowledge this interrupt to receive more interrupts from group 1 */
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}
