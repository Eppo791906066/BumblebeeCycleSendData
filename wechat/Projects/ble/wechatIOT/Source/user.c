#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
#include "OnBoard.h"
#include "ll.h"
#include "hci.h"
#include "gap.h"
#include "peripheral.h"
#include "hal_uart.h"
#include "wechatIOT.h"
#include "epb_MmBp.h"
#include "user.h"
#include "hal_key.h"

static void WechatCallBackFunc(uint32 event);
static void user_HandleKeys( uint8 shift, uint8 keys );
static void user_ProcessOSALMsg( osal_event_hdr_t *pMsg );

uint8 user_TaskId;

static void WechatCallBackFunc(uint32 event)
{
    switch(event)
    {
      //微信登陆与初始化完毕，可以开始正常发送数据
      case ECI_resp_init:                      
        osal_set_event(user_TaskId,SEND_DATA_PERIOD_EVT);
        break;
      //微信有数据到来，开启读数据事件  
      case ECI_push_manufacturerSvrSendData:  
          osal_set_event(user_TaskId,RecvDataEvt);
        break;    
      //微信进入后台
      case ECI_push_switchBackgroud:
        break;
        
      default :
        break;
    }
}

static void user_ProcessOSALMsg( osal_event_hdr_t *pMsg )
{
  switch ( pMsg->event )
  {
  case KEY_CHANGE:
      user_HandleKeys( ((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys );
      break;
  default:
      break;
  }
}

/*********************************************************************
 * @fn      user_HandleKeys
 *
 * @brief   处理按键事件
 *
 * @param   shift - true if in shift/alt.
 * @param   keys - bit field for key events. Valid entries:
 *                 HAL_KEY_SW_2
 *                 HAL_KEY_SW_1
 *
 * @return  none
 */
static void user_HandleKeys( uint8 shift, uint8 keys )
{
   if (keys & HAL_KEY_SW_1) 
   {
      SendDataToWechat("K1 Pressed",osal_strlen("K1 Pressed"));
   }

   if ( keys & HAL_KEY_SW_2 )
   {
      SendDataToWechat("K2 Pressed",osal_strlen("K2 Pressed"));
   }
}

/*********************************************************************
 * @fn      user_InitTask
 *
 * @brief   应用初始化函数
 *
 * @param   taskId - 任务号
 *
 * @return  none
 */
//   //测试地址

void user_InitTask(uint8 taskId)
{
    uint8 btAddr[] = {0x45,0xF8,0x29,0x16,0x4A,0x54};
    HCI_EXT_SetBDADDRCmd(btAddr);

   
    //分配任务号
    user_TaskId = taskId;
    
    //注册数据回调函数
    WechatCB_Register(WechatCallBackFunc);
    
    //注册按键回调
    RegisterForKeys(user_TaskId);
}

/*********************************************************************
 * @fn      user_ProcessEvent
 *
 * @brief   应用初始化函数
 *
 * @param   taskId - 任务号
 * @param   events - 事件
 *
 * @return  none
 */
uint16 user_ProcessEvent(uint8 taskId, uint16 events)
{
   if (events & SEND_DATA_PERIOD_EVT)
   {
         //发送数据
         SendDataToWechat("Hello",osal_strlen("Hello"));
         //2秒后重新执行
         osal_start_timerEx(user_TaskId,SEND_DATA_PERIOD_EVT,2000);
         
         return (events ^ SEND_DATA_PERIOD_EVT);
   }
    
    if ( events & SYS_EVENT_MSG )
    {
        uint8 *pMsg;
        if ( (pMsg = osal_msg_receive( user_TaskId )) != NULL )
        {
            user_ProcessOSALMsg( (osal_event_hdr_t *)pMsg );

            VOID osal_msg_deallocate( pMsg );
        }

        return (events ^ SYS_EVENT_MSG);
    }
    
    if (events & RecvDataEvt)
    {
         uint8 buf[32];
         uint8 len  = GetDataSize();
   
         if (len>32)
         {
            len = 32;
         }
         
         GetWechatData(buf,len);
        if(buf[0]==((MagicCode>>8)&0xff) && buf[1]==(MagicCode&0xff)) //magic
        {
              if (buf[2]==((VERSION>>8)&0xff) && buf[3]==(VERSION&0xff)) //version
              {
                  if (buf[6]==((OpenLightPush>>8)&0xff) && buf[7]==(OpenLightPush&0xff))
                  {
                        LED = LED_ON;//openLightPush
                  }
                  else if (buf[6]==((CloseLightPush>>8)&0xff) && buf[7]==(CloseLightPush&0xff))
                  {
                      LED = LED_OFF;//closeLightPush
                  }
              }
         }
        return (events ^ RecvDataEvt);
    }
    
  return 0;
}


