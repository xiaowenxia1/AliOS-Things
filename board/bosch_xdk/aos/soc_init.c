#include <stdio.h>
#include <stdint.h>
#include <hal/hal.h>
#include <k_config.h>
//#include <soc_init.h>

#include <em_chip.h>
#include <em_cmu.h>
#include <em_emu.h>
#include <em_gpio.h>
#include <em_device.h>
#include "BSP_BoardSettings.h"


#if defined (__CC_ARM) && defined(__MICROLIB)
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#elif defined(__ICCARM__)
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#else
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#endif /* defined (__CC_ARM) && defined(__MICROLIB) */



#define Key1Port  gpioPortE
#define Key1Pin   9

#define LedRedPort     gpioPortA
#define LedRedPin      12

#define LedYellowPort     gpioPortB
#define LedYellowPin      0

#define LedOrangePort     gpioPortB
#define LedOrangePin      1

uart_dev_t uart_0;
//i2c_dev_t brd_i2c0_dev = {0, {0}, NULL};

static void stduart_init(void)
{
    uart_0.port = 0;
    uart_0.config.baud_rate = 115200;
    uart_0.config.data_width = DATA_WIDTH_8BIT;
    uart_0.config.flow_control = FLOW_CONTROL_DISABLED;
    uart_0.config.mode = MODE_TX_RX;
    uart_0.config.parity = NO_PARITY;
    uart_0.config.stop_bits = STOP_BITS_1;

    hal_uart_init(&uart_0);
}

void board_sensor_init()
{
    GPIO_PinModeSet(VDD_BMA280_PORT, VDD_BMA280_PIN, VDD_BMA280_MODE, 1);

    GPIO_PinModeSet(VDD_BME280_PORT, VDD_BME280_PIN, VDD_BME280_MODE, 1);

    GPIO_PinModeSet(VDD_BMG160_PORT, VDD_BMG160_PIN, VDD_BMG160_MODE, 1);

    GPIO_PinModeSet(VDD_BMI160_PORT, VDD_BMI160_PIN, VDD_BMI160_MODE, 1);

    GPIO_PinModeSet(VDD_BMM150_PORT, VDD_BMM150_PIN, VDD_BMM150_MODE, 1);

    GPIO_PinModeSet(VDD_MAX44009_PORT, VDD_MAX44009_PIN, VDD_MAX44009_MODE, 1);

    GPIO_PinModeSet(BMA280_INT1_PORT, BMA280_INT1_PIN, BMA280_INT1_MODE, 1);
    GPIO_PinModeSet(BMA280_INT2_PORT, BMA280_INT2_PIN, BMA280_INT2_MODE, 1);

    GPIO_PinModeSet(BMG160_INT1_PORT, BMG160_INT1_PIN, BMG160_INT1_MODE, 1);
    GPIO_PinModeSet(BMG160_INT2_PORT, BMG160_INT2_PIN, BMG160_INT2_MODE, 1);

    GPIO_PinModeSet(BMI160_INT1_PORT, BMI160_INT1_PIN, BMI160_INT1_MODE, 1);
    GPIO_PinModeSet(BMI160_INT2_PORT, BMI160_INT2_PIN, BMI160_INT2_MODE, 1);

    GPIO_PinModeSet(BMM150_DRDY_PORT, BMM150_DRDY_PIN, BMM150_DRDY_MODE, 1);
    GPIO_PinModeSet(BMM150_INT_PORT, BMM150_INT_PIN, BMM150_INT_MODE, 1);

    GPIO_PinModeSet(MAX44009_INTN_PORT, MAX44009_INTN_PIN, MAX44009_INTN_MODE, 1);

}

void bsp_init()
{
    
    uint32_t param1 = 0;
    void* param2 = NULL;
    BSP_Board_Initialize(param1,param2);
}

void efm32_soc_init(void)
{
    CHIP_Init();

    CMU_ClockEnable(cmuClock_HFPER, true);

    SystemCoreClockUpdate();

   // SysTick_Config(SystemCoreClock/RHINO_CONFIG_TICKS_PER_SECOND);

    CMU_ClockEnable(cmuClock_GPIO, true);

    GPIO_PinModeSet(LedYellowPort, LedYellowPin,
                    gpioModePushPullDrive, 1);

    GPIO_PinModeSet(LedOrangePort, LedOrangePin,
                    gpioModePushPullDrive, 1);

    GPIO_PinModeSet(LedRedPort, LedRedPin,
                    gpioModePushPullDrive, 1);

    GPIO_PinOutSet(LedYellowPort, LedYellowPin);
    GPIO_PinOutSet(LedRedPort, LedRedPin);
    GPIO_PinOutClear(LedOrangePort, LedOrangePin);

    bsp_init();
    stduart_init();
    
    board_sensor_init();
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  if (ch == '\n') {
    //hal_uart_send(&console_uart, (void *)"\r", 1, 30000);
    hal_uart_send(&uart_0, (void *)"\r", 1, 30000);
  }
  hal_uart_send(&uart_0, &ch, 1, 30000);
  return ch;
}

/**
  * @brief  Retargets the C library scanf function to the USART.
  * @param  None
  * @retval None
  */
GETCHAR_PROTOTYPE
{
  /* Place your implementation of fgetc here */
  /* e.g. readwrite a character to the USART2 and Loop until the end of transmission */
  uint8_t ch = EOF;
  int32_t ret = -1;

  uint32_t recv_size;
  ret = hal_uart_recv_II(&uart_0, &ch, 1, &recv_size, HAL_WAIT_FOREVER);

  if (ret == 0) {
      return ch;
  } else {
      return -1;
  }
}


extern void Board_IncTick();
void SysTick_Handler(void)
{
    HAL_IncTick();
    krhino_intrpt_enter();
    krhino_tick_proc();
    krhino_intrpt_exit();
    Board_IncTick();
}


void HardFault_Handler(void)
{
    printf("hard fault !!!\r\n");

    while (1);
}
