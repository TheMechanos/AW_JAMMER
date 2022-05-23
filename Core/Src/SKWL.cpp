/*
 * SK13.cpp
 *
 *  Created on: Sep 13, 2021
 *      Author: skocz
 */

#include <SKWL.hpp>


extern "C" void send_char(char c)
{
	SKWL::getInstance()->logBuffor.push(c);
}
extern "C" int __io_putchar(int ch)
{
	send_char(ch);
	return ch;
}



SKWL SKWL::INSTANCE;
SKWL* SKWL::getInstance(){
	return &INSTANCE;
}

SKWL::SKWL(){

	pinLed[0] = PIN(GPIOC, GPIO_PIN_0);
		pinLed[1] = PIN(GPIOC, GPIO_PIN_1);
		pinLed[2] = PIN(GPIOB, GPIO_PIN_5);

		pinSw[0] = PIN(GPIOB, GPIO_PIN_6);
		pinSw[1] = PIN(GPIOB, GPIO_PIN_7);
		pinSw[2] = PIN(GPIOB, GPIO_PIN_3);

		pinRfSwTx = PIN(GPIOA, GPIO_PIN_5);
		pinRfSwRx = PIN(GPIOA, GPIO_PIN_4);



		led[0] = OUTPUT_ADVENCED(&pinLed[0]);
		led[1] = OUTPUT_ADVENCED(&pinLed[1]);
		led[2] = OUTPUT_ADVENCED(&pinLed[2]);

		button[0] = BUTTON_CLICK(&pinSw[0], 30);
		button[1] = BUTTON_CLICK(&pinSw[1], 30);
		button[2] = BUTTON_CLICK(&pinSw[2], 30);

		rfSwTx = OUTPUT_PIN(&pinRfSwTx);
		rfSwRx = OUTPUT_PIN(&pinRfSwRx);

		rfSw = RadioRFSwitch(&rfSwTx, &rfSwRx);

		sxRadio = SKMRadioSX126X(&subghz, &rfSw);

		radio = SKMController(&sxRadio);

}

void SKWL::init(){

	HAL_Init();

		//Dołączanie zegara do modułów GPIO
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();

		//Konfiguracja zegara systemowego
		SystemClock_Config();

		//CONFIG INTERRUPT GROUPING - 4 bits for preemption priority,  0 bits for subpriority
		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

		//Inicjalizacja switcha radiowego
		rfSwTx.init();
		rfSwRx.init();
		rfSw.init();


		led[0].init();
		led[1].init();
		led[2].init();

		button[0].init();
		button[1].init();
		button[2].init();


		//Inicjalizacja Radia
		__HAL_RCC_SUBGHZ_CLK_ENABLE();
		subghz.init();

		sxRadio.init();
		sxRadio.config(&sxExampleGFSK);

		radio.init();



}


void SKWL::iterateCritical(){


}

void SKWL::iterateNonCritical(){
	uint32_t TICK = System::getTick();
	led[0].iterate(TICK);
	led[1].iterate(TICK);
	led[2].iterate(TICK);

	button[0].iterate(TICK);
	button[1].iterate(TICK);
	button[2].iterate(TICK);

	radio.iterate();
}

void SKWL::SystemClock_Config(void) {
	SystemCoreClock = 48000000;

	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_PWR;
	RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
	RCC_OscInitStruct.PLL.PLLN = 12;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		System::SystemErrorHandler();
	}
	/** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
			| RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		System::SystemErrorHandler();
	}
}



//INTERRUPT SECTION ***********************************************************************************************************************

//SYS TICK INTERRUPT
extern "C" void HAL_SYSTICK_Callback(void){
	SKWL::getInstance()->iterateCritical();
}


//RADIO INTERRUPTS
extern "C" void HAL_SUBGHZ_TxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqTxCpltCallback();
}
extern "C" void HAL_SUBGHZ_RxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqRxCpltCallback();
}
extern "C" void HAL_SUBGHZ_PreambleDetectedCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqPreambleDetectedCallback();
}
extern "C" void HAL_SUBGHZ_SyncWordValidCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqSyncWordValidCallback();
}
extern "C" void HAL_SUBGHZ_HeaderValidCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqHeaderValidCallback();
}
extern "C" void HAL_SUBGHZ_HeaderErrorCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqHeaderErrorCallback();
}
extern "C" void HAL_SUBGHZ_CRCErrorCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqCRCErrorCallback();
}
extern "C" void HAL_SUBGHZ_CADStatusCallback(SUBGHZ_HandleTypeDef *hsubghz, HAL_SUBGHZ_CadStatusTypeDef cadstatus){
	SKWL::getInstance()->sxRadio.irqCADStatusCallback();
}
extern "C" void HAL_SUBGHZ_RxTxTimeoutCallback(SUBGHZ_HandleTypeDef *hsubghz){
	SKWL::getInstance()->sxRadio.irqRxTxTimeoutCallback();
}





/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
extern "C" void NMI_Handler(void) {
	while (1) {

	}

}

/**
 * @brief This function handles Hard fault interrupt.
 */
extern "C" void HardFault_Handler(void) {
	while (1) {

	}
}

/**
 * @brief This function handles Memory management fault.
 */
extern "C" void MemManage_Handler(void) {
	while (1) {

	}
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
extern "C" void BusFault_Handler(void) {
	while (1) {

	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
extern "C" void UsageFault_Handler(void) {
	while (1) {

	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
extern "C" void SVC_Handler(void) {

}

/**
 * @brief This function handles Debug monitor.
 */
extern "C" void DebugMon_Handler(void) {

}

/**
 * @brief This function handles Pendable request for system service.
 */
extern "C" void PendSV_Handler(void) {

}

/**
 * @brief This function handles System tick timer.
 */
extern "C" void SysTick_Handler(void) {

	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

/**
 * @brief This function handles SUBGHZ Radio Interrupt.
 */
extern "C" void SUBGHZ_Radio_IRQHandler(void) {
	HAL_SUBGHZ_IRQHandler(SKWL::getInstance()->subghz.getHandler());
}





