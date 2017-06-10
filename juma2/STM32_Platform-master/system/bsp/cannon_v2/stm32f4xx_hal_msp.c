/**
  ******************************************************************************
  * @file    PWR/PWR_CurrentConsumption/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    09-October-2015
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_msp.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @defgroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

UART_HandleTypeDef Uart1Handle;
UART_HandleTypeDef Uart2Handle;


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_StatusTypeDef status = HAL_UART_Transmit(&Uart1Handle, (uint8_t *)&ch, 1, 0xFFFF);

    if (status != HAL_OK) {
        //while (1);
        return EOF;
    }
    return ch;
}
int fputc2(int ch, FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_StatusTypeDef status = HAL_UART_Transmit(&Uart2Handle, (uint8_t *)&ch, 1, 0xFFFF);

    if (status != HAL_OK) {
        //while (1);
        return EOF;
    }
    return ch;
}


int Uart_Tx_String(char *string, uint16_t len)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(&Uart2Handle, (uint8_t *)string, len, 0xFFFF);

    if (status != HAL_OK) {
        //while (1);
        return HAL_MSP_FAIL;
    }
    return HAL_MSP_SUCCESS;
}

/* You know it's a blocking call, don't you? */
int Uart_Rx_String(char *string, uint16_t len, uint32_t timeout)
{
    uint8_t i;
    for(i=0; i<len; i++){
      //string[i] = 13; //set to a CR (acsii 13 or Enter)
      string[i] = 0;    //set to '\0'
    }

    HAL_StatusTypeDef status = HAL_UART_Receive(&Uart2Handle, (uint8_t *)string, len, timeout);
    //printf("status:%d\n", status);

    if ( (status != HAL_OK) && (status != HAL_TIMEOUT) ){
       return HAL_MSP_FAIL;
    }

    return HAL_MSP_SUCCESS;
}

void UART_Init(void)
{

    /*##-1- Configure the UART1 peripheral ######################################*/
    Uart1Handle.Instance          = USARTx1;

    Uart1Handle.Init.BaudRate     = 19200;
    Uart1Handle.Init.WordLength   = UART_WORDLENGTH_8B;
    Uart1Handle.Init.StopBits     = UART_STOPBITS_1;
    Uart1Handle.Init.Parity       = UART_PARITY_NONE;
    Uart1Handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    Uart1Handle.Init.Mode         = UART_MODE_TX|UART_MODE_RX;
    Uart1Handle.Init.OverSampling = UART_OVERSAMPLING_16;

    if(HAL_UART_Init(&Uart1Handle) != HAL_OK)
    {
       // while (1);
    }

    /*##-1- Configure the UART2 peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART1 configured as follow:
        - Word Length = 8 Bits
        - Stop Bit = One Stop bit
        - Parity = ODD parity
        - BaudRate = 9600 baud
        - Hardware flow control disabled (RTS and CTS signals) */
//    Uart2Handle.Instance          = USARTx2;

//    Uart2Handle.Init.BaudRate     = 115200;
//    Uart2Handle.Init.WordLength   = UART_WORDLENGTH_8B;
//    Uart2Handle.Init.StopBits     = UART_STOPBITS_1;
//    Uart2Handle.Init.Parity       = UART_PARITY_NONE;
//    Uart2Handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
//    Uart2Handle.Init.Mode         = UART_MODE_TX|UART_MODE_RX;
//    Uart2Handle.Init.OverSampling = UART_OVERSAMPLING_16;


//    if(HAL_UART_Init(&Uart2Handle) != HAL_OK)
//    {
//        while (1);
//    }

    //printf("\n\rUART2 initialized!\n\r");   

}


/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if(huart == &Uart1Handle)
    {
        GPIO_InitTypeDef  GPIO_InitStruct;

        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        USARTx1_TX_GPIO_CLK_ENABLE();
        USARTx1_RX_GPIO_CLK_ENABLE();
			  
			

        /* Enable USARTx clock */
         USARTx1_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();
        /*##-2- Configure peripheral GPIO ##########################################*/
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = USARTx1_TX_PIN;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
        GPIO_InitStruct.Alternate = USARTx1_TX_AF;

        HAL_GPIO_Init(USARTx1_TX_GPIO_PORT, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = USARTx1_RX_PIN;
        GPIO_InitStruct.Alternate = USARTx1_RX_AF;

        HAL_GPIO_Init(USARTx1_RX_GPIO_PORT, &GPIO_InitStruct);  
				
				 HAL_NVIC_EnableIRQ(USART1_IRQn);
			   HAL_NVIC_SetPriority(USART1_IRQn,0,0);				

    }
    else if(huart == &Uart2Handle)
    {
        GPIO_InitTypeDef  GPIO_InitStruct;

        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        USARTx2_TX_GPIO_CLK_ENABLE();
        USARTx2_RX_GPIO_CLK_ENABLE();

        /* Enable USARTx clock */
        USARTx2_CLK_ENABLE();

        /*##-2- Configure peripheral GPIO ##########################################*/
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = USARTx2_TX_PIN;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
        GPIO_InitStruct.Alternate = USARTx2_TX_AF;

        HAL_GPIO_Init(USARTx2_TX_GPIO_PORT, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = USARTx2_RX_PIN;
        GPIO_InitStruct.Alternate = USARTx2_RX_AF;

        HAL_GPIO_Init(USARTx2_RX_GPIO_PORT, &GPIO_InitStruct);    
    }
    else{
        while(1);
    }
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if(huart == &Uart1Handle)
    {
        /*##-1- Reset peripherals ##################################################*/
			  __HAL_RCC_USART1_CLK_DISABLE();
        USARTx1_FORCE_RESET();
        USARTx1_RELEASE_RESET();
			  HAL_NVIC_DisableIRQ(USART1_IRQn);

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure UART Tx as alternate function  */
        HAL_GPIO_DeInit(USARTx1_TX_GPIO_PORT, USARTx1_TX_PIN);
        /* Configure UART Rx as alternate function  */
        HAL_GPIO_DeInit(USARTx1_RX_GPIO_PORT, USARTx1_RX_PIN);    
    }
    else if(huart == &Uart2Handle)
    {
        /*##-1- Reset peripherals ##################################################*/
        USARTx2_FORCE_RESET();
        USARTx2_RELEASE_RESET();

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure UART Tx as alternate function  */
        HAL_GPIO_DeInit(USARTx2_TX_GPIO_PORT, USARTx2_TX_PIN);
        /* Configure UART Rx as alternate function  */
        HAL_GPIO_DeInit(USARTx2_RX_GPIO_PORT, USARTx2_RX_PIN);    
    }
    else{
        while(1);
    }

}

/**
  * @brief  Initializes the RTC MSP.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
//__weak void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
//{
//  /* NOTE : This function Should not be modified, when the callback is needed,
//            the HAL_RTC_MspInit could be implemented in the user file
//   */
//}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    RCC_OscInitTypeDef        RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

    /*##-1- Configue LSI as RTC clock soucre ###################################*/
#ifdef RTC_LSI
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#endif

#ifdef RTC_LSE
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
#endif
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
#ifdef RTC_LSI
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
#endif

#ifdef RTC_LSE
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
#endif
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }

    /*##-2- Enable RTC peripheral Clocks #######################################*/
    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    /*##-3- Configure the NVIC for RTC WakeUp Timer ############################*/
    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

/**
  * @brief RTC MSP De-Initialization
  *        This function freeze the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
    /*##-1- Reset peripherals ##################################################*/
    __HAL_RCC_RTC_DISABLE();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


/*
 * Original HAL_Delay may cause overflow.
 */
void HAL_Delay(__IO uint32_t Delay)
{
  uint32_t tt = HAL_GetTick();
   
  while((uint32_t)(HAL_GetTick() - tt) < Delay)
  {
  }
}
 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/