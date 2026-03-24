/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <stdlib.h>

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void StartCustomTask0(void const *argument);
void StartCustomTask1(void const *argument);
void StartCustomTask2(void const *argument);
void StartCustomTask3(void const *argument);
void StartCustomTask4(void const *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationTickHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook(void) {
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
	 task. It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()). If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
__weak void vApplicationTickHook(void) {
	/* This function will be called by each tick interrupt if
	 configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
	 added here, but the tick hook is called from an interrupt context, so
	 code must not attempt to block, and only the interrupt safe FreeRTOS API
	 functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask,
		signed char *pcTaskName) {
	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
	 called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	BaseType_t xReturned;
	TaskHandle_t *customTaskHandle = (TaskHandle_t *)pvPortMalloc(5 * sizeof(TaskHandle_t));
	if(customTaskHandle == NULL){
		while(1);
	}

	xReturned = xTaskCreate((TaskFunction_t) StartCustomTask1, "c1",
	configMINIMAL_STACK_SIZE,
	NULL, 5, &customTaskHandle[1]);
	if (xReturned != pdPASS) {
		vTaskDelete(customTaskHandle[1]);
	}

	xReturned = xTaskCreate((TaskFunction_t) StartCustomTask2, "c2",
	configMINIMAL_STACK_SIZE,
	NULL, 5, &customTaskHandle[2]);
	if (xReturned != pdPASS) {
		vTaskDelete(customTaskHandle[2]);
	}

	xReturned = xTaskCreate((TaskFunction_t) StartCustomTask3, "c3",
	configMINIMAL_STACK_SIZE,
	NULL, 5, &customTaskHandle[3]);
	if (xReturned != pdPASS) {
		vTaskDelete(customTaskHandle[3]);
	}

	xReturned = xTaskCreate((TaskFunction_t) StartCustomTask4, "c4",
	configMINIMAL_STACK_SIZE,
	NULL, 5, &customTaskHandle[4]);
	if (xReturned != pdPASS) {
		vTaskDelete(customTaskHandle[4]);
	}

	xReturned = xTaskCreate((TaskFunction_t) StartCustomTask0, "c0",
	configMINIMAL_STACK_SIZE, customTaskHandle, 5, &customTaskHandle[0]);
	if (xReturned != pdPASS) {
		vTaskDelete(customTaskHandle[0]);
	}

	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument) {
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
//		osDelay(200);
//		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	}
	/* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void StartCustomTask0(void const *argument) {
	int j = 0, k = 0;
	int flag[4] = {0};
	TaskHandle_t *customTaskHandle = (TaskHandle_t *)argument;
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		k = rand() % 4;
		j = rand() % 10000 + 1;

		if(flag[k] == 1){
			vTaskSuspend(customTaskHandle[k+1]);
			flag[k] = 0;
		}
		else{
			vTaskResume(customTaskHandle[k+1]);
			flag[k] = 1;
		}

		printf("%d, %d \r\n", j, k);
		vTaskDelayUntil(&xLastWakeTime, j);
	}
}

void StartCustomTask1(void const *argument) {
	for (;;) {
		osDelay(400);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	}
}

void StartCustomTask2(void const *argument) {
	for (;;) {
		osDelay(600);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
}

void StartCustomTask3(void const *argument) {
	for (;;) {
		osDelay(800);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	}
}

void StartCustomTask4(void const *argument) {
	for (;;) {
		osDelay(1600);
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	}
}

/* USER CODE END Application */
