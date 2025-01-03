/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/07/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *IAP upgrade routine:
 *Support serial port and USB for FLASH burning
 *
 *1. Use the IAP download tool to realize the download PB4 floating (default pull-up input)
 *2. After downloading the APP, connect PA0 to ground (low level input), and press
 *the reset button to run the APP program.
 *3. The routine needs to install the CH372 driver.
 *
*/

#include "ch32m030_usbfs_device.h"
#include "debug.h"
#include "iap.h"


/*********************************************************************
 * @fn      IAP_2_APP
 *
 * @brief   IAP_2_APP program.
 *
 * @return  none
 */
void IAP_2_APP(void) {
    USBFS_Device_Init(DISABLE);
    GPIO_Cfg_Float();
    RCC_PB2PeriphClockCmd( RCC_PB2Periph_AFIO, DISABLE );
    RCC_HBPeriphClockCmd( RCC_HBPeriph_USBFS, DISABLE );
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_USART1,DISABLE);

    Delay_Ms(50);
    printf("jump APP\r\n");
    Delay_Ms(10);
    NVIC_EnableIRQ(Software_IRQn);
    NVIC_SetPendingIRQ(Software_IRQn);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program..
 *
 * @return  none
 */
int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    if(PB4_Check() == 0){
        Delay_Ms(10);
        IAP_2_APP();
        while(1);
    }

    /* Usb Init */
    USBFS_RCC_Init( );
    USBFS_Device_Init( ENABLE );
    USART1_CFG(57600);
    while(1)
    {
        if( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
            UART_Rx_Deal();
        }
        if (End_Flag)
        {
            Delay_Ms(10);
            IAP_2_APP();
            while(1);
        }
    }
}







