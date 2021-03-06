/**************************************************************************************************
*                                                                                                 *
* This file is part of HPMPC.                                                                     *
*                                                                                                 *
* HPMPC -- Library for High-Performance implementation of solvers for MPC.                        *
* Copyright (C) 2014 by Technical University of Denmark. All rights reserved.                     *
*                                                                                                 *
* HPMPC is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPMPC is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPMPC; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, giaf (at) dtu.dk                                                       *
*                                                                                                 *
**************************************************************************************************/

#include <mmintrin.h>
#include <xmmintrin.h>  // SSE
#include <emmintrin.h>  // SSE2
#include <pmmintrin.h>  // SSE3
/*#include <smmintrin.h>  // SSE4*/
//#include <immintrin.h>  // AVX



// normal-transposed, 4x4 with data packed in 4
void kernel_dgemm_nt_4x4_lib4(int kmax, double *A, double *B, double *C, double *D, int alg)
	{
	
	if(kmax<=0)
		return;
	
	int k_iter = kmax / 4;
	int k_left = kmax % 4;

	__asm__ volatile
	(
		"                                \n\t"
		"                                \n\t"
		"movq          %2, %%rax         \n\t" // load address of A
		"movq          %3, %%rbx         \n\t" // load address of B
		"                                \n\t"
		"                                \n\t"
		"movaps        0(%%rax), %%xmm0  \n\t" // initialize loop by pre-loading elements
		"movaps       16(%%rax), %%xmm1  \n\t" // of a and b.
		"movaps        0(%%rbx), %%xmm2  \n\t"
		"                                \n\t"
		"                                \n\t"
		"xorpd     %%xmm3,  %%xmm3       \n\t"
		"movaps    %%xmm3,  %%xmm4       \n\t"
		"movaps    %%xmm3,  %%xmm5       \n\t"
		"movaps    %%xmm3,  %%xmm6       \n\t"
		"movaps    %%xmm3,  %%xmm7       \n\t"
		"movaps    %%xmm3,  %%xmm8       \n\t"
		"movaps    %%xmm3,  %%xmm9       \n\t"
		"movaps    %%xmm3, %%xmm10       \n\t"
		"movaps    %%xmm3, %%xmm11       \n\t"
		"movaps    %%xmm3, %%xmm12       \n\t"
		"movaps    %%xmm3, %%xmm13       \n\t"
		"movaps    %%xmm3, %%xmm14       \n\t"
		"movaps    %%xmm3, %%xmm15       \n\t"
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		"movl      %0, %%esi             \n\t" // i = k_iter;
		"testl  %%esi, %%esi             \n\t" // check i via logical AND.
		"je     .SCONSIDKLEFT            \n\t" // if i == 0, jump to code that
		"                                \n\t" // contains the k_left loop.
		"                                \n\t"
		"                                \n\t"
		".SLOOPKITER:                    \n\t" // MAIN LOOP
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t" // iteration 0
		"movaps       16(%%rbx), %%xmm6  \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"movaps  %%xmm2, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm2, %%xmm7  \n\t"
		"mulpd   %%xmm0, %%xmm2          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"movaps  %%xmm7, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm7          \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"                                \n\t"
		"addpd   %%xmm2, %%xmm8          \n\t"
		"movaps       32(%%rbx), %%xmm2  \n\t"
		"addpd   %%xmm3, %%xmm12         \n\t"
		"movaps  %%xmm6, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm6, %%xmm4  \n\t"
		"mulpd   %%xmm0, %%xmm6          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm7, %%xmm9          \n\t"
		"addpd   %%xmm5, %%xmm13         \n\t"
		"movaps  %%xmm4, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm4          \n\t"
		"movaps       32(%%rax), %%xmm0  \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"movaps       48(%%rax), %%xmm1  \n\t"
		"                                \n\t"
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t" // iteration 1
		"movaps       48(%%rbx), %%xmm6  \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"movaps  %%xmm2, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm2, %%xmm7  \n\t"
		"mulpd   %%xmm0, %%xmm2          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"movaps  %%xmm7, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm7          \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"                                \n\t"
		"addpd   %%xmm2, %%xmm8          \n\t"
		"movaps       64(%%rbx), %%xmm2  \n\t"
		"addpd   %%xmm3, %%xmm12         \n\t"
		"movaps  %%xmm6, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm6, %%xmm4  \n\t"
		"mulpd   %%xmm0, %%xmm6          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm7, %%xmm9          \n\t"
		"addpd   %%xmm5, %%xmm13         \n\t"
		"movaps  %%xmm4, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm4          \n\t"
		"movaps       64(%%rax), %%xmm0  \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"movaps       80(%%rax), %%xmm1  \n\t"
		"                                \n\t"
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t" // iteration 2
		"movaps       80(%%rbx), %%xmm6  \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"movaps  %%xmm2, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm2, %%xmm7  \n\t"
		"mulpd   %%xmm0, %%xmm2          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"movaps  %%xmm7, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm7          \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"                                \n\t"
		"addpd   %%xmm2, %%xmm8          \n\t"
		"movaps       96(%%rbx), %%xmm2  \n\t"
		"addpd   %%xmm3, %%xmm12         \n\t"
		"movaps  %%xmm6, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm6, %%xmm4  \n\t"
		"mulpd   %%xmm0, %%xmm6          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm7, %%xmm9          \n\t"
		"addpd   %%xmm5, %%xmm13         \n\t"
		"movaps  %%xmm4, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm4          \n\t"
		"movaps       96(%%rax), %%xmm0  \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"movaps      112(%%rax), %%xmm1  \n\t"
		"                                \n\t"
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t" // iteration 3
		"movaps      112(%%rbx), %%xmm6  \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"movaps  %%xmm2, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm2, %%xmm7  \n\t"
		"mulpd   %%xmm0, %%xmm2          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addq      $128, %%rax           \n\t" // A0 += 16
		"                                \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"movaps  %%xmm7, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm7          \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"                                \n\t"
		"addq      $128, %%rbx           \n\t" // B += 16
		"                                \n\t"
		"addpd   %%xmm2, %%xmm8          \n\t"
		"movaps         (%%rbx), %%xmm2  \n\t"
		"addpd   %%xmm3, %%xmm12         \n\t"
		"movaps  %%xmm6, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm6, %%xmm4  \n\t"
		"mulpd   %%xmm0, %%xmm6          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"                                \n\t"
		"addpd   %%xmm7, %%xmm9          \n\t"
		"decl    %%esi                   \n\t" // i -= 1;
		"addpd   %%xmm5, %%xmm13         \n\t"
		"movaps  %%xmm4, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm4          \n\t"
		"movaps         (%%rax), %%xmm0  \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"movaps       16(%%rax), %%xmm1  \n\t"
		"                                \n\t"
		"                                \n\t"
		"jne    .SLOOPKITER              \n\t" // iterate again if i != 0.
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		".SCONSIDKLEFT:                  \n\t"
		"                                \n\t"
		"movl      %1, %%esi             \n\t" // i = k_left;
		"testl  %%esi, %%esi             \n\t" // check i via logical AND.
		"je     .SPOSTACCUM              \n\t" // if i == 0, we're done; jump to end.
		"                                \n\t" // else, we prepare to enter k_left loop.
		"                                \n\t"
		"                                \n\t"
		".SLOOPKLEFT:                    \n\t" // EDGE LOOP
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t" // iteration 0
		"movaps       16(%%rbx), %%xmm6  \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"movaps  %%xmm2, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm2, %%xmm7  \n\t"
		"mulpd   %%xmm0, %%xmm2          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"movaps  %%xmm7, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm7          \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"                                \n\t"
		"addpd   %%xmm2, %%xmm8          \n\t"
		"movaps       32(%%rbx), %%xmm2  \n\t"
		"addpd   %%xmm3, %%xmm12         \n\t"
		"movaps  %%xmm6, %%xmm3          \n\t"
		"pshufd   $0x4e, %%xmm6, %%xmm4  \n\t"
		"mulpd   %%xmm0, %%xmm6          \n\t"
		"mulpd   %%xmm1, %%xmm3          \n\t"
		"                                \n\t"
		"addpd   %%xmm7, %%xmm9          \n\t"
		"addpd   %%xmm5, %%xmm13         \n\t"
		"movaps  %%xmm4, %%xmm5          \n\t"
		"mulpd   %%xmm0, %%xmm4          \n\t"
		"movaps       32(%%rax), %%xmm0  \n\t"
		"mulpd   %%xmm1, %%xmm5          \n\t"
		"movaps       48(%%rax), %%xmm1  \n\t"
		"                                \n\t"
		"addq          $32, %%rax        \n\t" // A += 4
		"addq          $32, %%rbx        \n\t" // B += 4
		"                                \n\t"
		"                                \n\t"
		"decl    %%esi                   \n\t" // i -= 1;
		"jne    .SLOOPKLEFT              \n\t" // iterate again if i != 0.
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		".SPOSTACCUM:                    \n\t"
		"                                \n\t"
		"addpd   %%xmm6, %%xmm10         \n\t"
		"addpd   %%xmm3, %%xmm14         \n\t"
		"addpd   %%xmm4, %%xmm11         \n\t"
		"addpd   %%xmm5, %%xmm15         \n\t"
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		"movaps   %%xmm8,  %%xmm0        \n\t"
		"movsd    %%xmm9,  %%xmm8        \n\t"
		"movsd    %%xmm0,  %%xmm9        \n\t"
		"                                \n\t"
		"movaps  %%xmm10,  %%xmm0        \n\t"
		"movsd   %%xmm11, %%xmm10        \n\t"
		"movsd    %%xmm0, %%xmm11        \n\t"
		"                                \n\t"
		"movaps  %%xmm12,  %%xmm0        \n\t"
		"movsd   %%xmm13, %%xmm12        \n\t"
		"movsd    %%xmm0, %%xmm13        \n\t"
		"                                \n\t"
		"movaps  %%xmm14,  %%xmm0        \n\t"
		"movsd   %%xmm15, %%xmm14        \n\t"
		"movsd    %%xmm0, %%xmm15        \n\t"
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		"movq   %4, %%rax                \n\t" // load address of C
		"movq   %6, %%rbx                \n\t" // load address of D
		"                                \n\t"
		"                                \n\t"
		"movl   %5, %%ecx                \n\t" // alg
		"testl  %%ecx, %%ecx             \n\t" // check alg
		"je     .S0                      \n\t" // if alg==0, jump
		"                                \n\t"
		"cmpl	$1, %%ecx                \n\t"
		"                                \n\t"
		"movaps  (%%rax),   %%xmm0       \n\t" // load C0
		"movaps  32(%%rax), %%xmm1       \n\t"
		"movaps  64(%%rax), %%xmm2       \n\t"
		"movaps  96(%%rax), %%xmm3       \n\t"
		"movaps  16(%%rax), %%xmm4       \n\t" // load C0
		"movaps  48(%%rax), %%xmm5       \n\t"
		"movaps  80(%%rax), %%xmm6       \n\t"
		"movaps 112(%%rax), %%xmm7       \n\t"
		"                                \n\t"
		"je     .S1                      \n\t" // if alg==1, jump
		"                                \n\t"
		"                                \n\t"// alg==-1
		"subpd  %%xmm9,  %%xmm0           \n\t"
		"subpd  %%xmm8,  %%xmm1           \n\t"
		"subpd  %%xmm11, %%xmm2           \n\t"
		"subpd  %%xmm10, %%xmm3           \n\t"
		"subpd  %%xmm13, %%xmm4           \n\t"
		"subpd  %%xmm12, %%xmm5           \n\t"
		"subpd  %%xmm15, %%xmm6           \n\t"
		"subpd  %%xmm14, %%xmm7           \n\t"
		"                                \n\t"
		"movaps  %%xmm0, (%%rbx)         \n\t"
		"movaps  %%xmm1, 32(%%rbx)       \n\t"
		"movaps  %%xmm2, 64(%%rbx)       \n\t"
		"movaps  %%xmm3, 96(%%rbx)       \n\t"
		"movaps  %%xmm4, 16(%%rbx)       \n\t"
		"movaps  %%xmm5, 48(%%rbx)       \n\t"
		"movaps  %%xmm6, 80(%%rbx)       \n\t"
		"movaps  %%xmm7, 112(%%rbx)       \n\t"
		"                                \n\t"
		"jmp    .SDONE                   \n\t" // jump to end
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		".S1:                            \n\t" // alg==1
		"                                \n\t"
		"addpd  %%xmm0, %%xmm9           \n\t"
		"addpd  %%xmm1, %%xmm8           \n\t"
		"addpd  %%xmm2, %%xmm11          \n\t"
		"addpd  %%xmm3, %%xmm10          \n\t"
		"addpd  %%xmm4, %%xmm13          \n\t"
		"addpd  %%xmm5, %%xmm12          \n\t"
		"addpd  %%xmm6, %%xmm15          \n\t"
		"addpd  %%xmm7, %%xmm14          \n\t"
		"                                \n\t"
		".S0:                            \n\t" // alg==0
		"                                \n\t"
		"movaps	%%xmm9,  (%%rbx)          \n\t"
		"movaps	%%xmm8,  32(%%rbx)        \n\t"
		"movaps	%%xmm11, 64(%%rbx)        \n\t"
		"movaps	%%xmm10, 96(%%rbx)        \n\t"
		"movaps	%%xmm13, 16(%%rbx)        \n\t"
		"movaps	%%xmm12, 48(%%rbx)        \n\t"
		"movaps	%%xmm15, 80(%%rbx)        \n\t"
		"movaps	%%xmm14, 112(%%rbx)       \n\t"
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		"                                \n\t"
		".SDONE:                         \n\t"
		"                                \n\t"

		: // output operands (none)
		: // input operands
		  "m" (k_iter),		// %0
		  "m" (k_left),		// %1
		  "m" (A),			// %2
		  "m" (B),			// %3
		  "m" (C),			// %4
		  "m" (alg),		// %5
		  "m" (D)			// %6
		: // register clobber list
		  "rax", "rbx", "rsi", //"rdx", //"rdi", "r8", "r9", "r10", "r11",
		  "xmm0", "xmm1", "xmm2", "xmm3",
		  "xmm4", "xmm5", "xmm6", "xmm7",
		  "xmm8", "xmm9", "xmm10", "xmm11",
		  "xmm12", "xmm13", "xmm14", "xmm15",
		  "memory"
	);
}



// 4x2 with data packed in 4
void kernel_dgemm_nt_4x2_lib4(int kmax, double *A, double *B, double *C, double *D, int alg)
	{
	
	if(kmax<=0)
		return;

	const int ldc = 4;

	int k;
	
	__m128d
		c_00_11, c_01_10, c_20_31, c_21_30,
		a_01, a_23,
		b_01, b_10, b_temp_0, b_temp_1;
	
	c_00_11 = _mm_setzero_pd();
	c_01_10 = _mm_setzero_pd();
	c_20_31 = _mm_setzero_pd();
	c_21_30 = _mm_setzero_pd();
	
	k = 0;
	for(; k<kmax-3; k+=4)
		{
		a_01 = _mm_load_pd(&A[0]);
		a_23 = _mm_load_pd(&A[2]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_temp_0 = b_01;
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );
		b_temp_0 = _mm_mul_pd( a_23, b_temp_0 );
		c_20_31 = _mm_add_pd( c_20_31, b_temp_0 );

		b_temp_1 = b_10;
		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		b_temp_1 = _mm_mul_pd( a_23, b_temp_1 );
		c_21_30 = _mm_add_pd( c_21_30, b_temp_1 );
		
		
		a_01 = _mm_load_pd(&A[4]);
		a_23 = _mm_load_pd(&A[6]);
		
		b_01 = _mm_load_pd(&B[4]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_temp_0 = b_01;
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );
		b_temp_0 = _mm_mul_pd( a_23, b_temp_0 );
		c_20_31 = _mm_add_pd( c_20_31, b_temp_0 );

		b_temp_1 = b_10;
		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		b_temp_1 = _mm_mul_pd( a_23, b_temp_1 );
		c_21_30 = _mm_add_pd( c_21_30, b_temp_1 );
		
		
		a_01 = _mm_load_pd(&A[8]);
		a_23 = _mm_load_pd(&A[10]);
		
		b_01 = _mm_load_pd(&B[8]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_temp_0 = b_01;
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );
		b_temp_0 = _mm_mul_pd( a_23, b_temp_0 );
		c_20_31 = _mm_add_pd( c_20_31, b_temp_0 );

		b_temp_1 = b_10;
		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		b_temp_1 = _mm_mul_pd( a_23, b_temp_1 );
		c_21_30 = _mm_add_pd( c_21_30, b_temp_1 );
		
		
		a_01 = _mm_load_pd(&A[12]);
		a_23 = _mm_load_pd(&A[14]);
		
		b_01 = _mm_load_pd(&B[12]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_temp_0 = b_01;
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );
		b_temp_0 = _mm_mul_pd( a_23, b_temp_0 );
		c_20_31 = _mm_add_pd( c_20_31, b_temp_0 );

		b_temp_1 = b_10;
		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		b_temp_1 = _mm_mul_pd( a_23, b_temp_1 );
		c_21_30 = _mm_add_pd( c_21_30, b_temp_1 );

		
		A += 16;
		B += 16;

		}
	
	for(; k<kmax; k++)
		{

		a_01 = _mm_load_pd(&A[0]);
		a_23 = _mm_load_pd(&A[2]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_temp_0 = b_01;
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );
		b_temp_0 = _mm_mul_pd( a_23, b_temp_0 );
		c_20_31 = _mm_add_pd( c_20_31, b_temp_0 );

		b_temp_1 = b_10;
		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		b_temp_1 = _mm_mul_pd( a_23, b_temp_1 );
		c_21_30 = _mm_add_pd( c_21_30, b_temp_1 );
		

		A += 4;
		B += 4;

		}

	__m128d
		c_00_10, c_20_30, c_01_11, c_21_31,
		d_00_10, d_20_30, d_01_11, d_21_31;

/*	c_00_10 = _mm_blend_pd(c_00_11, c_01_10, 2);*/
/*	c_01_11 = _mm_blend_pd(c_01_10, c_00_11, 2);*/
/*	c_20_30 = _mm_blend_pd(c_20_31, c_21_30, 2);*/
/*	c_21_31 = _mm_blend_pd(c_21_30, c_20_31, 2);*/

	c_00_10 = _mm_shuffle_pd(c_00_11, c_01_10, 2);
	c_01_11 = _mm_shuffle_pd(c_01_10, c_00_11, 2);
	c_20_30 = _mm_shuffle_pd(c_20_31, c_21_30, 2);
	c_21_31 = _mm_shuffle_pd(c_21_30, c_20_31, 2);

	if(alg==0) // C = A * B'
		{
		_mm_store_pd(&D[0+ldc*0], c_00_10);
		_mm_store_pd(&D[2+ldc*0], c_20_30);
		_mm_store_pd(&D[0+ldc*1], c_01_11);
		_mm_store_pd(&D[2+ldc*1], c_21_31);
		}
	else
		{
		d_00_10 = _mm_load_pd(&C[0+ldc*0]);
		d_20_30 = _mm_load_pd(&C[2+ldc*0]);
		d_01_11 = _mm_load_pd(&C[0+ldc*1]);
		d_21_31 = _mm_load_pd(&C[2+ldc*1]);
		
		if(alg==1) // C += A * B'
			{
			d_00_10 = _mm_add_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_add_pd( d_01_11, c_01_11 ); 
			d_20_30 = _mm_add_pd( d_20_30, c_20_30 ); 
			d_21_31 = _mm_add_pd( d_21_31, c_21_31 );
			}
		else // C -= A * B'
			{
			d_00_10 = _mm_sub_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_sub_pd( d_01_11, c_01_11 ); 
			d_20_30 = _mm_sub_pd( d_20_30, c_20_30 ); 
			d_21_31 = _mm_sub_pd( d_21_31, c_21_31 ); 
			}

		_mm_store_pd(&D[0+ldc*0], d_00_10);
		_mm_store_pd(&D[2+ldc*0], d_20_30);
		_mm_store_pd(&D[0+ldc*1], d_01_11);
		_mm_store_pd(&D[2+ldc*1], d_21_31);
		}

	}



// 2x4 with data packed in 4
void kernel_dgemm_nt_2x4_lib4(int kmax, double *A, double *B, double *C, double *D, int alg)
	{
	
	if(kmax<=0)
		return;

	const int ldc = 4;

	int k;
	
	__m128d
		c_00_11, c_01_10, c_02_13, c_03_12,
		a_01,
		b_01, b_10, b_23, b_32;
	
	c_00_11 = _mm_setzero_pd();
	c_01_10 = _mm_setzero_pd();
	c_02_13 = _mm_setzero_pd();
	c_03_12 = _mm_setzero_pd();
	
	k = 0;
	for(; k<kmax-3; k+=4)
		{
		a_01 = _mm_load_pd(&A[0]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
		b_23 = _mm_load_pd(&B[2]);
		b_32 = _mm_shuffle_pd(b_23, b_23, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		b_23 = _mm_mul_pd( a_01, b_23 );
		c_02_13 = _mm_add_pd( c_02_13, b_23 );

		b_32 = _mm_mul_pd( a_01, b_32 );
		c_03_12 = _mm_add_pd( c_03_12, b_32 );
		
		
		a_01 = _mm_load_pd(&A[4]);
		
		b_01 = _mm_load_pd(&B[4]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
		b_23 = _mm_load_pd(&B[6]);
		b_32 = _mm_shuffle_pd(b_23, b_23, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		b_23 = _mm_mul_pd( a_01, b_23 );
		c_02_13 = _mm_add_pd( c_02_13, b_23 );

		b_32 = _mm_mul_pd( a_01, b_32 );
		c_03_12 = _mm_add_pd( c_03_12, b_32 );
		
		
		a_01 = _mm_load_pd(&A[8]);
		
		b_01 = _mm_load_pd(&B[8]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
		b_23 = _mm_load_pd(&B[10]);
		b_32 = _mm_shuffle_pd(b_23, b_23, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		b_23 = _mm_mul_pd( a_01, b_23 );
		c_02_13 = _mm_add_pd( c_02_13, b_23 );

		b_32 = _mm_mul_pd( a_01, b_32 );
		c_03_12 = _mm_add_pd( c_03_12, b_32 );
		
		
		a_01 = _mm_load_pd(&A[12]);
		
		b_01 = _mm_load_pd(&B[12]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
		b_23 = _mm_load_pd(&B[14]);
		b_32 = _mm_shuffle_pd(b_23, b_23, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		b_23 = _mm_mul_pd( a_01, b_23 );
		c_02_13 = _mm_add_pd( c_02_13, b_23 );

		b_32 = _mm_mul_pd( a_01, b_32 );
		c_03_12 = _mm_add_pd( c_03_12, b_32 );

		
		A += 16;
		B += 16;

		}
	
	for(; k<kmax; k++)
		{

		a_01 = _mm_load_pd(&A[0]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
		b_23 = _mm_load_pd(&B[2]);
		b_32 = _mm_shuffle_pd(b_23, b_23, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		b_23 = _mm_mul_pd( a_01, b_23 );
		c_02_13 = _mm_add_pd( c_02_13, b_23 );

		b_32 = _mm_mul_pd( a_01, b_32 );
		c_03_12 = _mm_add_pd( c_03_12, b_32 );
		

		A += 4;
		B += 4;

		}

	__m128d
		c_00_10, c_01_11, c_02_12, c_03_13,
		d_00_10, d_01_11, d_02_12, d_03_13;

/*	c_00_10 = _mm_blend_pd(c_00_11, c_01_10, 2);*/
/*	c_01_11 = _mm_blend_pd(c_01_10, c_00_11, 2);*/
/*	c_02_12 = _mm_blend_pd(c_02_13, c_03_12, 2);*/
/*	c_03_13 = _mm_blend_pd(c_03_12, c_02_13, 2);*/

	c_00_10 = _mm_shuffle_pd(c_00_11, c_01_10, 2);
	c_01_11 = _mm_shuffle_pd(c_01_10, c_00_11, 2);
	c_02_12 = _mm_shuffle_pd(c_02_13, c_03_12, 2);
	c_03_13 = _mm_shuffle_pd(c_03_12, c_02_13, 2);

	if(alg==0) // C = A * B'
		{
		_mm_store_pd(&D[0+ldc*0], c_00_10);
		_mm_store_pd(&D[0+ldc*1], c_01_11);
		_mm_store_pd(&D[0+ldc*2], c_02_12);
		_mm_store_pd(&D[0+ldc*3], c_03_13);
		}
	else
		{
		d_00_10 = _mm_load_pd(&C[0+ldc*0]);
		d_01_11 = _mm_load_pd(&C[0+ldc*1]);
		d_02_12 = _mm_load_pd(&C[0+ldc*2]);
		d_03_13 = _mm_load_pd(&C[0+ldc*3]);
		
		if(alg==1) // C += A * B'
			{
			d_00_10 = _mm_add_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_add_pd( d_01_11, c_01_11 ); 
			d_02_12 = _mm_add_pd( d_02_12, c_02_12 ); 
			d_03_13 = _mm_add_pd( d_03_13, c_03_13 ); 
			}
		else // C -= A * B'
			{
			d_00_10 = _mm_sub_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_sub_pd( d_01_11, c_01_11 ); 
			d_02_12 = _mm_sub_pd( d_02_12, c_02_12 ); 
			d_03_13 = _mm_sub_pd( d_03_13, c_03_13 ); 
			}

		_mm_store_pd(&D[0+ldc*0], d_00_10);
		_mm_store_pd(&D[0+ldc*1], d_01_11);
		_mm_store_pd(&D[0+ldc*2], d_02_12);
		_mm_store_pd(&D[0+ldc*3], d_03_13);
		}

	}



// 2x2 with data packed in 4
void kernel_dgemm_nt_2x2_lib4(int kmax, double *A, double *B, double *C, double *D, int alg)
	{
	
	if(kmax<=0)
		return;

	const int ldc = 4;

	int k;
	
	__m128d
		c_00_11, c_01_10,
		a_01,
		b_01, b_10;
	
	c_00_11 = _mm_setzero_pd();
	c_01_10 = _mm_setzero_pd();
	
	k = 0;
	for(; k<kmax-3; k+=4)
		{
		a_01 = _mm_load_pd(&A[0]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		
		a_01 = _mm_load_pd(&A[4]);
		
		b_01 = _mm_load_pd(&B[4]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		
		a_01 = _mm_load_pd(&A[8]);
		
		b_01 = _mm_load_pd(&B[8]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		
		
		a_01 = _mm_load_pd(&A[12]);
		
		b_01 = _mm_load_pd(&B[12]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );

		
		A += 16;
		B += 16;

		}
	
	for(; k<kmax; k++)
		{

		a_01 = _mm_load_pd(&A[0]);
		
		b_01 = _mm_load_pd(&B[0]);
		b_10 = _mm_shuffle_pd(b_01, b_01, 1);
	
		b_01 = _mm_mul_pd( a_01, b_01 );
		c_00_11 = _mm_add_pd( c_00_11, b_01 );

		b_10 = _mm_mul_pd( a_01, b_10 );
		c_01_10 = _mm_add_pd( c_01_10, b_10 );
		

		A += 4;
		B += 4;

		}

	__m128d
		c_00_10, c_01_11,
		d_00_10, d_01_11;

/*	c_00_10 = _mm_blend_pd(c_00_11, c_01_10, 2);*/
/*	c_01_11 = _mm_blend_pd(c_01_10, c_00_11, 2);*/

	c_00_10 = _mm_shuffle_pd(c_00_11, c_01_10, 2);
	c_01_11 = _mm_shuffle_pd(c_01_10, c_00_11, 2);

	if(alg==0) // C = A * B'
		{
		_mm_store_pd(&D[0+ldc*0], c_00_10);
		_mm_store_pd(&D[0+ldc*1], c_01_11);
		}
	else
		{
		d_00_10 = _mm_load_pd(&C[0+ldc*0]);
		d_01_11 = _mm_load_pd(&C[0+ldc*1]);
		
		if(alg==1) // C += A * B'
			{
			d_00_10 = _mm_add_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_add_pd( d_01_11, c_01_11 ); 
			}
		else // C -= A * B'
			{
			d_00_10 = _mm_sub_pd( d_00_10, c_00_10 ); 
			d_01_11 = _mm_sub_pd( d_01_11, c_01_11 ); 
			}

		_mm_store_pd(&D[0+ldc*0], d_00_10);
		_mm_store_pd(&D[0+ldc*1], d_01_11);
		}

	}

