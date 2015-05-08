//---------------------------------------------------------------------------
//-                             aes.h                                       -
//-                             WeChat Embedded                             -
//---------------------------------------------------------------------------
#ifndef HEADER_AES_H
#define HEADER_AES_H
//---------------------------------------------------------------------------
//-                             Include                                     -
//---------------------------------------------------------------------------
#include "epb.h"
#include <stddef.h>
//---------------------------------------------------------------------------
//-                             Define                                      -
//---------------------------------------------------------------------------
/* Because array size can't be a const in C, the following two are macros.
   Both sizes are in bytes. */
#define AES_MAXNR 14
#define AES_BLOCK_SIZE 16

/* This should be a hidden type, but EVP requires that the size be known */
struct aes_key_st
{
    uint32 rd_key[4 *(AES_MAXNR + 1)] ;
    int32 rounds ;
} ;
typedef struct aes_key_st AES_KEY ;
//---------------------------------------------------------------------------
//-                             Function                                    -
//---------------------------------------------------------------------------
int32 AES_set_encrypt_key(const unsigned char *userKey, const int32 bits,
	AES_KEY *key) ;
int32 AES_set_decrypt_key(const unsigned char *userKey, const int32 bits,
	AES_KEY *key) ;

void AES_encrypt(const unsigned char *in, unsigned char *out,
	const AES_KEY *key) ;
void AES_decrypt(const unsigned char *in, unsigned char *out,
	const AES_KEY *key) ;

void AES_cbc_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const AES_KEY *key,
	unsigned char *ivec) ;

void AES_cbc_decrypt(const unsigned char *in, unsigned char *out,
	size_t length, const AES_KEY *key,
	unsigned char *ivec) ;
//---------------------------------------------------------------------------
//-                             END                                         -
//---------------------------------------------------------------------------
#endif
