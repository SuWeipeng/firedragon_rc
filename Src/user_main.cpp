#include "RC_Channel.h"

extern ADC_HandleTypeDef hadc1;

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
  rc->vel_x();
  rc->vel_y();
  rc->rad_z(-1);
}

#if defined(__GNUC__) && defined(__cplusplus)
}
#endif
