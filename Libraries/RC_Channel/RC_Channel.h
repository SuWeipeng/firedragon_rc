#ifndef __RC_CHANNEL__
#define __RC_CHANNEL__

#include <stm32f1xx_hal.h>

#define ADC_CHANNEL_CNT 4
#define ADC_CHANNEL_FRE 100
#define ADC_DEAD_ZONE   50

class RC_Channel
{
public:
  RC_Channel(ADC_HandleTypeDef* hadc);
  ~RC_Channel() {}
  
  void     adc_update(void);
  uint32_t get_value(uint8_t channel);
  float    vel_x(int8_t inv = 1);
  float    vel_y(int8_t inv = 1);
  float    rad_z(int8_t inv = 1);
  
private:
  ADC_HandleTypeDef* _hadc;
  uint32_t _adc_buf[ADC_CHANNEL_CNT * ADC_CHANNEL_FRE];
};

#endif /* __RC_CHANNEL__ */
