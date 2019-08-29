#include "nrf_mavlink.h"
#include "MY_NRF24.h"
#include "usb_device.h"
#include "led.h"

#define _ABS_(x) (((x)>0) ? x : -x)
#define GET_BIT(value, i) ((value)>>i)

extern LED_STATUS led_status;

static uint32_t last_timestamp;

char myRxData[50];
char myAckPayload[32] = "Ack by firedragon_rc";

vel_target vel;

void update_mavlink(void)
{
  uint32_t timestamp = HAL_GetTick();
  
  if(_ABS_(timestamp - last_timestamp) > 500){
    led_status = LED_ON;
  } 
  
  if(NRF24_available()) {
    NRF24_read(myRxData, 32);
    uint8_t i;
    mavlink_message_t msg_receive;
    mavlink_status_t mav_status;
    for(i=0; i<32; i++) {
      if(mavlink_parse_char(0, myRxData[i], &msg_receive, &mav_status)) {
        
        last_timestamp = timestamp;
        
        switch (msg_receive.msgid) {

        case MAVLINK_MSG_ID_SIMPLE: {
          mavlink_simple_t packet;
          mavlink_msg_simple_decode(&msg_receive, &packet);

          char buffer[32];
          sprintf(buffer, "%d\r\n", packet.data);
          VCPSend((uint8_t *)buffer, strlen(buffer));
          uint8_t temp = GET_BIT(packet.data&0x80, 7);
          if(temp == 1){
            led_status = LED_BLINK_5Hz;
          }else{
            led_status = LED_OFF;
          }

          mavlink_message_t msg_ack;
          mavlink_msg_velocity_pack(0, 0, &msg_ack, vel.vel_x, vel.vel_y, vel.rad_z);
          int len = mavlink_msg_to_send_buffer((uint8_t *)myAckPayload, &msg_ack);
          NRF24_writeAckPayload(1, myAckPayload, len);
          break;
        }
        }
      }
    }
  }
}
