#include <AP_Math.h>
#include "usb_device.h"
#include "RC_Channel.h"

RC_Channel::RC_Channel(ADC_HandleTypeDef* hadc)
  : _hadc(hadc)
{
  HAL_ADC_Start_DMA(_hadc, _adc_buf, ADC_CHANNEL_CNT * ADC_CHANNEL_FRE);
}

void RC_Channel::adc_update(void)
{
  for(uint8_t i=0; i<ADC_CHANNEL_CNT; i++) {
    _adc_buf[i] = 0;
  }

  for(uint8_t i=0; i<ADC_CHANNEL_FRE; i++) {
    _adc_buf[0] +=  _adc_buf[i*ADC_CHANNEL_CNT+0];
    _adc_buf[1] +=  _adc_buf[i*ADC_CHANNEL_CNT+1];
    _adc_buf[2] +=  _adc_buf[i*ADC_CHANNEL_CNT+2];
    _adc_buf[3] +=  _adc_buf[i*ADC_CHANNEL_CNT+3];
  }

  for(uint8_t i=0; i<ADC_CHANNEL_CNT; i++) {
    _adc_buf[i] /=ADC_CHANNEL_FRE;
  }
}

uint32_t RC_Channel::get_value(uint8_t channel)
{
  if(channel > ADC_CHANNEL_CNT -1) return 0;

  return _adc_buf[channel];
}

float RC_Channel::vel_x(int8_t inv)
{

}

float RC_Channel::vel_y(int8_t inv)
{

}

float RC_Channel::rad_z(int8_t inv)
{
  float    ret = 0.0f;
  uint16_t min = 0;
  uint16_t mid = 1926;
  uint16_t max = 4010;
  uint16_t val = get_value(1);

  if(abs(val-mid) < ADC_DEAD_ZONE) return 0.0f;

  if(val > mid) {
    ret = (val-mid)*(0.7f/(max-mid));
  } else {
    ret = (val-mid)*(0.7f/(mid-min));
  }
  
  if(inv == -1) ret *= inv;
  
  char buffer[30];
  sprintf(buffer, "rad_z:%.2f\r\n", ret);
  VCPSend((uint8_t *)buffer, strlen(buffer));
  
  return ret;
}
