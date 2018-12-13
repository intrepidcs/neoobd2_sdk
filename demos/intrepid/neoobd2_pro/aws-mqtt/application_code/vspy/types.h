/*
Copyright (c) 2018 Intrepid Control Systems, Inc.
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#define icscm_bitfield	uint16_t

#define int8  	uint8_t
#define int16 	unsigned short
#define int32	unsigned int
#define int64	unsigned long long

#define int8s	char
#define int16s	short
#define int32s	int
#define int64s	long long

#define icscm_uint8		uint8_t
#define icscm_uint16	int16
#define icscm_uint32	int32
#define icscm_uint64	int64

#define icscm_int8		int8s
#define icscm_int16		int16s
#define icscm_int32		int32s
#define icscm_int64		int64s

#define icscm_float32	float
#define icscm_float64	long double

#define POINTERS_ARE_32BITS

static inline uint32_t __REV16(uint32_t x)
{
    return (((uint32_t)(x) & (uint32_t)0x00ff00ffUL) << 8) | (((uint32_t)(x) & (uint32_t)0xff00ff00UL) >> 8);
}

#endif /* TYPES_H_ */
