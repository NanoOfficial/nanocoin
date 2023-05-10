/**
 * @file ctaes.h
 * @author Krisna Pranav
 * @brief CTAES
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, NanoBlocksDevelopers
 * 
 */

#ifndef _CTAES_H_
#define _CTAES_H_

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief AES STATE
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

#endif