//---------------------------------------------------------------------------
//-                             epb_WristBand.h                             -
//-                             WeChat Embedded                             -
//---------------------------------------------------------------------------
//  Version : 0.7.5

#ifndef __EPB_WRISTBAND_H__
#define __EPB_WRISTBAND_H__
//---------------------------------------------------------------------------
//-                             Include                                     -
//---------------------------------------------------------------------------
//#include <stdint.h>
//#include <stdbool.h>
#include "epb.h"
//---------------------------------------------------------------------------
//-                             Struct                                      -
//---------------------------------------------------------------------------
typedef enum
{
	MPT_wristband_proto = 1
} MpProtoType;

typedef struct
{
    uint32_t step ;
    uint32_t timestamp ;
} MMOpen_StepDataItem;

typedef struct
{
	int step_data_count ;
	MMOpen_StepDataItem *step_data ;
	bool has_ext_data ;
	Bytes ext_data ;
} MMOpen_WristbandRequest ;

typedef struct
{
    bool has_err_code ;
    int err_code ;
    bool has_err_msg ;
    CString err_msg ;
} MMOpen_BaseResponse ;

typedef struct
{
    MMOpen_BaseResponse base_response ;
} MMOpen_WristbandResponse ;

int epb_mmopen_wristband_request_pack_size(MMOpen_WristbandRequest *request) ;
int epb_mmopen_pack_wristband_request(MMOpen_WristbandRequest *request, uint8_t *buf, int buf_len) ;

MMOpen_WristbandResponse *epb_mmopen_unpack_wristband_response(const uint8_t *buf, int buf_len) ;
//---------------------------------------------------------------------------
//-                             END                                         -
//---------------------------------------------------------------------------
#endif