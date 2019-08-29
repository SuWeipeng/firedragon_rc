#include "led.h"

static uint32_t last_tick;
LED_STATUS led_status = LED_ON;

void led_toggle(GPIO_TypeDef *led_port, uint16_t led_pin);

void update_led(LED_STATUS *status, GPIO_TypeDef *led_port, uint16_t led_pin)
{
  uint32_t tick = HAL_GetTick();
  if(status == NULL)
    return;
  switch( *status ){
    case LED_OFF:{
      HAL_GPIO_WritePin(led_port, led_pin, LED_TURN_OFF);
      break;
    }
    case LED_ON:{
      HAL_GPIO_WritePin(led_port, led_pin, LED_TURN_ON);
      break;
    }
    case LED_BLINK_1Hz:{
      if(tick - last_tick > 1000){
        led_toggle(led_port, led_pin);
        last_tick = tick;
      }
      break;
    }
    case LED_BLINK_3Hz:{
      if(tick - last_tick > 333){
        led_toggle(led_port, led_pin);
        last_tick = tick;
      }
      break;
    }
    case LED_BLINK_5Hz:{
      if(tick - last_tick > 200){
        led_toggle(led_port, led_pin);
        last_tick = tick;
      }
      break;
    }
  }
}

void led_toggle(GPIO_TypeDef *led_port, uint16_t led_pin)
{
  if(HAL_GPIO_ReadPin(led_port, led_pin) == GPIO_PIN_SET){
    HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_SET);
  }
}