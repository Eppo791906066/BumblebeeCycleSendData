/**************************************************************************************************
  Filename:       wechatIOTService.h
  Revised:        $Date $
  Revision:       $Revision $

  Description:    This file contains the wechatIOT service definitions and
                  prototypes.

 Copyright 2011 - 2013 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef wechatServICE_H
#define wechatServICE_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "att.h"

/*********************************************************************
 * CONSTANTS
 */
// Service UUID
#define WECHAT_SERV_UUID                        0xFEE7

// Characteristics  UUID
#define WECHAT_WRITE_CHAR_UUID                  0xFEC7
#define WECHAT_INDICATE_CHAR_UUID               0xFEC8
#define WECHAT_READ_CHAR_UUID                   0xFEC9

// Status
#define STATUS_INDICATE_AUTH                0x00
#define STATUS_INDICATE_REAUTH              0x01
#define STATUS_INDICATE_INIT                0x02
#define STATUS_INDICATE_REINIT              0x03
#define STATUS_INDICATE_PUSH                0x04
#define STATUS_INDICATE_SENDDATA            0x05
#define STATUS_INDICATE_RESENDDATA          0x06

#define STATUS_INDICATE_FINISH              0xFF

//#define SW_BACKGROUND_DELAY_TIME            1000


// wechatIOT Service bit fields
#define WECHATIOT_SERVICE                   0x00000001

// Callback events
#define WECHATIOT_NOTI_ENABLED          1
#define WECHATIOT_NOTI_DISABLED         2

#define SEND_DATA_NONE                  0
#define SEND_DATA_RESEND                1
#define SEND_DATA_RESEND_SKIP           2
#define SEND_DATA_RESEND_PAUSE          3
#define SEND_DATA_SIM                   4
#define SEND_DATA_SIM_SKIP              5

//for Hal_Key
#define HAL_KEY_SW_6_BIT    BV(1)

#define HAL_KEY_SW_6_IEN      IEN1  // CPU interrupt mask register
#define HAL_KEY_SW_6_IENBIT   BV(5) // Mask bit for all of Port_0
#define HAL_KEY_SW_6_ICTL     P0IEN // Port Interrupt Control register
#define HAL_KEY_SW_6_ICTLBIT  BV(1) // P0IEN - P0.1 enable/disable bit
#define HAL_KEY_SW_6_PXIFG    P0IFG

#define HAL_KEY_JOY_MOVE_EDGEBIT  BV(3)
#define HAL_KEY_JOY_MOVE_BIT      BV(0)
#define HAL_KEY_JOY_MOVE_IEN      IEN2  // CPU interrupt mask register
#define HAL_KEY_JOY_MOVE_IENBIT   BV(1) // Mask bit for all of Port_2
#define HAL_KEY_JOY_MOVE_ICTL     P2IEN // Port Interrupt Control register
#define HAL_KEY_JOY_MOVE_ICTLBIT  BV(0) // P2IENL - P2.0<->P2.3 enable/disable bit
#define HAL_KEY_JOY_MOVE_PXIFG    P2IFG // Interrupt flag at source




#define HAL_JOYSTICK_INT_ENABLE()           st(HAL_KEY_JOY_MOVE_ICTL |= (HAL_KEY_JOY_MOVE_ICTLBIT);\
                                            HAL_KEY_JOY_MOVE_IEN |= HAL_KEY_JOY_MOVE_IENBIT;\
                                            HAL_KEY_JOY_MOVE_PXIFG &= ~(HAL_KEY_JOY_MOVE_BIT);)
#define HAL_JOYSTICK_INT_DISABLE()          st( HAL_KEY_JOY_MOVE_ICTL &= ~(HAL_KEY_JOY_MOVE_ICTLBIT);\
                                            HAL_KEY_JOY_MOVE_IEN &= ~(HAL_KEY_JOY_MOVE_IENBIT);\
                                            HAL_KEY_JOY_MOVE_PXIFG &= ~(HAL_KEY_JOY_MOVE_BIT); )

/*********************************************************************
 * TYPEDEFS
 */

// wechatIOT Service callback function
typedef void (*wechatServiceCB_t)(uint8 event);

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

/*********************************************************************
 * API FUNCTIONS
 */

/*
 * wechatIOT_AddService- Initializes the wechatIOT service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 */

extern bStatus_t wechatIOT_AddService( uint32 services );

/*
 * wechatIOT_Register - Register a callback function with the
 *          wechatIOT Service
 *
 * @param   pfnServiceCB - Callback function.
 */

extern void wechatIOT_Register( wechatServiceCB_t pfnServiceCB );

/*
 * wechatIOT_SetParameter - Set a wechatIOT parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t wechatIOT_SetParameter( uint8 param, uint8 len, void *value );

/*
 * wechatIOT_GetParameter - Get a wechatIOT parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t wechatIOT_GetParameter( uint8 param, void *value );

/*********************************************************************
 * @fn          wechat_sendIndicate
 *
 * @brief       Send a notification containing a wechatIOT
 *              measurement.
 *
 * @param       connHandle - connection handle
 * @param       pNoti - pointer to notification structure
 *
 * @return      Success or Failure
 */
extern bStatus_t wechat_sendIndicate( uint16 connHandle, attHandleValueInd_t *pNoti, uint8 taskId );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* wechatServICE_H */
