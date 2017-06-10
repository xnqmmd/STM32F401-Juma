#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
extern UART_HandleTypeDef Uart1Handle;
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&Uart1Handle);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}