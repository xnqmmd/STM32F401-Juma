#include "pwm.h"
TIM_HandleTypeDef        TimHandleT2;

/**
  * @brief  Init TIM PWM .
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *                the configuration information for TIM module.
  * @param  Channel: TIM Channels to be enabled.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
        * @param  GPIOx:   x can be (A..D) to select the GPIO peripheral .                    
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
        * @param  Freq:        specifies the PWM frequency to be written.
        * @param  Pulse: specifies the PWM duty cycle to be written.
  * @retval HAL status
  */
HAL_StatusTypeDef TIM_PWM_Init(TIM_HandleTypeDef *htim,  uint32_t Channel,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint32_t Freq,uint32_t Pulse){
        
        //TODO:Simplify the PWM initialization function
        return HAL_OK;
}

/**
  * @brief  set PWM duty cycle.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *                the configuration information for TIM module.
  * @param  Channel: TIM Channels to be enabled.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @retval HAL status
  */
HAL_StatusTypeDef TIM_PWM_Duty(TIM_HandleTypeDef *htim,  uint32_t Channel,uint32_t Pulse){
        
         /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));
        
  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
                          /* Set the Capture Compare Register value */
   htim->Instance->CCR1 =Pulse;
    }break;
    case TIM_CHANNEL_2:
    {
                         /* Set the Capture Compare Register value */
       htim->Instance->CCR2 =Pulse;
    }break;
    case TIM_CHANNEL_3:
    {
                         /* Set the Capture Compare Register value */
       htim->Instance->CCR3 =Pulse;
    }break;
    case TIM_CHANNEL_4:
    {
                         /* Set the Capture Compare Register value */
       htim->Instance->CCR4 =Pulse;
    }break;
    default:
    break;  
  }
   return HAL_OK;        
}


void PWM_init(){        
TIM_OC_InitTypeDef       pwmConfig;
//PWM I/O                
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_TIM2_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
  TimHandleT2.Instance = TIM2;
  TimHandleT2.Init.Period = 1000 - 1;  
  TimHandleT2.Init.Prescaler = 8 - 1;   
  TimHandleT2.Init.ClockDivision = 0;
  TimHandleT2.Init.CounterMode = TIM_COUNTERMODE_UP;  
  HAL_TIM_PWM_Init(&TimHandleT2);

  pwmConfig.OCMode=TIM_OCMODE_PWM1;
  pwmConfig.Pulse=0;
  HAL_TIM_PWM_ConfigChannel(&TimHandleT2, &pwmConfig, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&TimHandleT2, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&TimHandleT2, &pwmConfig, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&TimHandleT2, TIM_CHANNEL_2);

//Motor I/O
GPIO_InitTypeDef GPIO_InitStruct1;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct1.Pin     = GPIO_PIN_0|GPIO_PIN_8;
  GPIO_InitStruct1.Mode    = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct1.Pull    = GPIO_NOPULL;
  GPIO_InitStruct1.Speed   = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct1);
  
GPIO_InitTypeDef GPIO_InitStruct2;
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct2.Pin     = GPIO_PIN_5|GPIO_PIN_13;
  GPIO_InitStruct2.Mode    = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct2.Pull    = GPIO_NOPULL;
  GPIO_InitStruct2.Speed   = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct2);
}

void Motor_Control_1(int16_t Pulse){
  if(Pulse>=0){
        if(Pulse>1000) Pulse=1000;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);        
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
    TIM_PWM_Duty(&TimHandleT2,TIM_CHANNEL_1,Pulse);
  }
  else{
        if(Pulse<-1000) Pulse=-1000;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);        
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);        
    TIM_PWM_Duty(&TimHandleT2,TIM_CHANNEL_1,-Pulse);
  }
}
void Motor_Control_2(int16_t Pulse){
  if(Pulse>=0){
        if(Pulse>1000)Pulse=1000;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);        
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);        
    TIM_PWM_Duty(&TimHandleT2,TIM_CHANNEL_2,Pulse);
  }
  else{
        if(Pulse<-1000)Pulse=-1000;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);        
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);        
    TIM_PWM_Duty(&TimHandleT2,TIM_CHANNEL_2,-Pulse);
  }
}