#include "nrf_mavlink.h"
#include "led.h"
#include "RC_Channel.h"

extern ADC_HandleTypeDef hadc1;
extern vel_target vel;
extern LED_STATUS led_status;

RC_Channel* rc;

#if defined(__GNUC__) && defined(__cplusplus)
extern "C" {
#endif

void setup(void)
{
  rc = new RC_Channel(&hadc1);
}

void loop(void)
{
  vel.vel_x = rc->vel_x();
  vel.vel_y = rc->vel_y();
  vel.rad_z = rc->rad_z(-1);
  
  update_led(&led_status, GPIOB, GPIO_PIN_11 | GPIO_PIN_12);
}

#if defined(__GNUC__) && defined(__cplusplus)
}
#endif
