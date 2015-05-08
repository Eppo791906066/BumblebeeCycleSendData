#ifndef WECHATIOT_H
#define WECHATIOT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
/*********************************************************************
 * MACROS
 */
#define WECHATIOT_START_DEVICE_EVT                              0x0001
#define TIMER_WECHATIOT_INDICATE_EVT                            0x0002   
   

/*wechatIOT Service callback function*/
typedef void (*WechatCB_t)(uint32 event);  


/*********************************************************************
 * FUNCTIONS
 */

 /*********************************************************************


 /*********************************************************************
 * @fn      wechatIOT_Init
 *
 * @brief   AirSync协议任务初始化函数
 *
 * @param   task_id - 任务号
 *
 * @return  N/A
 */
extern void wechatIOT_Init( uint8 task_id );

 /*********************************************************************
 * @fn      wechatIOT_ProcessEvent
 *
 * @brief   AirSync事件处理函数
 *
 * @param   task_id - 任务号
 * @param   events - 事件
 *
 * @return  未处理事件
 */
extern uint16 wechatIOT_ProcessEvent( uint8 task_id, uint16 events );


 /*********************************************************************
 * @fn      WechatCB_Register
 *
 * @brief   微信服务回调函数注册
 *
 * @param   pfnServiceCB - 回调函数指针
 *
 * @return  N/A
 */
extern void WechatCB_Register( WechatCB_t pfnServiceCB );

 /*********************************************************************
 * @fn      SendDataToWechat
 *
 * @brief   发送数据给微信
 *
 * @param   buf - 要发送的数据源
 * @param   len - 要发送数据源长度
 *
 * @return  0    成功
 *          -1   发送数据长度过长
 *          -2   蓝牙未连接
 */
extern int8 SendDataToWechat(uint8 *buf,uint8 len);

 /*********************************************************************
 * @fn      GetWechatData
 *
 * @brief   获得微信的数据
 *
 * @param   pBuf - 存放数据的地方
 * @param   len -  要读取的长度
 *
 * @return  读到的字节数
 */
extern uint16  GetWechatData(uint8 *pBuf, uint16 len);

/*********************************************************************
 * @fn      GetDataSize
 *
 * @brief   获取数据缓冲区的数据长度
 *
 * @return  数据长度  
 */
extern uint16 GetDataSize(void);
/*********************************************************************
 * @fn      SendDataToRecvPool
 *
 * @brief   把数据放到缓存
 *
 * @param   pData - 数据源
 * @param   len -  长度
 *
 * @return  
 */
uint16 SendDataToRecvPool(uint8 *pData, uint16 len);



extern void wechatIOT_BLE_Device_Init(void);

extern void wechatIOT_BLE_Device_Close(void);

extern void wechatIOT_BLE_Device_SendData(void);

extern void wechatIOT_BLE_Device_ReSendData(void);

extern void wechatIOT_Close_Device_SetAvertising(void);

extern void wechat_IndicateEventTimeDelaySet(uint16 u16DelayTime);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /*WECHATIOT_H */
