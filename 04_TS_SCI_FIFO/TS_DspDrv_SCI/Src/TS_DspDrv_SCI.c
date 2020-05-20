/***********************************************************************************
 * File                     :TS_DspDrv_SCI.c
 *
 * Title                    :
 *
 * Author                   :Tarik SEMRADE
 *
 * Description              :
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
#include "device.h"
#include "F2837xD_device.h"
#include "F2837xD_sci.h"
#include "F2837xD_Gpio_defines.h"
#include "F2837xD_GlobalPrototypes.h"

/**********************************************************************************
 *  Defines
 *
 *********************************************************************************/

#define LSPCLK_FREQ     (DEVICE_SYSCLK_FREQ/4)          /* Default value at reset */
#define SCI_FREQ        460800U                         /* Change the Bauds Speed */
#define SCI_PRD         ((LSPCLK_FREQ/(SCI_FREQ*8))-1)  /* Baud Rate LSB bit */

/**********************************************************************************
 * \function:       TS_DspCom_SciFifoConfig
 * \brief           TS_DspCom_SciFifoConfig `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void TS_DspDrv_SciFifoConfig(void)
{

    SciaRegs.SCICCR.all = 0x0007;

    /*
     * 1 stop bit,  No loopback
     * No parity,8 char bits,
     * async mode, idle-line protocol
     * enable TX, RX, internal SCICLK,
     * Disable RX ERR, SLEEP, TXWAKE
     * */

    SciaRegs.SCICTL1.all = 0x0003;

    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    SciaRegs.SCIHBAUD.all = ((uint16_t)SCI_PRD  & 0xFF00U) >> 8U;
    SciaRegs.SCILBAUD.all = (uint16_t)SCI_PRD  & 0x00FFU;

    SciaRegs.SCIFFTX.all = 0xC030;
    SciaRegs.SCIFFRX.all = 0x0030;
    SciaRegs.SCIFFCT.all = 0x00;

    /* Relinquish SCI from Reset */
    SciaRegs.SCICTL1.all = 0x0023;
    SciaRegs.SCIFFTX.bit.TXFIFORESET = 1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;

}
/**********************************************************************************
 * \function:       TS_DspCom_Error
 * \brief           TS_DspCom_Error `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void TS_DspDrv_Error(void)
{
    asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}
/**********************************************************************************
 * \function:       TS_DspCom_Error
 * \brief           TS_DspCom_Error `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void TS_DspDrv_Sci(void)
{
    /*
     * Note: Clocks were turned on to the SCIA peripheral
     * in the InitSysCtrl() function
     * */

    SciaRegs.SCICCR.all = 0x0007;
    /*
     * 1 stop bit,  No loopback
     * No parity,8 char bits,
     * async mode, idle-line protocol
     * enable TX, RX, internal SCICLK,
     * Disable RX ERR, SLEEP, TXWAKE
     * */

    SciaRegs.SCICTL1.all = 0x0003;

    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    SciaRegs.SCIHBAUD.all = ((uint16_t) SCI_PRD & 0xFF00U) >> 8U;
    SciaRegs.SCILBAUD.all = (uint16_t) SCI_PRD & 0x00FFU;
    SciaRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
}
/**********************************************************************************
 * \function:       TS_DspCom_SciTransChar
 * \brief           TS_DspCom_SciTransChar `1` numbers
 * \param[in]       Uint16
 * \return          void
 **********************************************************************************/
void TS_DspDrv_SciTransChar(Uint16 p_u16Char)
{
    SciaRegs.SCITXBUF.all = (p_u16Char & 0x00FF);
}
/**********************************************************************************
 * \function:       TS_DspCom_SciTransChar
 * \brief           TS_DspCom_SciTransChar `1` numbers
 * \param[in]       Uint16
 * \return          void
 **********************************************************************************/
void TS_DspDrv_SciTransUint16(Uint16 p_u16Data)
{
    SciaRegs.SCITXBUF.all = ((p_u16Data & 0xFF00) >> 8U);
    SciaRegs.SCITXBUF.all = (p_u16Data & 0x00FF);
}
