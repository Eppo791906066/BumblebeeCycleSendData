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
 * @brief   AirSyncЭ�������ʼ������
 *
 * @param   task_id - �����
 *
 * @return  N/A
 */
extern void wechatIOT_Init( uint8 task_id );

 /*********************************************************************
 * @fn      wechatIOT_ProcessEvent
 *
 * @brief   AirSync�¼�������
 *
 * @param   task_id - �����
 * @param   events - �¼�
 *
 * @return  δ�����¼�
 */
extern uint16 wechatIOT_ProcessEvent( uint8 task_id, uint16 events );


 /*********************************************************************
 * @fn      WechatCB_Register
 *
 * @brief   ΢�ŷ���ص�����ע��
 *
 * @param   pfnServiceCB - �ص�����ָ��
 *
 * @return  N/A
 */
extern void WechatCB_Register( WechatCB_t pfnServiceCB );

 /*********************************************************************
 * @fn      SendDataToWechat
 *
 * @brief   �������ݸ�΢��
 *
 * @param   buf - Ҫ���͵�����Դ
 * @param   len - Ҫ��������Դ����
 *
 * @return  0    �ɹ�
 *          -1   �������ݳ��ȹ���
 *          -2   ����δ����
 */
extern int8 SendDataToWechat(uint8 *buf,uint8 len);

 /*********************************************************************
 * @fn      GetWechatData
 *
 * @brief   ���΢�ŵ�����
 *
 * @param   pBuf - ������ݵĵط�
 * @param   len -  Ҫ��ȡ�ĳ���
 *
 * @return  �������ֽ���
 */
extern uint16  GetWechatData(uint8 *pBuf, uint16 len);

/*********************************************************************
 * @fn      GetDataSize
 *
 * @brief   ��ȡ���ݻ����������ݳ���
 *
 * @return  ���ݳ���  
 */
extern uint16 GetDataSize(void);
/*********************************************************************
 * @fn      SendDataToRecvPool
 *
 * @brief   �����ݷŵ�����
 *
 * @param   pData - ����Դ
 * @param   len -  ����
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
