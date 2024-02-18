/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
 * 1桁 表示は「8」
 18V 0.54W 30mA
 */

uint8_t segmentPatterns[16] = {
		0x3F, // 0: 0111111
		0x06, // 1: 0000110
		0x5B, // 2: 1011011
		0x4F, // 3: 1001111
		0x66, // 4: 1100110
		0x6D, // 5: 1101101
		0x7D, // 6: 1111101
		0x07, // 7: 0000111
		0x7F, // 8: 1111111
		0x6F, // 9: 1101111
		0x77, // A: 1110111
		0x7C, // B: 1111100
		0x39, // C: 0111001
		0x5E, // D: 1011110
		0x79, // E: 1111001
		0x71  // F: 1110001
};
void litBit(uint8_t data){
	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG_DP_GPIO_Port, SEG_DP_Pin, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void displayNumber(uint8_t number){
	if (0 <= number && number <= 0x0F){
		litBit(segmentPatterns[number]);
	}
}

void enableDigit(uint8_t digit){
	switch(digit){
	case 0:
		HAL_GPIO_WritePin(GRID1_GPIO_Port, GRID1_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GRID2_GPIO_Port, GRID2_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GRID3_GPIO_Port, GRID3_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GRID4_GPIO_Port, GRID4_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(GRID5_GPIO_Port, GRID5_Pin, GPIO_PIN_SET);
		break;
	case 5:
		HAL_GPIO_WritePin(GRID6_GPIO_Port, GRID6_Pin, GPIO_PIN_SET);
		break;
	}
}

void disableAllDigit(){
	HAL_GPIO_WritePin(GRID1_GPIO_Port, GRID1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRID2_GPIO_Port, GRID2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRID3_GPIO_Port, GRID3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRID4_GPIO_Port, GRID4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRID5_GPIO_Port, GRID5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRID6_GPIO_Port, GRID6_Pin, GPIO_PIN_RESET);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
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
	MX_I2C1_Init();
	MX_RTC_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	uint8_t ct = 0;
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BCD);

		disableAllDigit();
		enableDigit(0);
		displayNumber(gTime.Seconds % 10);
		HAL_Delay(1);
		disableAllDigit();
		enableDigit(1);
		displayNumber(gTime.Seconds / 10);
		HAL_Delay(1);


		disableAllDigit();
		enableDigit(2);
		displayNumber(gTime.Minutes % 10);
		HAL_Delay(1);
		disableAllDigit();
		enableDigit(3);
		displayNumber(gTime.Minutes / 10);
		HAL_Delay(1);

		disableAllDigit();
		enableDigit(4);
		displayNumber(gTime.Hours % 10);
		HAL_Delay(1);
		disableAllDigit();
		enableDigit(5);
		displayNumber(gTime.Hours / 10);
		HAL_Delay(1);


		//			printf("Current time is %02d:%02d:%02d\n", gTime.Hours, gTime.Minutes, gTime.Seconds);


	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}

	/** Enable MSI Auto calibration
	 */
	HAL_RCCEx_EnableMSIPLLMode();
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00000E14;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void)
{

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */
#define MAGIC_NO 0x1200

	if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != MAGIC_NO)
	{
		RTC_TimeTypeDef sTime = {0};
		RTC_DateTypeDef sDate = {0};

		sTime.Hours = 14;
		sTime.Minutes = 41;
		sTime.Seconds = 40;
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
		sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
		sDate.Month = RTC_MONTH_FEBRUARY;
		sDate.Date = 18;
		sDate.Year = 24;
		if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();

		}
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, MAGIC_NO);
	}
	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
			|SEG_E_Pin|SEG_F_Pin|SEG_G_Pin|SEG_DP_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, SEG_MINUS_Pin|LED_Pin|GRID6_Pin|GRID5_Pin
			|GRID4_Pin|GRID3_Pin|GRID2_Pin|GRID1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : SEG_A_Pin SEG_B_Pin SEG_C_Pin SEG_D_Pin
                           SEG_E_Pin SEG_F_Pin SEG_G_Pin SEG_DP_Pin */
	GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
			|SEG_E_Pin|SEG_F_Pin|SEG_G_Pin|SEG_DP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : SEG_MINUS_Pin LED_Pin GRID6_Pin GRID5_Pin
                           GRID4_Pin GRID3_Pin GRID2_Pin GRID1_Pin */
	GPIO_InitStruct.Pin = SEG_MINUS_Pin|LED_Pin|GRID6_Pin|GRID5_Pin
			|GRID4_Pin|GRID3_Pin|GRID2_Pin|GRID1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
