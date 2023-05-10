/**
 * @file ctaes.h
 * @author Krisna Pranav
 * @brief CTAES
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023 MIT-LICENSE Krisna Pranav, NanoBlocksDevelopers
 * 
 */

#ifndef _CTAES_H_
#define _CTAES_H_ 1

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief AES_STATE
 * 
 */
typedef struct {
    uint16_t slice[8];
} AES_state;

/**
 * @brief AES128_CTX
 * 
 */
typedef struct {
    AES_state rk[11];
} AES128_ctx;

/**
 * @brief AES192_CTX
 * 
 */
typedef struct {
    AES_state rk[13];
} AES192_ctx;

/**
 * @brief AES256_CTX
 * 
 */
typedef struct {
    AES_state rk[15];
} AES256_ctx;

/**
 * @brief AES128_INIT
 * 
 * @param ctx 
 * @param key16 
 */
void AES128_init(AES128_ctx* ctx, const unsigned char* key16);

/**
 * @brief AES128_ENCRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param cipher16 
 * @param plain16 
 */
void AES128_encrypt(const AES128_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);

/**
 * @brief AES128_DECRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param plain16 
 * @param cipher16 
 */
void AES128_decrypt(const AES128_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

/**
 * @brief AES192_INIT
 * 
 * @param ctx 
 * @param key24 
 */
void AES192_init(AES192_ctx* ctx, const unsigned char* key24);

/**
 * @brief AES192_ENCRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param cipher16 
 * @param plain16 
 */
void AES192_encrypt(const AES192_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);

/**
 * @brief AES192_DECRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param plain16 
 * @param cipher16 
 */
void AES192_decrypt(const AES192_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

/**
 * @brief AES256_INIT
 * 
 * @param ctx 
 * @param key32 
 */
void AES256_init(AES256_ctx* ctx, const unsigned char* key32);

/**
 * @brief AES256_ENCRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param cipher16 
 * @param plain16 
 */
void AES256_encrypt(const AES256_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);

/**
 * @brief AES256_DECRYPT
 * 
 * @param ctx 
 * @param blocks 
 * @param plain16 
 * @param cipher16 
 */
void AES256_decrypt(const AES256_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

#endif