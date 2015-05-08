//---------------------------------------------------------------------------
//-                             epb_MmBp.h                                  -
//-                             WeChat Embedded                             -
//---------------------------------------------------------------------------

//  Version : 0.7.5

#ifndef __EPB_MMBP_H__
#define __EPB_MMBP_H__

//#include <stdint.h>
#include <stdbool.h>
#include "epb.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
//-                             Typedef enum                                -
//---------------------------------------------------------------------------
typedef enum
{
    ECI_none = 0,

    // Req： 藍牙設備 -> 微信/廠商服务器
    ECI_req_auth = 10001,                       // 登錄
    ECI_req_sendDataToManufacturerSvr = 10002,  // 發送數據給廠商
    ECI_req_init = 10003,                       // 初始化
    
    // Resp： 微信/廠商服務器 -> 蓝牙設備
    ECI_resp_auth = 20001,
    ECI_resp_sendDataToManufacturerSvr = 20002,
    ECI_resp_init = 20003,
    
    // Push： 微信/廠商服务器 -> 蓝牙设備
    ECI_push_manufacturerSvrSendData = 30001,   // 廠商發送数據给蓝牙設備
    ECI_push_switchView = 30002,                // 進入/退出界面
    ECI_push_switchBackgroud = 30003,           // 切换后台

    ECI_err_decode = 29999                      // 解密失败的錯誤碼。注意：這不是cmdid。為節省固定包頭大小，這種特殊的錯誤碼放在包頭的 cmdid 字段。
        
} EmCmdId ;

typedef enum
{
    EEC_system = -1 ,                           // 通用的錯誤
    EEC_needAuth = -2 ,                         // 設備未登錄
    EEC_sessionTimeout = -3 ,                   // session 超時，需要重新登錄
    EEC_decode = -4 ,                           // proto 解碼失敗
    EEC_deviceIsBlock = -5 ,                    // 設備出現異常，導致被微信臨時性禁止登錄
    EEC_serviceUnAvalibleInBackground = -6 ,    // ios 處於後台模式，無法正常服務
    EEC_deviceProtoVersionNeedUpdate = -7 ,     // 設備的 proto 版本過老，需要更新
    EEC_phoneProtoVersionNeedUpdate = -8 ,      // 微信客戶端的 proto 版本過老，需要更新
    EEC_maxReqInQueue = -9 ,                    // 設備發送了多個請求，並且沒有收到回包。微信客戶端請求隊列壅塞。
    EEC_userExitWxAccount = -10                 // 用戶退出微信帳號。
} EmErrorCode ;
//-----
typedef enum
{
	EAM_md5 = 1,
	EAM_macNoEncrypt = 2
} EmAuthMethod;
//-----初始化包要的資料-----
typedef enum
{
    EIRFF_userNickName      = 0x01 ,
    EIRFF_platformType      = 0x02 ,
    EIRFF_model             = 0x04 ,
    EIRFF_os                = 0x08 ,
    EIRFF_time              = 0x10 ,
    EIRFF_timeZone          = 0x20 ,
    EIRFF_timeString        = 0x40
} EmInitRespFieldFilter ;

typedef enum
{
    EIM_deviceChat = 1 ,                        // 聊天
    EIM_autoSync = 2                            // 自動同步
} EmInitScence ;


typedef enum 
{
    EPT_ios = 1 ,
    EPT_andriod = 2 ,
    EPT_wp = 3 ,
    EPT_s60v3 = 4 ,
    EPT_s60v5 = 5 ,
    EPT_s40 = 6 ,
    EPT_bb = 7
} EmPlatformType ;

typedef enum
{
    EEVO_enter = 1 ,
    EEVO_exit = 2
} EmSwitchViewOp ;

typedef enum
{
    EVI_deviceChatView = 1                      // 設備號會話界面
} EmViewId ;

typedef enum
{
    EEVO_enterBackground = 1 ,                  // 進入後台
    EEVO_enterForground = 2 ,                   // 進入前台
    EEVO_sleep = 3                              // 後台休眠
} EmSwitchBackgroundOp ;

//---------------------------------------------------------------------------
//-                             Typedef Struct                              -
//---------------------------------------------------------------------------
//-----Base-----
typedef struct
{
    void *request ;
} BaseRequest ;

typedef struct
{
    EmErrorCode err_code ;
    bool has_err_msg ;
    CString err_msg ;
} BaseResponse ;

typedef struct
{
    void *push ;
} BasePush ;
//-----

//-----AuthRequest-----
/*
typedef struct
{
    BaseRequest base_request ;
    Bytes md5_device_type_and_deviceid ;
    int32_t proto_version ;
    int32_t auth_proto ;
    int32_t auth_method ;
    Bytes aes_sign ;
    bool has_time_zone ;
    String time_zone ;
    bool has_language ;
    String language ;
    bool has_device_name ;
    String device_name ;
} AuthRequest;
*/
typedef struct
{
	BaseRequest *base_request;
	bool has_md5_device_type_and_device_id;
	Bytes md5_device_type_and_deviceid;
	int32_t proto_version;
	int32_t auth_proto;
	EmAuthMethod auth_method;
	bool has_aes_sign;
	Bytes aes_sign;
	bool has_mac_address;
	Bytes mac_address;
	bool has_time_zone;
	String time_zone;
	bool has_language;
	String language;
	bool has_device_name;
	String device_name;
} AuthRequest;
//-----AuthResponse-----
typedef struct
{
    BaseResponse base_response ;
    CBytes aes_session_key ;
} AuthResponse ;
//-----InitRequest-----
typedef struct
{
    BaseRequest base_request ;
    bool has_resp_field_filter ;
    Bytes resp_field_filter ;
    bool has_challeange ;
    Bytes challeange ;
} InitRequest ;
//-----InitResponse-----
typedef struct
{
    BaseResponse base_response ;
    uint32_t user_id_hight ;
    uint32_t user_id_low ;
    bool has_challeange_answer ;
    uint32_t challeange_answer ;
    bool has_init_mode ;
    uint32_t init_mode ;
    bool has_auto_sync_max_duration_second ;
    uint32_t auto_sync_max_duration_second ;
    bool has_user_nick_name ;
    CString user_nick_name ;
    bool has_platform_type ;
    EmPlatformType platform_type ;
    bool has_model ;
    CString model ;
    bool has_os ;
    CString os ;
    bool has_time ;
    int32_t time ;
    bool has_time_zone ;
    int32_t time_zone ;
    bool has_time_string ;
    CString time_string ;
} InitResponse ;
//-----SendDataToManufacturerSvrRequest-----
typedef struct
{
    BaseRequest base_request ;
    Bytes data ;
    bool has_type ;
    uint32_t type ;
} SendDataToManufacturerSvrRequest ;
//-----SendDataToManufacturerSvrResponse-----
typedef struct
{
    BaseResponse base_response ;
    bool has_data ;
    CBytes data ;
} SendDataToManufacturerSvrResponse ;
//-----ManufacturerSvrSendDataPush-----
typedef struct
{
    BasePush base_push ;
    CBytes data ;
    bool has_type ;
    uint32_t type ;
} ManufacturerSvrSendDataPush ;
//-----SwitchViewPush-----
typedef struct
{
    BasePush base_push ;
    EmSwitchViewOp switch_view_op ;
    EmViewId view_id ;
} SwitchViewPush ;
//-----SwitchBackgroudPush-----
typedef struct
{
    BasePush base_push ;
    EmSwitchBackgroundOp switch_background_op ;
} SwitchBackgroudPush ;
//---------------------------------------------------------------------------
//-                             Extern                                      -
//---------------------------------------------------------------------------
#define htonl(x)   __bswap_32(x)
uint32_t __bswap_32(uint32_t __val) ;

int epb_auth_request_pack_size(AuthRequest *request) ;
int epb_pack_auth_request(AuthRequest *request, uint8_t *buf, int buf_len) ;
AuthResponse *epb_unpack_auth_response(const uint8_t *buf, int buf_len) ;
int epb_init_request_pack_size(InitRequest *request) ;
int epb_pack_init_request(InitRequest *request, uint8_t *buf, int buf_len) ;
InitResponse *epb_unpack_init_response(const uint8_t *buf, int buf_len) ;
int epb_send_data_to_manufacturer_svr_request_pack_size(SendDataToManufacturerSvrRequest *request) ;
int epb_pack_send_data_to_manufacturer_svr_request(SendDataToManufacturerSvrRequest *request, uint8_t *buf, int buf_len) ;
SendDataToManufacturerSvrResponse *epb_unpack_send_data_to_manufacturer_svr_response(const uint8_t *buf, int buf_len) ;
ManufacturerSvrSendDataPush *epb_unpack_manufacturer_svr_send_data_push(const uint8_t *buf, int buf_len) ;
SwitchViewPush *epb_unpack_switch_view_push(const uint8_t *buf, int buf_len) ;
SwitchBackgroudPush *epb_unpack_switch_backgroud_push(const uint8_t *buf, int buf_len) ;

//-----
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
//-                             END                                         -
//---------------------------------------------------------------------------
#endif
