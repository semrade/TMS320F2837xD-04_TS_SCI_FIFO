/***********************************************************************************
 * File                     :TS_DspDrv_GPIO_X.h
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
#ifndef TS_DSPDRV_GPIO_TS_DSPDRV_GPIO_X_H_
#define TS_DSPDRV_GPIO_TS_DSPDRV_GPIO_X_H_

/**********************************************************************************
 *  Defines
 *
 *********************************************************************************/
#define BLUE_LED        DEVICE_GPIO_PIN_LED1
#define RED_LED         DEVICE_GPIO_PIN_LED2

/**********************************************************************************
 *  External prototypes
 *
 *********************************************************************************/
extern void TS_DspDrv_GpioLedInit(void);
extern void TS_DspDrv_SciPinsConfig(void);


#endif /* TS_DSPDRV_GPIO_TS_DSPDRV_GPIO_X_H_ */
