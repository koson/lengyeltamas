#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

GPIO_InitTypeDef user_button_handle;

volatile int counter = 1;
volatile uint32_t previous_tick = 0;

void init_user_button()
														// Initializing user push button:
{
														// Enable clock for GPIO I port
__HAL_RCC_GPIOF_CLK_ENABLE();

														// Configure user_button_handle struct
user_button_handle.Pin = GPIO_PIN_8;
														// Set I port's 11th pin (board blue button)
user_button_handle.Pull = GPIO_NOPULL;
														// no pull-up resistor
user_button_handle.Speed = GPIO_SPEED_FAST;

user_button_handle.Mode = GPIO_MODE_IT_RISING;
														// IT = interrupt for the rising edge
														// user_button_handle.Alternate to be set only
														// when you use the pin for output (PWM)
														// You also need to modify the .Mode this case!

HAL_GPIO_Init(GPIOF, &user_button_handle);
														// Initializing GPIO I port for the user_button_handle struct

HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
														// Set priority for the EXTI lines 15:10, preempt priority 4, sub priority 0

HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
														// Enable interrupt for EXTI lines 15:10
}



int main()
{
	HAL_Init();
	BSP_LED_Init(LED_GREEN);
	init_user_button();

	while (1) {
	}
	return 0;
}

void EXTI9_5_IRQHandler()
													// the name of the function must come from the startup/startup_stm32f746xx.s file,
{
	HAL_GPIO_EXTI_IRQHandler(user_button_handle.Pin);
													// set PIN from the EXTI15_10 range, for the Interrupt handler
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
													// the name of the callback function comes from the Handler function's HAL_GPIO_EXTI_IRQHandler line's function
{
	if (GPIO_Pin == user_button_handle.Pin) {
													// Check if the function's input parameter PIN is the one we defined in the struct,
		uint32_t actual_tick = HAL_GetTick();
		uint32_t period_time = actual_tick - previous_tick;

		if (period_time < actual_tick && period_time > 250) {
			counter++;
			if (counter % 5 == 0 && (counter / 5) % 2 == 1){
				BSP_LED_On(LED_GREEN);
				} else if (counter % 5 == 0){
				BSP_LED_Off(LED_GREEN);
				}

			}
		previous_tick = actual_tick;
	}
}
