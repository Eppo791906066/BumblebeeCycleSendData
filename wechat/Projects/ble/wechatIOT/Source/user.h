#ifndef _userApp_h
#define _userApp_h

#ifdef __cplusplus
extern "C"
{
#endif
  
#define RecvDataEvt   0x0001

#define SEND_DATA_PERIOD_EVT  0x0002  
  
#define MagicCode               0xFECF
#define VERSION                 0x0001
#define OpenLightPush           0x2001
#define CloseLightPush          0x2002
#define LED                     P1_1
#define LED_ON                  1
#define LED_OFF                 0
  
  
void user_InitTask(uint8 taskId);
uint16 user_ProcessEvent(uint8 taskId, uint16 events);

#ifdef __cplusplus
extern "C"
}
#endif
  
#endif