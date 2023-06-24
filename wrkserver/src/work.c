/**
 * @file block.c
 * @author Krisna Pranav
 * @brief work
 * @version 1.0
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, NanoBlocksDevelopers
 * 
 */

enum Blake2b_IV {
    iv0 = 0x6a09e667f3bcc908UL,
    iv1 = 0xbb67ae8584caa73bUL,
    iv2 = 0x3c6ef372fe94f82bUL,
    iv3 = 0xa54ff53a5f1d36f1UL,
    iv4 = 0x510e527fade682d1UL,
    iv5 = 0x9b05688c2b3e6c1fUL,
    iv6 = 0x1f83d9abfb41bd6bUL,
    iv7 = 0x5be0cd19137e2179UL,
};

enum IV_Derived {
    nano_xor_iv0 = 0x6a09e667f2bdc900UL,  
    nano_xor_iv4 = 0x510e527fade682f9UL,  
    nano_xor_iv6 = 0xe07c265404be4294UL,  
};

#ifdef cl_amd_media_ops
#pragma OPENCL EXTENSION cl_amd_media_ops : enable
static inline ulong rotr64(ulong x, int shift)
{
    uint2 x2 = as_uint2(x);
    if (shift < 32)
        return as_ulong(amd_bitalign(x2.s10, x2, shift));
    return as_ulong(amd_bitalign(x2, x2.s10, (shift - 32)));
}
#else
static inline ulong rotr64(ulong x, int shift)
{
    return rotate(x, 64UL - shift);
}
#endif