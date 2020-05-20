/***********************************************************************************
 * File                     :TS_DspDrv_GPIO.c
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
#include "F28x_Project.h"
#include "device.h"
#include "gpio.h"
#include "TS_DspDrv_GPIO_X.h"


/**********************************************************************************
 * \function:       GpioLedInit
 * \brief           `0` Param
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void TS_DspDrv_GpioLedInit(void)
{

    /* GPIO blueLed configuration */
    GPIO_SetupPinMux(BLUE_LED, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(BLUE_LED, GPIO_OUTPUT, GPIO_ASYNC);

    /* GPIO RedLed configuration  */
    GPIO_SetupPinMux(RED_LED, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(RED_LED, GPIO_OUTPUT, GPIO_ASYNC);

}
/**********************************************************************************
 * \function:       TS_DspCom_SciPinsConfig
 * \brief           TS_DspCom_SciPinsConfig `0` numbers
 * \param[in]       void
 * \return          void
 **********************************************************************************/
void TS_DspDrv_SciPinsConfig(void)
{

    /* CPU RX pin configuration */
    GPIO_SetupPinMux(DEVICE_GPIO_PIN_SCIRXDA, GPIO_MUX_CPU1, 15);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_SCIRXDA, GPIO_INPUT, GPIO_PUSHPULL);

    /* CPU TX pin configuration */
    GPIO_SetupPinMux(DEVICE_GPIO_PIN_SCITXDA, GPIO_MUX_CPU1, 15);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_SCITXDA, GPIO_OUTPUT, GPIO_ASYNC);

}
