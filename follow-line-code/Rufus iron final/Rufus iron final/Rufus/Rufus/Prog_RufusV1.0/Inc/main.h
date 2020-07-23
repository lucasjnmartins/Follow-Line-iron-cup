/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
	volatile uint16_t adc_valor[8];
	volatile int power;
	volatile int Direita;
	volatile int Esquerda;
	volatile int Encoder1;
	volatile int Encoder2;
	static int vi_1;
	static int vi_2;
	volatile uint16_t Start;
	volatile uint16_t Direita_Recebida;
	volatile uint16_t Encoder1_Recebida;
	volatile uint16_t Velocidade_Inicial_Recebida;
	volatile uint16_t Velocidade_Final_Recebida;
	volatile uint16_t Kp_Recebido;
	volatile uint16_t Kd_Recebido;
	volatile uint16_t Ki_Recebido;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AIN1_Pin GPIO_PIN_13
#define AIN1_GPIO_Port GPIOC
#define AIN2_Pin GPIO_PIN_14
#define AIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_15
#define BIN1_GPIO_Port GPIOC
#define BIN2_Pin GPIO_PIN_0
#define BIN2_GPIO_Port GPIOF
#define Dir_Pin GPIO_PIN_1
#define Dir_GPIO_Port GPIOF
#define Dir_EXTI_IRQn EXTI0_1_IRQn
#define S7_Pin GPIO_PIN_0
#define S7_GPIO_Port GPIOA
#define S6_Pin GPIO_PIN_1
#define S6_GPIO_Port GPIOA
#define S5_Pin GPIO_PIN_2
#define S5_GPIO_Port GPIOA
#define S4_Pin GPIO_PIN_3
#define S4_GPIO_Port GPIOA
#define S3_Pin GPIO_PIN_4
#define S3_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_5
#define S2_GPIO_Port GPIOA
#define S1_Pin GPIO_PIN_6
#define S1_GPIO_Port GPIOA
#define S0_Pin GPIO_PIN_7
#define S0_GPIO_Port GPIOA
#define Led_esq_Pin GPIO_PIN_0
#define Led_esq_GPIO_Port GPIOB
#define Led_dir_Pin GPIO_PIN_2
#define Led_dir_GPIO_Port GPIOB
#define Esq_Pin GPIO_PIN_8
#define Esq_GPIO_Port GPIOA
#define Esq_EXTI_IRQn EXTI4_15_IRQn
#define start_Pin GPIO_PIN_11
#define start_GPIO_Port GPIOA
#define start_EXTI_IRQn EXTI4_15_IRQn
#define Enc2_Pin GPIO_PIN_12
#define Enc2_GPIO_Port GPIOA
#define Enc2_EXTI_IRQn EXTI4_15_IRQn
#define Led7_Pin GPIO_PIN_6
#define Led7_GPIO_Port GPIOF
#define Led8_Pin GPIO_PIN_7
#define Led8_GPIO_Port GPIOF
#define INT2_Pin GPIO_PIN_15
#define INT2_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_3
#define Buzzer_GPIO_Port GPIOB
#define INT1_Pin GPIO_PIN_4
#define INT1_GPIO_Port GPIOB
#define Enc1_Pin GPIO_PIN_7
#define Enc1_GPIO_Port GPIOB
#define Enc1_EXTI_IRQn EXTI4_15_IRQn
#define PWMB_Pin GPIO_PIN_8
#define PWMB_GPIO_Port GPIOB
#define PWMA_Pin GPIO_PIN_9
#define PWMA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
