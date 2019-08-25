#ifndef __RC_CHANNEL__
#define __RC_CHANNEL__

#include <stm32f1xx_hal.h>

#define ADC_CHANNEL_CNT 4
#define ADC_BUFF_LEN    ADC_CHANNEL_CNT*2
#define ADC_DEAD_ZONE   300
#define ADC_VCP_DEBUG   1

#define ADC_CHANNEL_X_MID 1970
#define ADC_CHANNEL_Y_MID 1920
#define ADC_CHANNEL_Z_MID 1980
#define ADC_CHANNEL_X_MAX 4032
#define ADC_CHANNEL_Y_MAX 3873
#define ADC_CHANNEL_Z_MAX 3807

#define VEL_X_MAX_M_S   0.0685f
#define VEL_Y_MAX_M_S   0.0685f
#define RAD_Z_MAX_RAD_S 0.82f

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
  uint32_t           _adc_buf[ADC_BUFF_LEN];
};

#endif /* __RC_CHANNEL__ */
