/**************************************************************************************************
  Filename:       simpleGATTprofile.c
  Revised:        $Date: 2013-05-06 13:33:47 -0700 (Mon, 06 May 2013) $
  Revision:       $Revision: 34153 $

  Description:    This file contains the Simple GATT profile sample GATT service
                  profile for use with the BLE sample application.

  Copyright 2010 - 2013 Texas Instruments Incorporated. All rights reserved.

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

/*********************************************************************
 * INCLUDES
 */
#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"

#include "simpleGATTprofile.h"
#ifdef UART_DEBUG
#include "hal_uart.h"
#endif

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED        17

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
// Simple GATT Profile Service UUID: 0xFFF0
CONST uint8 simpleProfileServUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_SERV_UUID), HI_UINT16(SIMPLEPROFILE_SERV_UUID)
};

// Characteristic 1 UUID: 0xFFC7
CONST uint8 simpleProfilechar1UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_WRITE_CHAR_UUID), HI_UINT16(SIMPLEPROFILE_WRITE_CHAR_UUID)
};

// Characteristic 2 UUID: 0xFFC8
CONST uint8 simpleProfilechar2UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_INDICATE_CHAR_UUID), HI_UINT16(SIMPLEPROFILE_INDICATE_CHAR_UUID)
};


// Characteristic 5 UUID: 0xFFC9
CONST uint8 simpleProfilechar5UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(SIMPLEPROFILE_READ_CHAR_UUID), HI_UINT16(SIMPLEPROFILE_READ_CHAR_UUID)
};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static simpleProfileCBs_t *simpleProfile_AppCBs;

/*********************************************************************
 * Profile Attributes - variables
 */

// Simple Profile Service attribute
static CONST gattAttrType_t simpleProfileService = { ATT_BT_UUID_SIZE, simpleProfileServUUID };


// Simple Profile Characteristic 1 Properties
static uint8 simpleProfileChar1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 1 Value
static uint8 simpleProfileChar1 = 0;

// Simple Profile Characteristic 1 User Description
static uint8 simpleProfileChar1UserDesp[21] = "Write Characteristic\0";


// Simple Profile Characteristic 2 Properties
static uint8 simpleProfileChar2Props = GATT_PROP_INDICATE;

// Characteristic 2 Value
static uint8 simpleProfileChar2[SIMPLEPROFILE_INDICATE_CHAR_LEN] = { 0 , 1 , 2 , 3 , 4 ,\
                                                                     5 , 6 , 7 , 8 , 9 ,\
                                                                     10, 11, 12, 13, 14,\
                                                                     15, 16, 17, 18, 19 };
//(Add)Abellee 20140716 wechat need
static gattCharCfg_t simpleProfileChar2Config[GATT_MAX_NUM_CONN];
// Simple Profile Characteristic 2 User Description
static uint8 simpleProfileChar2UserDesp[24] = "Indicate Characteristic\0";


// Simple Profile Characteristic 5 Properties
static uint8 simpleProfileChar5Props = GATT_PROP_READ;

// Characteristic 5 Value
static uint8 simpleProfileChar5[SIMPLEPROFILE_READ_CHAR_LEN] = { 0, 0, 0, 0, 0 };

// Simple Profile Characteristic 5 User Description
static uint8 simpleProfileChar5UserDesp[20] = "Read Characteristic\0";


/*********************************************************************
 * Profile Attributes - Table
 */
#define SIMPLE_SERVICE      0
#define SIMPLE_CHAR1_DEC    1
#define SIMPLE_CHAR1_VAL    2
#define SIMPLE_CHAR1_DES    3
#define SIMPLE_CHAR2_DEC    4
#define SIMPLE_CHAR2_VAL    5
#define SIMPLE_CHAR2_DES    6
#define SIMPLE_CHAR2_CFG    7
#define SIMPLE_CHAR5_DEC    8
#define SIMPLE_CHAR5_VAL    9
#define SIMPLE_CHAR5_DES    10

static gattAttribute_t simpleProfileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] =
{
  // Simple Profile Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&simpleProfileService            /* pValue */
  },

    // Characteristic 1 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &simpleProfileChar1Props
    },

      // Characteristic Value 1
      {
        { ATT_BT_UUID_SIZE, simpleProfilechar1UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &simpleProfileChar1
      },

      // Characteristic 1 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        simpleProfileChar1UserDesp
      },

    // Characteristic 2 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &simpleProfileChar2Props
    },

      // Characteristic Value 2
      {
        { ATT_BT_UUID_SIZE, simpleProfilechar2UUID },
        GATT_PERMIT_READ, //0,//return READ_NOT_PERMITTED
        0,
        &simpleProfileChar2[0]
      },

      // Characteristic 2 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        simpleProfileChar2UserDesp
      },
      // Characteristic 2 Configuration //(Add)Abellee 20140716 wechat need
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&simpleProfileChar2Config
      },

    // Characteristic 5 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &simpleProfileChar5Props
    },

      // Characteristic Value 5
      {
        { ATT_BT_UUID_SIZE, simpleProfilechar5UUID },
        GATT_PERMIT_READ,
        0,
        simpleProfileChar5
      },

      // Characteristic 5 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        simpleProfileChar5UserDesp
      },


};


/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8 simpleProfile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen );
static bStatus_t simpleProfile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset );

static void simpleProfile_HandleConnStatusCB( uint16 connHandle, uint8 changeType );


/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t simpleProfileCBs =
{
  simpleProfile_ReadAttrCB,  // Read callback function pointer
  simpleProfile_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};



/*********************************************************************
 * PUBLIC FUNCTIONS
 */
uint8 u8_SimpleIndicateFlag;
/*********************************************************************
 * @fn      SimpleProfile_AddService
 *
 * @brief   Initializes the Simple Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t SimpleProfile_AddService( uint32 services )
{
  uint8 status = SUCCESS;

  u8_SimpleIndicateFlag =0;
  // Register with Link DB to receive link status change callback
  VOID linkDB_Register( simpleProfile_HandleConnStatusCB );
  GATTServApp_InitCharCfg( INVALID_CONNHANDLE, simpleProfileChar2Config );
  if ( services & SIMPLEPROFILE_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( simpleProfileAttrTbl,
                                          GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                          &simpleProfileCBs );
  }

  return ( status );
}


/*********************************************************************
 * @fn      SimpleProfile_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t SimpleProfile_RegisterAppCBs( simpleProfileCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    simpleProfile_AppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}


/*********************************************************************
 * @fn      SimpleProfile_SetParameter
 *
 * @brief   Set a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t SimpleProfile_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  #ifdef UART_DEBUG
  print_msg("SetParameter = 0x%X \r\n",param);
  #endif
  switch ( param )
  {
    case SIMPLEPROFILE_CHAR1:
      if ( len == sizeof ( uint8 ) )
      {
        simpleProfileChar1 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case SIMPLEPROFILE_CHAR2:
      if ( len == SIMPLEPROFILE_INDICATE_CHAR_LEN )
      {
        VOID osal_memcpy( simpleProfileChar2, value, SIMPLEPROFILE_INDICATE_CHAR_LEN );
        // See if Notification has been enabled
        GATTServApp_ProcessCharCfg( simpleProfileChar2Config, simpleProfileChar2, FALSE,
                                         simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ),
                                         INVALID_TASK_ID );

      }
      else
      {
        ret = bleInvalidRange;
      }
      break;


    case SIMPLEPROFILE_CHAR5:
      if ( len == SIMPLEPROFILE_READ_CHAR_LEN )
      {
        VOID osal_memcpy( simpleProfileChar5, value, SIMPLEPROFILE_READ_CHAR_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn      SimpleProfile_GetParameter
 *
 * @brief   Get a Simple Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t SimpleProfile_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  #ifdef UART_DEBUG
  print_msg("GetParameter = 0x%X \r\n",param);
  #endif
  switch ( param )
  {
    case SIMPLEPROFILE_CHAR1:
      *((uint8*)value) = simpleProfileChar1;
      break;

    case SIMPLEPROFILE_CHAR2:
      VOID osal_memcpy( value, simpleProfileChar2, SIMPLEPROFILE_INDICATE_CHAR_LEN );
      break;

    case SIMPLEPROFILE_CHAR5:
      VOID osal_memcpy( value, simpleProfileChar5, SIMPLEPROFILE_READ_CHAR_LEN );
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn          simpleProfile_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 *
 * @return      Success or Failure
 */
static uint8 simpleProfile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen )
{
  bStatus_t status = SUCCESS;

  // If attribute permissions require authorization to read, return error
  if ( gattPermitAuthorRead( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);

    #ifdef UART_DEBUG
    print_msg("ReadAttrCB uuid = 0x%X \r\n",uuid);
    #endif
    switch ( uuid )
    {
      // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
      // gattserverapp handles those reads

      // characteristics 1 and 2 have read permissions
      // characteritisc 3 does not have read permissions; therefore it is not
      //   included here
      // characteristic 4 does not have read permissions, but because it
      //   can be sent as a notification, it is included here
      case SIMPLEPROFILE_WRITE_CHAR_UUID:
        *pLen = 1;
        pValue[0] = *pAttr->pValue;
        break;
      case SIMPLEPROFILE_INDICATE_CHAR_UUID:
        *pLen = SIMPLEPROFILE_INDICATE_CHAR_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, SIMPLEPROFILE_INDICATE_CHAR_LEN );
        break;

      case SIMPLEPROFILE_READ_CHAR_UUID:
        *pLen = SIMPLEPROFILE_READ_CHAR_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, SIMPLEPROFILE_READ_CHAR_LEN );
        break;
      case GATT_CLIENT_CHAR_CFG_UUID:
      {
        #ifdef UART_DEBUG
        print_msg("GATT_CLIENT_CHAR_CFG_UUID = 0x%X \r\n",pAttr->handle);
        #endif
        // Read Measurement or Command Configuration
        if ( pAttr->handle == simpleProfileAttrTbl[SIMPLE_CHAR2_DEC].handle  )
        {

          *pLen = 1;
          pValue[0] = *pAttr->pValue;

          // Set the handle
          //pNoti->handle = simpleProfileAttrTbl[SIMPLE_CHAR2_DEC].handle;


        }
        else
        {
          status = ATT_ERR_ATTR_NOT_FOUND;
        }
      }
      break;

      default:
        // Should never get here! (characteristics 3 and 4 do not have read permissions)
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      simpleProfile_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 *
 * @return  Success or Failure
 */
static bStatus_t simpleProfile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset )
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  // If attribute permissions require authorization to write, return error
  if ( gattPermitAuthorWrite( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    #ifdef UART_DEBUG
    print_msg("WriteAttrCB uuid = 0x%X  \r\n",uuid);
    #endif
    switch ( uuid )
    {
      case SIMPLEPROFILE_WRITE_CHAR_UUID:

        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != 1 )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          uint8 *pCurValue = (uint8 *)pAttr->pValue;
          *pCurValue = pValue[0];
        }

        break;

      case GATT_CLIENT_CHAR_CFG_UUID:
#ifdef UART_DEBUG
          print_msg("AttrTbl = 0x%X \r\n",simpleProfileAttrTbl[SIMPLE_CHAR2_CFG].handle );
          print_msg("GATT_CLIENT = 0x%X \r\n",pAttr->handle);
#endif

          if ( pAttr->handle == simpleProfileAttrTbl[SIMPLE_CHAR2_CFG].handle )
          {
            uint8 *pCurValue = (uint8 *)pAttr->pValue;
            *pCurValue++ = pValue[0];
            *pCurValue = pValue[1];
        #ifdef UART_DEBUG
        print_msg("start len = 0x%x \r\n",len);
        print_msg("pValue[0] = 0x%x \r\n",pValue[0]);
        print_msg("pValue[1] = 0x%x \r\n",pValue[1]);
        #endif
            if (pValue[0] == GATT_CLIENT_CFG_INDICATE && pValue[1] ==00) //Indicate Start
            {
                #ifdef UART_DEBUG
                print_msg("Indicate Start \r\n");
                #endif

                // If indications enabled
                // Send the Indication
                u8_SimpleIndicateFlag=1;
                //  Indications
                status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                         offset, GATT_CLIENT_CFG_INDICATE );


            }
            else //Indicate Stop
            {
                #ifdef UART_DEBUG
                print_msg("Indicate Stop \r\n");
                #endif
                u8_SimpleIndicateFlag=0;
            }
        #ifdef UART_DEBUG
        print_msg("end status = 0x%x \r\n",status);
        #endif
            if ( status == SUCCESS )
            {

              // Notify application
              if (pValue[0] == GATT_CFG_NO_OPERATION)
                notifyApp = SIMPLE_PROFILE_NOTI_DISABLED;
              else
                notifyApp = SIMPLE_PROFILE_NOTI_ENABLED;

            }
          }
          else
            status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;
      default:
        // Should never get here! (characteristics 2 and 4 do not have write permissions)
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }

  // If a charactersitic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange )
  {
    simpleProfile_AppCBs->pfnSimpleProfileChange( notifyApp );
  }

  return ( status );
}

//(Add)Abellee 20140716
bStatus_t simpleProfileIndicate( uint16 connHandle, attHandleValueInd_t *pNoti,uint8 taskId )
{
  uint16 value = GATTServApp_ReadCharCfg( connHandle, simpleProfileChar2Config );
#ifdef UART_DEBUG
  print_msg("simpleProfileIndicate =0x%x \r\n",value);
#endif

  // If indications enabled
  if ( value & GATT_CLIENT_CFG_INDICATE )
  {
    // Set the handle (uses stored relative handle to lookup actual handle)
    pNoti->handle = simpleProfileAttrTbl[SIMPLE_CHAR2_CFG].handle;

    // Send the Indication
    return GATT_Indication( connHandle, pNoti, FALSE, taskId );
  }
  //else
  //{
  //  u8_SimpleIndicateFlag = 0;
  //}

  return bleIncorrectMode;
}
bStatus_t simpleProfileNotify( uint16 connHandle, attHandleValueNoti_t *pNoti, uint8 taskId )
{
  uint16 value = GATTServApp_ReadCharCfg( connHandle, simpleProfileChar2Config );
#ifdef UART_DEBUG
    print_msg("simpleProfileNotify =0x%x \r\n",value);
#endif


  // If notifications enabled
  if ( value & GATT_CLIENT_CFG_NOTIFY )
  {
    // Set the handle
    pNoti->handle = simpleProfileAttrTbl[SIMPLE_CHAR2_CFG].handle;

    // Send the Indication
    return GATT_Notification( connHandle, pNoti, FALSE);

  }
    return bleIncorrectMode;

}

/*********************************************************************
 * @fn          simpleProfile_HandleConnStatusCB
 *
 * @brief       Simple Profile link status change handler function.
 *
 * @param       connHandle - connection handle
 * @param       changeType - type of change
 *
 * @return      none
 */
static void simpleProfile_HandleConnStatusCB( uint16 connHandle, uint8 changeType )
{
  // Make sure this is not loopback connection
  if ( connHandle != LOOPBACK_CONNHANDLE )
  {
    // Reset Client Char Config if connection has dropped
    if ( ( changeType == LINKDB_STATUS_UPDATE_REMOVED )      ||
         ( ( changeType == LINKDB_STATUS_UPDATE_STATEFLAGS ) &&
           ( !linkDB_Up( connHandle ) ) ) )
    {
    #ifdef UART_DEBUG
    print_msg("ConnStatus connHandle = 0x%X \r\n",connHandle);
    #endif
        GATTServApp_InitCharCfg( connHandle, simpleProfileChar2Config ); //(Add)Abellee 20140716 wechat need
    }
  }
}


/*********************************************************************
*********************************************************************/
