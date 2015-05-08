//---------------------------------------------------------------------------
//-                             epb.h                                       -
//-                             WeChat Embedded                             -
//---------------------------------------------------------------------------
//  Version : 0.7.5

#ifndef __EPB_H__
#define __EPB_H__

//#include <stdbool.h>
#include "hal_types.h"
//#include <stdint.h>
typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef signed int 	int16_t;
typedef unsigned int 	uint16_t;
typedef signed long int 	int32_t;
typedef unsigned long int 	uint32_t;
typedef signed long long int 	int64_t;
typedef unsigned long long int 	uint64_t;

#define true 1
#define false 0

typedef struct
{
    uint8_t *data ;
    int len ;
} Bytes ;

typedef struct
{
    const uint8_t *data ;
    int len ;
} CBytes ;

typedef struct
{
    char *str ;
    int len ;
} String ;

typedef struct
{
    const char *str ;
    int len ;
} CString ;

typedef uint8_t Message ;

typedef struct
{
    const uint8_t *unpack_buf ;
    uint8_t *pack_buf ;
    int buf_len ;
    int buf_offset ;
} Epb ;
//---------------------------------------------------------------------------
//-                             Function                                    -
//---------------------------------------------------------------------------
//embeded protobuf unpack functions
void epb_unpack_init(Epb *e, const uint8_t *buf, int len) ;
bool epb_has_tag(Epb *e, uint16_t tag) ;

//Varint
int32_t epb_get_int32(Epb *e, uint16_t tag) ;
uint32_t epb_get_uint32(Epb *e, uint16_t tag) ;
int32_t epb_get_sint32(Epb *e, uint16_t tag) ;
bool epb_get_bool(Epb *e, uint16_t tag) ;
int epb_get_enum(Epb *e, uint16_t tag) ;

//Length Delimited
const char *epb_get_string(Epb *e, uint16_t tag, int *len) ;
const uint8_t *epb_get_bytes(Epb *e, uint16_t tag, int *len) ;
const Message *epb_get_message(Epb *e, uint16_t tag, int *len) ;

//Length Delimited Packed Repeadted Field
//TODO

//Fixed32
uint32_t epb_get_fixed32(Epb *e, uint16_t tag) ;
int32_t epb_get_sfixed32(Epb *e, uint16_t tag) ;
float epb_get_float(Epb *e, uint16_t tag) ;

//embeded protobuf pack functions
void epb_pack_init(Epb *e, uint8_t *buf, int len) ;
int epb_get_packed_size(Epb *e) ;

//Varint
int epb_set_int32(Epb *e, uint16_t tag, int32_t value) ;
int epb_set_uint32(Epb *e, uint16_t tag, uint32_t value) ;
int epb_set_sint32(Epb *e, uint16_t tag, int32_t value) ;
int epb_set_bool(Epb *e, uint16_t tag, bool value) ;
int epb_set_enum(Epb *e, uint16_t tag, int value) ;

//Length Delimited
int epb_set_string(Epb *e, uint16_t tag, const char *data, int len) ;
int epb_set_bytes(Epb *e, uint16_t tag, const uint8_t *data, int len) ;
int epb_set_message(Epb *e, uint16_t tag, const Message *data, int len) ;

//Length Delimited Packed Repeadted Field
//TODO

//Fixed32
int epb_set_fixed32(Epb *e, uint16_t tag, uint32_t value) ;
int epb_set_sfixed32(Epb *e, uint16_t tag, int32_t value) ;
int epb_set_float(Epb *e, uint16_t tag, float value) ;

//Pack size
int epb_varint32_pack_size(uint16_t tag, uint32_t value, bool is_signed) ;
int epb_fixed32_pack_size(uint16_t tag) ;
int epb_length_delimited_pack_size(uint16_t tag, int len) ;

#endif
