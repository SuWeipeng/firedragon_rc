#ifndef __LED_H__
#define __LED_H__

#include <stm32f1xx_hal.h>

#define LED_TURN_ON  GPIO_PIN_RESET
#define LED_TURN_OFF GPIO_PIN_SET

typedef enum{
  LED_OFF,
  LED_ON,
  LED_BLINK_1Hz,
  LED_BLINK_3Hz,
  LED_BLINK_5Hz
}LED_STATUS;

void update_led(LED_STATUS *status, GPIO_TypeDef *led_port, uint16_t led_pin);

#endif
