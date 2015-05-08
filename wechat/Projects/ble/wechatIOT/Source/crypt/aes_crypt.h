//---------------------------------------------------------------------------
//-                             aes_cbc.c                                   -
//-                             WeChat Embedded                             -
//---------------------------------------------------------------------------
#ifndef __AES_CRYPT_H__
#define __AES_CRYPT_H__
//---------------------------------------------------------------------------
//-                             Include                                     -
//---------------------------------------------------------------------------
//#include <stdint.h>
#include "aes/aes.h"
#include "epb.h"

#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
//-                             Struct                                      -
//---------------------------------------------------------------------------
typedef struct
{
	AES_KEY key;
	uint8_t iv[16];
} AES_CTX;
//---------------------------------------------------------------------------
//-                             Function                                    -
//---------------------------------------------------------------------------
int aes_cbc_encrypt_init(AES_CTX *c, const uint8_t key[16]);
int aes_cbc_encrypt_update(AES_CTX *c, const uint8_t in[16], uint8_t out[16]);
//int aes_cbc_encrypt_final(AES_CTX *c, const uint8_t *in, int in_len, uint8_t out[32], int *out_len);
int aes_cbc_encrypt_final(AES_CTX *c, uint8_t *in, int in_len, uint8_t *out, int *out_len);

int aes_cbc_decrypt_init(AES_CTX *c, const uint8_t key[16]);
int aes_cbc_decrypt_update(AES_CTX *c, const uint8_t in[16], uint8_t out[16]);
//int aes_cbc_decrypt_final(AES_CTX *c, const uint8_t in[16], uint8_t out[16], int *out_len);
int aes_cbc_decrypt_final(AES_CTX *c, uint8_t *in, int in_len, uint8_t *out, int *out_len);

#ifdef __cplusplus
}
#endif

#endif
