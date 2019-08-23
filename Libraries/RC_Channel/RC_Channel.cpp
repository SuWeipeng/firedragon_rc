#include <AP_Math.h>
#include "usb_device.h"
#include "RC_Channel.h"

RC_Channel::RC_Channel(ADC_HandleTypeDef* hadc)
  : _hadc(hadc)
{
  HAL_ADC_Start_DMA(_hadc, _adc_buf, ADC_BUFF_LEN);
}

uint32_t RC_Channel::get_value(uint8_t channel)
{
  if(channel > ADC_CHANNEL_CNT -1) return 0;
#if ADC_VCP_DEBUG == 2  
  char buffer[30];
  sprintf(buffer, "x:%d, y:%d, z:%d\r\n", _adc_buf[0], _adc_buf[2], _adc_buf[1]);
  VCPSend((uint8_t *)buffer, strlen(buffer));
#endif  
  return _adc_buf[channel];
}

float RC_Channel::vel_x(int8_t inv)
{
  float    ret = 0.0f;
  uint16_t min = 0;
  uint16_t mid = ADC_CHANNEL_X_MID;
  uint16_t max = ADC_CHANNEL_X_MAX;
  uint16_t val = get_value(0);

  if(abs(val-mid) < ADC_DEAD_ZONE) return 0.0f;

  if(val > mid) {
    ret = (val-mid)*(VEL_X_MAX_M_S/(max-mid));
  } else {
    ret = (val-mid)*(VEL_X_MAX_M_S/(mid-min));
  }
  
  if(inv == -1) ret *= inv;
  
#if ADC_VCP_DEBUG == 1  
  char buffer[30];
  sprintf(buffer, "vel_x:%.2f\r\n", ret);
  VCPSend((uint8_t *)buffer, strlen(buffer));
#endif 
  
  return constrain_float(ret, -VEL_X_MAX_M_S, VEL_X_MAX_M_S);
}

float RC_Channel::vel_y(int8_t inv)
{
  float    ret = 0.0f;
  uint16_t min = 0;
  uint16_t mid = ADC_CHANNEL_Y_MID;
  uint16_t max = ADC_CHANNEL_Y_MAX;
  uint16_t val = get_value(2);

  if(abs(val-mid) < ADC_DEAD_ZONE) return 0.0f;

  if(val > mid) {
    ret = (val-mid)*(VEL_Y_MAX_M_S/(max-mid));
  } else {
    ret = (val-mid)*(VEL_Y_MAX_M_S/(mid-min));
  }
  
  if(inv == -1) ret *= inv;
  
#if ADC_VCP_DEBUG == 1  
  char buffer[30];
  sprintf(buffer, "vel_y:%.2f\r\n", ret);
  VCPSend((uint8_t *)buffer, strlen(buffer));
#endif  
  
  return constrain_float(ret, -VEL_Y_MAX_M_S, VEL_Y_MAX_M_S);
}

float RC_Channel::rad_z(int8_t inv)
{
  float    ret = 0.0f;
  uint16_t min = 0;
  uint16_t mid = ADC_CHANNEL_Z_MID;
  uint16_t max = ADC_CHANNEL_Z_MAX;
  uint16_t val = get_value(1);

  if(abs(val-mid) < ADC_DEAD_ZONE) return 0.0f;

  if(val > mid) {
    ret = (val-mid)*(RAD_Z_MAX_RAD_S/(max-mid));
  } else {
    ret = (val-mid)*(RAD_Z_MAX_RAD_S/(mid-min));
  }
  
  if(inv == -1) ret *= inv;
  
#if ADC_VCP_DEBUG == 1  
  char buffer[30];
  sprintf(buffer, "rad_z:%.2f\r\n", ret);
  VCPSend((uint8_t *)buffer, strlen(buffer));
#endif 
  
  return constrain_float(ret, -RAD_Z_MAX_RAD_S, RAD_Z_MAX_RAD_S);
}
