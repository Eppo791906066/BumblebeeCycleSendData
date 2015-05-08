#ifndef __PB_EXAMPLE_H__
#define __PB_EXAMPLE_H__
//---------------------------------------------------------------------------
//-                             Write By Adam                               -
//---------------------------------------------------------------------------
#include <stdbool.h>
#include "epb.h"
#include "epb_MmBp.h"
#include "hal_uart.h"

#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
//-                             Define                                      -
//---------------------------------------------------------------------------
#define SEQUENCE                0//0//1 //0:disable Seq ; 1:Enable Seq
#define PACKLEN                 72
#define UNPACKLEN               72
//-----定長包頭-----
#define MagicNumber             0xFE
#define bVer                    0x01
//-----
#define PACK_OK                 0
#define ERR_EMCMDID             1
#define ERR_LEN                 2
//-----
#define UNPACK_OK               0
#define UNPACK_CONTINUOUS       1
#define ERR_MAGICNUMBER         2
#define ERR_BVER                3
#define ERR_UNPACKLEN           4

#define PUSH_REC_DATA           81
#define PUSH_SWITCHVIEW         82
#define PUSH_SWITCHBACKGROUD    83

#define SEND_DATA_MAX           50
//---------------------------------------------------------------------------
//-
//---------------------------------------------------------------------------
typedef struct
{
	bool has_md5_device_type_and_device_id ;
	Bytes md5_device_type_and_deviceid ;
	int32_t proto_version ;
	int32_t auth_proto ;
	EmAuthMethod auth_method ;
	bool has_aes_sign ;
	Bytes aes_sign ;
	bool has_mac_address ;
	Bytes mac_address ;
    
    bool has_resp_field_filter ;
    Bytes resp_field_filter ;
    bool has_challeange ;
    Bytes challeange ;
}InitWechat ;
//---------------------------------------------------------------------------
//-                             Extern Variables                            -
//---------------------------------------------------------------------------
//-----送包資料-----
extern uint8_t PackProtobufData[PACKLEN] ;
extern uint16_t PackProtobufLen ;
extern uint16_t PacknSeq ;
//-----解包資料-----
extern uint8_t UnPackStatus ;
extern uint8_t UnPackProtobufData[UNPACKLEN] ;
extern uint16_t UnPackProtobufLen ;

extern uint16_t UnPackProtobufConLen ;
extern uint16_t UnPackProtobufAllLen ;
extern uint16_t UnPackEmCmdID ;
extern uint16_t UnPacknSeq ;
extern uint8_t StartUnPack ;
//-----送資料包使用-----SendData
extern uint8_t SendData[SEND_DATA_MAX] ;
extern uint8_t SendDataLen ;
extern uint32_t SendDataType ;
//-----
extern uint16_t nSeq ;
extern uint16_t UnPacknSeq ;

extern unsigned char SwitchBackgroud ;
//---------------------------------------------------------------------------
//-                             Extern Function                             -
//---------------------------------------------------------------------------
extern uint8_t InitWechatData(InitWechat *R) ;
extern uint8_t Pack_Data(uint16 EmCmdIDData ,InitWechat *Reg ) ;
extern uint8_t UnPack_Data(uint8_t *buf, int buf_len) ;

//-----
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
//-                             END                                         -
//---------------------------------------------------------------------------
#endif
