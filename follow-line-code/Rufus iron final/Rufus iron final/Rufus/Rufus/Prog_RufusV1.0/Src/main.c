/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "drive_TB66.h"
#include "controle.h"
#include "Bluetooth.h"
//#include "controle.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t rx_endereco[Pacote_variaveis] = { 0 };
rx_pacote_estado_t pacote_estado = RX_STATUS_ERRO;
void serial_init(void) {
	MX_DMA_Init();
	MX_USART1_UART_Init();
	HAL_UART_Receive_DMA(&huart1, rx_endereco, Pacote_variaveis);

}
uint8_t adc_completo = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	adc_completo = 1;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {

	if (huart->Instance != USART1) {
		return;
	}

	if (rx_endereco[RX_Pacote_Comeco_I] != RX_Pacote_comeco
			|| rx_endereco[RX_Pacote_fim_I] != RX_Pacote_fim) {
		pacote_estado = RX_STATUS_ERRO;
		for (int i = 0; i < Pacote_variaveis; i++) {
			rx_endereco[i] = 0;
		}
		return;
	}

	Start = rx_endereco[RX_Pacote_Start_I];

	Direita_Recebida = rx_endereco[RX_Pacote_Direita_I];

	Encoder1_Recebida = rx_endereco[RX_Pacote_Encoder_I];

	Velocidade_Inicial_Recebida = rx_endereco[RX_Pacote_velocidade_inicial_I];

	Velocidade_Final_Recebida = rx_endereco[RX_Pacote_velocidade_Final_I];

	Kp_Recebido = (rx_endereco[RX_Pacote_Kp_I]);

	Kd_Recebido = (rx_endereco[RX_Pacote_Kd_I]);

	Ki_Recebido = (rx_endereco[RX_Pacote_Ki_I]);

}
volatile int scan;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM3) {
		posicao();
		PID();
		TIM3->SR &= ~TIM_SR_UIF;
	}
	if (htim->Instance == TIM14) {
		scanner();
		scan++;
		TIM14->SR &= ~TIM_SR_UIF;
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC_Init();
	MX_TIM1_Init();
	MX_TIM14_Init();
	MX_TIM16_Init();
	MX_TIM17_Init();
	MX_USART1_UART_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	serial_init();
	power = 0;
	Direita = 0;
	Esquerda = 1;
	Encoder1 = 0;
	Encoder2 = 0;
	int reset = 1;
	int vi_1PID;
	int vi_2PID;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		HAL_GPIO_WritePin(Led_dir_GPIO_Port, Led_dir_Pin,SET);
		HAL_GPIO_WritePin(Led_esq_GPIO_Port, Led_esq_Pin,SET);
		HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, RESET);
		while ((power) || (Start)) {
			vi_1 = 25; // Velocidade_Inicial_Recebida;
			vi_2 = 25; //Velocidade_Inicial_Recebida;
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, RESET);
			HAL_Delay(2000);
			HAL_ADCEx_Calibration_Start(&hadc);
			HAL_ADC_Start_DMA(&hadc, (uint32_t*) adc_valor, 8);
			while (!adc_completo)
				;
			adc_completo = 0;
			inicia_scanner();
			HAL_TIM_Base_Start_IT(&htim14);
			while (scan < 450) {
				velocidade_motor1(0);
				velocidade_motor2(21);
			}
			scan = 0;
			velocidade_motor1(0);
			velocidade_motor2(0);
			motor1_freio();
			motor2_freio();
			HAL_Delay(250);
			while (scan < 1000) {
				velocidade_motor1(0);
				velocidade_motor2(-21);
			}
			scan = 0;
			velocidade_motor1(0);
			velocidade_motor2(0);
			motor1_freio();
			motor2_freio();
			HAL_Delay(250);
			while (scan < 620) {
				velocidade_motor1(0);
				velocidade_motor2(21);
			}
			velocidade_motor1(0);
			velocidade_motor2(0);
			motor1_freio();
			motor2_freio();
			HAL_Delay(500);
			/*while (scan < 10000) {
			 }
			 HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, SET);
			 HAL_Delay(2000);
			 */
			HAL_TIM_Base_Stop_IT(&htim14);
			HAL_TIM_Base_Start_IT(&htim3);
			Direita = 0;
			vi_1 = 25; // Velocidade_Inicial_Recebida;
			vi_2 = 25; // Velocidade_Inicial_Recebida;
			while ((power) || (Start)) {
				HAL_GPIO_WritePin(Led_dir_GPIO_Port, Led_dir_Pin,SET);
				HAL_GPIO_WritePin(Led_esq_GPIO_Port, Led_esq_Pin,SET);
				//velocidade_motor1(+PID_valor);
				//velocidade_motor2(-PID_valor);
				if (valor_posicao == 0) {
					/*if (vi_1 < 25) { //Velocidade_Final_Recebida) {
						vi_1++;
						vi_2++;
					}*/
					velocidade_motor1(vi_1);
					velocidade_motor2(vi_2);

				} else {
					velocidade_motor1(vi_1 + PID_valor);
					velocidade_motor2(vi_2 - PID_valor);
				}
				if (Direita >= 4) { //Direita_Recebida) {
					if (Encoder1 >= 25) { //Encoder1_Recebida) { //antigo = 25
						while (reset) {
							velocidade_motor1(0);
							velocidade_motor2(0);
							motor1_freio();
							motor2_freio();
							HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, SET);
							if (!Start) {
								power = 0;
								reset = 0;
								Direita = 0;
								Encoder1 = 0;
							}
						}
					}
				}
			}
			if (!Start) {
				reset = 1;
				Direita = 0;
				Encoder1 = 0;
				velocidade_motor1(0);
				velocidade_motor2(0);
				motor1_freio();
				motor2_freio();
				HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, SET);
			}
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_HSI14;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.HSI14CalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	/*if (!HAL_GPIO_ReadPin(Esq_GPIO_Port, Esq_Pin)) {
		if (!HAL_GPIO_ReadPin(Esq_GPIO_Port, Esq_Pin)) {
			int tempo = 3;
			unsigned int valorNovo = 0x0000;
			unsigned int valorAntigo = 0x0000;
			valorNovo = HAL_GPIO_ReadPin(Esq_GPIO_Port, Esq_Pin);
			HAL_GPIO_WritePin(Led_esq_GPIO_Port, Led_esq_Pin,RESET);
			if (valorAntigo == valorNovo) {
				tempo--;
			} else {
				tempo = 3;
				valorAntigo = valorNovo;
				HAL_GPIO_WritePin(Led_esq_GPIO_Port, Led_esq_Pin,SET);
			}
			if (tempo == 0) {
				Esquerda++;
				HAL_GPIO_WritePin(Led_esq_GPIO_Port, Led_esq_Pin,SET);
			}
		}
	}*/
	if (HAL_GPIO_ReadPin(start_GPIO_Port, start_Pin)) {
		power = 1;
	}
	if (!HAL_GPIO_ReadPin(Enc1_GPIO_Port, Enc1_Pin)) {
		if (Direita >= 4) { //Direita_Recebida) {
			Encoder1++;
		}
	}
	if (!HAL_GPIO_ReadPin(Dir_GPIO_Port, Dir_Pin)) {
		if (!HAL_GPIO_ReadPin(Dir_GPIO_Port, Dir_Pin)) {
			int tempo = 3;
			unsigned int valorNovo = 0x0000;
			unsigned int valorAntigo = 0x0000;
			valorNovo = HAL_GPIO_ReadPin(Dir_GPIO_Port, Dir_Pin);
			HAL_GPIO_WritePin(Led_dir_GPIO_Port, Led_dir_Pin,RESET);
			if (valorAntigo == valorNovo) {
				tempo--;
			} else {
				tempo = 3;
				valorAntigo = valorNovo;
				HAL_GPIO_WritePin(Led_dir_GPIO_Port, Led_dir_Pin,SET);
			}
			if (tempo == 0) {
				Direita++;
				HAL_GPIO_WritePin(Led_dir_GPIO_Port, Led_dir_Pin,SET);
			}

		}

	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(char *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
