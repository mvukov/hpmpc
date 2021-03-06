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
#include <smmintrin.h>  // SSE4
#include <immintrin.h>  // AVX



// it moves horizontally inside a block
void kernel_dtrsv_n_8_lib4(int kmax, double *A0, double *A1, double *x, double *y)
	{

/*printf("\nciao\n");*/

/*	if(kmax<=0) */
/*		return;*/
	
	const int lda = 4;
	
	int k;

	__m256d
		ax_temp, temp0, temp1,
		a_00_10_20_30, a_01_11_21_31,
		a_40_50_60_70, a_41_51_61_71,
		x_0, x_1,
		y_0_1_2_3, y_0_1_2_3_b, z_0_1_2_3,
		y_4_5_6_7, y_4_5_6_7_b, z_4_5_6_7;
	
	y_0_1_2_3   = _mm256_setzero_pd();	
	y_4_5_6_7   = _mm256_setzero_pd();	
	y_0_1_2_3_b = _mm256_setzero_pd();	
	y_4_5_6_7_b = _mm256_setzero_pd();	

	k=0;
	for(; k<kmax-7; k+=8)
		{

/*		__builtin_prefetch( A0 + 4*lda );*/
/*		__builtin_prefetch( A1 + 4*lda );*/

		x_0 = _mm256_broadcast_sd( &x[0] );
		x_1 = _mm256_broadcast_sd( &x[1] );

		a_00_10_20_30 = _mm256_load_pd( &A0[0+lda*0] );
		a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A0[0+lda*1] );
		a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*1] );

		ax_temp = _mm256_mul_pd( a_00_10_20_30, x_0 );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, ax_temp );
		ax_temp = _mm256_mul_pd( a_40_50_60_70, x_0 );
		y_4_5_6_7 = _mm256_add_pd( y_4_5_6_7, ax_temp );
		ax_temp = _mm256_mul_pd( a_01_11_21_31, x_1 );
		y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, ax_temp );
		ax_temp = _mm256_mul_pd( a_41_51_61_71, x_1 );
		y_4_5_6_7_b = _mm256_add_pd( y_4_5_6_7_b, ax_temp );

/*		__builtin_prefetch( A0 + 5*lda );*/
/*		__builtin_prefetch( A1 + 5*lda );*/

		x_0 = _mm256_broadcast_sd( &x[2] );
		x_1 = _mm256_broadcast_sd( &x[3] );

		a_00_10_20_30 = _mm256_load_pd( &A0[0+lda*2] );
		a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*2] );
		a_01_11_21_31 = _mm256_load_pd( &A0[0+lda*3] );
		a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*3] );

		ax_temp = _mm256_mul_pd( a_00_10_20_30, x_0 );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, ax_temp );
		ax_temp = _mm256_mul_pd( a_40_50_60_70, x_0 );
		y_4_5_6_7 = _mm256_add_pd( y_4_5_6_7, ax_temp );
		ax_temp = _mm256_mul_pd( a_01_11_21_31, x_1 );
		y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, ax_temp );
		ax_temp = _mm256_mul_pd( a_41_51_61_71, x_1 );
		y_4_5_6_7_b = _mm256_add_pd( y_4_5_6_7_b, ax_temp );
	
		A0 += 4*lda;
		A1 += 4*lda;
		x  += 4;

/*		__builtin_prefetch( A0 + 4*lda );*/
/*		__builtin_prefetch( A1 + 4*lda );*/

		x_0 = _mm256_broadcast_sd( &x[0] );
		x_1 = _mm256_broadcast_sd( &x[1] );

		a_00_10_20_30 = _mm256_load_pd( &A0[0+lda*0] );
		a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A0[0+lda*1] );
		a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*1] );

		ax_temp = _mm256_mul_pd( a_00_10_20_30, x_0 );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, ax_temp );
		ax_temp = _mm256_mul_pd( a_40_50_60_70, x_0 );
		y_4_5_6_7 = _mm256_add_pd( y_4_5_6_7, ax_temp );
		ax_temp = _mm256_mul_pd( a_01_11_21_31, x_1 );
		y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, ax_temp );
		ax_temp = _mm256_mul_pd( a_41_51_61_71, x_1 );
		y_4_5_6_7_b = _mm256_add_pd( y_4_5_6_7_b, ax_temp );

/*		__builtin_prefetch( A0 + 5*lda );*/
/*		__builtin_prefetch( A1 + 5*lda );*/

		x_0 = _mm256_broadcast_sd( &x[2] );
		x_1 = _mm256_broadcast_sd( &x[3] );

		a_00_10_20_30 = _mm256_load_pd( &A0[0+lda*2] );
		a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*2] );
		a_01_11_21_31 = _mm256_load_pd( &A0[0+lda*3] );
		a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*3] );

		ax_temp = _mm256_mul_pd( a_00_10_20_30, x_0 );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, ax_temp );
		ax_temp = _mm256_mul_pd( a_40_50_60_70, x_0 );
		y_4_5_6_7 = _mm256_add_pd( y_4_5_6_7, ax_temp );
		ax_temp = _mm256_mul_pd( a_01_11_21_31, x_1 );
		y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, ax_temp );
		ax_temp = _mm256_mul_pd( a_41_51_61_71, x_1 );
		y_4_5_6_7_b = _mm256_add_pd( y_4_5_6_7_b, ax_temp );
	
		A0 += 4*lda;
		A1 += 4*lda;
		x  += 4;

		}
	
	y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, y_0_1_2_3_b );
	y_4_5_6_7 = _mm256_add_pd( y_4_5_6_7, y_4_5_6_7_b );

	z_0_1_2_3 = _mm256_loadu_pd( &y[0] );
	z_4_5_6_7 = _mm256_loadu_pd( &y[4] );
	z_0_1_2_3 = _mm256_sub_pd( z_0_1_2_3, y_0_1_2_3 );
	z_4_5_6_7 = _mm256_sub_pd( z_4_5_6_7, y_4_5_6_7 );

	// solve

	__m128d
		zeros,
		a_00, a_10, a_11, a_20_30, a_21_31,
		z_0, z_1,
		z_0_1, z_2_3, tmp0, tmp1;
	
	zeros = _mm_setzero_pd();
	
	// A_00
	z_2_3 = _mm256_extractf128_pd( z_0_1_2_3, 0x1 );
	z_0_1 = _mm256_castpd256_pd128( z_0_1_2_3 );

	a_00 = _mm_load_sd( &A0[0+lda*0] );
	a_10 = _mm_load_sd( &A0[1+lda*0] );
	a_11 = _mm_load_sd( &A0[1+lda*1] );

	z_0   = _mm_shuffle_pd( z_0_1, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_0_1, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	a_20_30 = _mm_load_pd( &A0[2+lda*0] );
	a_21_31 = _mm_load_pd( &A0[2+lda*1] );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[0], z_0 );
	z_0   = _mm_movedup_pd( z_0 );
	z_1   = _mm_sub_pd( z_1, tmp0 );
	tmp0  = _mm_mul_pd( a_20_30, z_0 );
	z_1   = _mm_mul_sd( a_11, z_1 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp0 );
	_mm_store_sd( &y[1], z_1 );
	z_1   = _mm_movedup_pd( z_1 );
	tmp1  = _mm_mul_pd( a_21_31, z_1 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp1 );
	
	a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*0] );
	a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*1] );
	x_0   = _mm256_castpd128_pd256( z_0 );
	x_1   = _mm256_castpd128_pd256( z_1 );
	x_0   = _mm256_permute2f128_pd( x_0, x_0, 0x0 );
	x_1   = _mm256_permute2f128_pd( x_1, x_1, 0x0 );
	temp0 = _mm256_mul_pd( a_40_50_60_70, x_0 );
	temp1 = _mm256_mul_pd( a_41_51_61_71, x_1 );
	z_4_5_6_7 = _mm256_sub_pd( z_4_5_6_7, temp0 );
	z_4_5_6_7 = _mm256_sub_pd( z_4_5_6_7, temp1 );
	
	

	// A_11
	a_00 = _mm_load_sd( &A0[2+lda*2] );
	a_10 = _mm_load_sd( &A0[3+lda*2] );
	a_11 = _mm_load_sd( &A0[3+lda*3] );

	z_0   = _mm_shuffle_pd( z_2_3, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_2_3, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[2], z_0 );
	z_0   = _mm_movedup_pd( z_0 );
	z_1   = _mm_sub_pd( z_1, tmp0 );
	z_1   = _mm_mul_sd( a_11, z_1 );
	_mm_store_sd( &y[3], z_1 );
	z_1   = _mm_movedup_pd( z_1 );

	a_40_50_60_70 = _mm256_load_pd( &A1[0+lda*2] );
	a_41_51_61_71 = _mm256_load_pd( &A1[0+lda*3] );
	x_0   = _mm256_castpd128_pd256( z_0 );
	x_1   = _mm256_castpd128_pd256( z_1 );
	x_0   = _mm256_permute2f128_pd( x_0, x_0, 0x0 );
	x_1   = _mm256_permute2f128_pd( x_1, x_1, 0x0 );
	temp0 = _mm256_mul_pd( a_40_50_60_70, x_0 );
	temp1 = _mm256_mul_pd( a_41_51_61_71, x_1 );
	z_4_5_6_7 = _mm256_sub_pd( z_4_5_6_7, temp0 );
	z_4_5_6_7 = _mm256_sub_pd( z_4_5_6_7, temp1 );



	// A_22
	z_2_3 = _mm256_extractf128_pd( z_4_5_6_7, 0x1 );
	z_0_1 = _mm256_castpd256_pd128( z_4_5_6_7 );

	a_00 = _mm_load_sd( &A1[0+lda*4] );
	a_10 = _mm_load_sd( &A1[1+lda*4] );
	a_11 = _mm_load_sd( &A1[1+lda*5] );

	z_0   = _mm_shuffle_pd( z_0_1, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_0_1, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	a_20_30 = _mm_load_pd( &A1[2+lda*4] );
	a_21_31 = _mm_load_pd( &A1[2+lda*5] );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[4], z_0 );
	z_0   = _mm_movedup_pd( z_0 );
	z_1   = _mm_sub_pd( z_1, tmp0 );
	tmp0  = _mm_mul_pd( a_20_30, z_0 );
	z_1   = _mm_mul_sd( a_11, z_1 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp0 );
	_mm_store_sd( &y[5], z_1 );
	z_1   = _mm_movedup_pd( z_1 );
	tmp1  = _mm_mul_pd( a_21_31, z_1 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp1 );



	// A_33
	a_00 = _mm_load_sd( &A1[2+lda*6] );
	a_10 = _mm_load_sd( &A1[3+lda*6] );
	a_11 = _mm_load_sd( &A1[3+lda*7] );

	z_0   = _mm_shuffle_pd( z_2_3, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_2_3, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[6], z_0 );
/*	z_0   = _mm_movedup_pd( z_0 );*/
	z_1   = _mm_sub_pd( z_1, tmp0 );
	z_1   = _mm_mul_sd( a_11, z_1 );
	_mm_store_sd( &y[7], z_1 );
/*	z_1   = _mm_movedup_pd( z_1 );*/


	}



// it moves horizontally inside a block ( assume ksv>0 !!! )
void kernel_dtrsv_n_4_lib4(int kmax, int ksv, double *A, double *x, double *y)
	{

/*	if(kmax<=0) */
/*		return;*/
	
	const int lda = 4;
	
	int k;

	__m256d
		ax_temp,
		a_00_10_20_30, a_01_11_21_31, a_02_12_22_32, a_03_13_23_33,
		x_0, x_1, x_2, x_3,
		y_0_1_2_3, y_0_1_2_3_b, y_0_1_2_3_c, y_0_1_2_3_d, z_0_1_2_3;
	
	y_0_1_2_3   = _mm256_setzero_pd();	
	y_0_1_2_3_b = _mm256_setzero_pd();	
	y_0_1_2_3_c = _mm256_setzero_pd();	
	y_0_1_2_3_d = _mm256_setzero_pd();	

	k=0;
	for(; k<kmax-3; k+=4)
		{

		x_0 = _mm256_broadcast_sd( &x[0] );
		x_1 = _mm256_broadcast_sd( &x[1] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );

		x_2 = _mm256_broadcast_sd( &x[2] );
		x_3 = _mm256_broadcast_sd( &x[3] );

		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );

		ax_temp = _mm256_mul_pd( a_00_10_20_30, x_0 );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, ax_temp );
		ax_temp = _mm256_mul_pd( a_01_11_21_31, x_1 );
		y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, ax_temp );

		ax_temp = _mm256_mul_pd( a_02_12_22_32, x_2 );
		y_0_1_2_3_c = _mm256_add_pd( y_0_1_2_3_c, ax_temp );
		ax_temp = _mm256_mul_pd( a_03_13_23_33, x_3 );
		y_0_1_2_3_d = _mm256_add_pd( y_0_1_2_3_d, ax_temp );
		
		A += 4*lda;
		x += 4;

		}
	
	y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, y_0_1_2_3_c );
	y_0_1_2_3_b = _mm256_add_pd( y_0_1_2_3_b, y_0_1_2_3_d );
	y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, y_0_1_2_3_b );

	z_0_1_2_3 = _mm256_loadu_pd( &y[0] );
	z_0_1_2_3 = _mm256_sub_pd ( z_0_1_2_3, y_0_1_2_3 );
	
	// solve

	__m128d
		zeros,
		a_00, a_10, a_11, a_20_30, a_21_31,
		z_0, z_1,
		z_0_1, z_2_3, tmp0, tmp1;
	
	zeros = _mm_setzero_pd();
	
	z_2_3 = _mm256_extractf128_pd( z_0_1_2_3, 0x1 );
	z_0_1 = _mm256_castpd256_pd128( z_0_1_2_3 );

	// a_00
	a_00 = _mm_load_sd( &A[0+lda*0] );
	a_10 = _mm_load_sd( &A[1+lda*0] );
	z_0   = _mm_shuffle_pd( z_0_1, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_0_1, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	a_20_30 = _mm_load_pd( &A[2+lda*0] );
	a_21_31 = _mm_load_pd( &A[2+lda*1] );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[0], z_0 );
	z_0   = _mm_movedup_pd( z_0 );
	z_1   = _mm_sub_pd( z_1, tmp0 );
	tmp0  = _mm_mul_pd( a_20_30, z_0 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp0 );
	if(ksv==1)
		{
		_mm_store_sd( &y[1], z_1 );
		_mm_store_pd( &y[2], z_2_3 );
		return;
		}
	
	// a_11
	a_11 = _mm_load_sd( &A[1+lda*1] );
	z_1   = _mm_mul_sd( a_11, z_1 );
	_mm_store_sd( &y[1], z_1 );
	z_1   = _mm_movedup_pd( z_1 );
	tmp1  = _mm_mul_pd( a_21_31, z_1 );
	z_2_3 = _mm_sub_pd( z_2_3, tmp1 );
	if(ksv==2)
		{
		_mm_store_pd( &y[2], z_2_3 );
		return;
		}

	// a_22
	a_00 = _mm_load_sd( &A[2+lda*2] );
	a_10 = _mm_load_sd( &A[3+lda*2] );
	z_0   = _mm_shuffle_pd( z_2_3, zeros, 0x0 );
	z_1   = _mm_shuffle_pd( z_2_3, zeros, 0x1 );
	z_0   = _mm_mul_sd( a_00, z_0 );
	tmp0  = _mm_mul_sd( a_10, z_0 );
	_mm_store_sd( &y[2], z_0 );
/*	z_0   = _mm_movedup_pd( z_0 );*/
	z_1   = _mm_sub_pd( z_1, tmp0 );
	if(ksv==3)
		{
		_mm_store_sd( &y[3], z_1 );
		return;
		}

	// a_33
	a_11 = _mm_load_sd( &A[3+lda*3] );
	z_1   = _mm_mul_sd( a_11, z_1 );
	_mm_store_sd( &y[3], z_1 );
/*	z_1   = _mm_movedup_pd( z_1 );*/
	
		

	}



// it moves vertically across blocks
void kernel_dtrsv_t_4_lib4(int kmax, double *A, int sda, double *x)
	{

	if(kmax<=0) 
		return;
	
	const int lda = 4;
	
/*	__builtin_prefetch( A + 0*lda );*/
/*	__builtin_prefetch( A + 2*lda );*/

	double *tA, *tx;
	tA = A;
	tx = x;

	int k;
/*	int ka = kmax-kna; // number from aligned positon*/
	
	__m256d
		tmp0, tmp1,
		a_00_10_20_30, a_01_11_21_31, a_02_12_22_32, a_03_13_23_33,
		x_0_1_2_3,
		y_00, y_11, y_22, y_33;
	
	y_00 = _mm256_setzero_pd();
	y_11 = _mm256_setzero_pd();
	y_22 = _mm256_setzero_pd();
	y_33 = _mm256_setzero_pd();
	
	k=4;
	A += 4 + (sda-1)*lda;
	x += 4;
	for(; k<kmax-4; k+=8) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		y_33 = _mm256_add_pd( y_33, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;


/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		y_33 = _mm256_add_pd( y_33, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	for(; k<kmax; k+=4) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		y_33 = _mm256_add_pd( y_33, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	
	A = tA;
	x = tx;

	__m128d
/*		tmp,*/
		a_00, a_10, a_11, a_20_30, a_21_31,
		y_2_3,
		z_0, z_1, z_2, z_3,
		y_0, y_1, y_2, y_3;
	
	y_0 = _mm256_extractf128_pd( y_00, 0x1 );
	y_1 = _mm256_extractf128_pd( y_11, 0x1 );
	y_2 = _mm256_extractf128_pd( y_22, 0x1 );
	y_3 = _mm256_extractf128_pd( y_33, 0x1 );
	
	y_0 = _mm_add_pd( y_0, _mm256_castpd256_pd128( y_00 ) );
	y_1 = _mm_add_pd( y_1, _mm256_castpd256_pd128( y_11 ) );
	y_2 = _mm_add_pd( y_2, _mm256_castpd256_pd128( y_22 ) );
	y_3 = _mm_add_pd( y_3, _mm256_castpd256_pd128( y_33 ) );
	
	// bottom trinagle
	z_3  = _mm_load_sd( &x[3] );
	y_3  = _mm_hadd_pd( y_3, y_3 );
	a_11 = _mm_load_sd( &A[3+lda*3] );
	y_3  = _mm_sub_sd( z_3, y_3 );
	y_3  = _mm_mul_sd( y_3, a_11 );
	_mm_store_sd( &x[3], y_3 );

	a_10 = _mm_load_sd( &A[3+lda*2] );
	a_10 = _mm_mul_sd( a_10, y_3 );
	z_2  = _mm_load_sd( &x[2] );
	y_2  = _mm_hadd_pd( y_2, y_2 );
	z_2  = _mm_sub_sd( z_2, a_10 );
	a_00 = _mm_load_sd( &A[2+lda*2] );
	y_2  = _mm_sub_sd( z_2, y_2 );
	y_2  = _mm_mul_sd( y_2, a_00 );
	_mm_store_sd( &x[2], y_2 );

	// square
	y_2_3   = _mm_shuffle_pd( y_2, y_3, 0x0 );
	a_20_30 = _mm_load_pd( &A[2+lda*0] );
	a_21_31 = _mm_load_pd( &A[2+lda*1] );
	a_20_30 = _mm_mul_pd( a_20_30, y_2_3 );
	a_21_31 = _mm_mul_pd( a_21_31, y_2_3 );
	y_0     = _mm_add_pd( y_0, a_20_30 );
	y_1     = _mm_add_pd( y_1, a_21_31 );
		
	// top trinagle
	z_1  = _mm_load_sd( &x[1] );
	y_1  = _mm_hadd_pd( y_1, y_1 );
	a_11 = _mm_load_sd( &A[1+lda*1] );
	y_1  = _mm_sub_sd( z_1, y_1 );
	y_1  = _mm_mul_sd( y_1, a_11 );
	_mm_store_sd( &x[1], y_1 );

	a_10 = _mm_load_sd( &A[1+lda*0] );
	a_10 = _mm_mul_sd( a_10, y_1 );
	z_0  = _mm_load_sd( &x[0] );
	y_0  = _mm_hadd_pd( y_0, y_0 );
	z_0  = _mm_sub_sd( z_0, a_10 );
	a_00 = _mm_load_sd( &A[0+lda*0] );
	y_0  = _mm_sub_sd( z_0, y_0 );
	y_0  = _mm_mul_sd( y_0, a_00 );
	_mm_store_sd( &x[0], y_0 );

	}



// it moves vertically across blocks
void kernel_dtrsv_t_3_lib4(int kmax, double *A, int sda, double *x)
	{

	if(kmax<=0) 
		return;
	
	const int lda = 4;
	
/*	__builtin_prefetch( A + 0*lda );*/
/*	__builtin_prefetch( A + 2*lda );*/

	double *tA, *tx;
	tA = A;
	tx = x;

	int k;
/*	int ka = kmax-kna; // number from aligned positon*/
	
	__m256d
		zeros,
		tmp0, tmp1,
		a_00_10_20_30, a_01_11_21_31, a_02_12_22_32,
		x_0_1_2_3,
		y_00, y_11, y_22;
	
	zeros = _mm256_setzero_pd();

	y_00 = _mm256_setzero_pd();
	y_11 = _mm256_setzero_pd();
	y_22 = _mm256_setzero_pd();
	
	// clean up at the beginning
	x_0_1_2_3 = _mm256_loadu_pd( &x[0] );
	x_0_1_2_3 = _mm256_blend_pd( x_0_1_2_3, zeros, 0x7 );

	a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
	a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
	a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
	
	tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
	tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
	y_00 = _mm256_add_pd( y_00, tmp0 );
	y_11 = _mm256_add_pd( y_11, tmp1 );
	tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
	y_22 = _mm256_add_pd( y_22, tmp0 );

	A += 4 + (sda-1)*lda;
	x += 4;

	k=4;
	for(; k<kmax-4; k+=8) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;


/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	for(; k<kmax; k+=4) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		tmp0 = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	
	A = tA;
	x = tx;

	__m128d
/*		tmp,*/
		a_00, a_10, a_11, a_20, a_21,
		y_2_3,
		z_0, z_1, z_2,
		y_0, y_1, y_2;
	
	y_0 = _mm256_extractf128_pd( y_00, 0x1 );
	y_1 = _mm256_extractf128_pd( y_11, 0x1 );
	y_2 = _mm256_extractf128_pd( y_22, 0x1 );
	
	y_0 = _mm_add_pd( y_0, _mm256_castpd256_pd128( y_00 ) );
	y_1 = _mm_add_pd( y_1, _mm256_castpd256_pd128( y_11 ) );
	y_2 = _mm_add_pd( y_2, _mm256_castpd256_pd128( y_22 ) );
	
	// bottom trinagle
	z_2  = _mm_load_sd( &x[2] );
	y_2  = _mm_hadd_pd( y_2, y_2 );
	a_00 = _mm_load_sd( &A[2+lda*2] );
	y_2  = _mm_sub_sd( z_2, y_2 );
	y_2  = _mm_mul_sd( y_2, a_00 );
	_mm_store_sd( &x[2], y_2 );

	// square
	a_20 = _mm_load_sd( &A[2+lda*0] );
	a_21 = _mm_load_sd( &A[2+lda*1] );
	a_20 = _mm_mul_sd( a_20, y_2 );
	a_21 = _mm_mul_sd( a_21, y_2 );
	y_0  = _mm_add_sd( y_0, a_20 );
	y_1  = _mm_add_sd( y_1, a_21 );
		
	// top trinagle
	z_1  = _mm_load_sd( &x[1] );
	y_1  = _mm_hadd_pd( y_1, y_1 );
	a_11 = _mm_load_sd( &A[1+lda*1] );
	y_1  = _mm_sub_sd( z_1, y_1 );
	y_1  = _mm_mul_sd( y_1, a_11 );
	_mm_store_sd( &x[1], y_1 );

	a_10 = _mm_load_sd( &A[1+lda*0] );
	a_10 = _mm_mul_sd( a_10, y_1 );
	z_0  = _mm_load_sd( &x[0] );
	y_0  = _mm_hadd_pd( y_0, y_0 );
	z_0  = _mm_sub_sd( z_0, a_10 );
	a_00 = _mm_load_sd( &A[0+lda*0] );
	y_0  = _mm_sub_sd( z_0, y_0 );
	y_0  = _mm_mul_sd( y_0, a_00 );
	_mm_store_sd( &x[0], y_0 );

	}



// it moves vertically across blocks (A is supposed to be aligned)
void kernel_dtrsv_t_2_lib4(int kmax, double *A, int sda, double *x)
	{

	if(kmax<=0) 
		return;
	
	const int lda = 4;
	
/*	__builtin_prefetch( A + 0*lda );*/
/*	__builtin_prefetch( A + 2*lda );*/

	double *tA, *tx;
	tA = A;
	tx = x;

	int k;
/*	int ka = kmax-kna; // number from aligned positon*/
	
	__m256d
		zeros,
		tmp0, tmp1,
		a_00_10_20_30, a_01_11_21_31,
		x_0_1_2_3,
		y_00, y_11;
	
	zeros = _mm256_setzero_pd();

	y_00 = _mm256_setzero_pd();
	y_11 = _mm256_setzero_pd();
	
	// clean up at the beginning
	x_0_1_2_3 = _mm256_loadu_pd( &x[0] );
	x_0_1_2_3 = _mm256_blend_pd( x_0_1_2_3, zeros, 0x3 );

	a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
	a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
	
	tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
	tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
	y_00 = _mm256_add_pd( y_00, tmp0 );
	y_11 = _mm256_add_pd( y_11, tmp1 );

	A += 4 + (sda-1)*lda;
	x += 4;

	k=4;
	for(; k<kmax-4; k+=8) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;


/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	for(; k<kmax; k+=4) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		tmp1 = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		y_11 = _mm256_add_pd( y_11, tmp1 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	
	A = tA;
	x = tx;

	__m128d
/*		tmp,*/
		a_00, a_10, a_11,
		z_0, z_1,
		y_0, y_1;
	
	y_0 = _mm256_extractf128_pd( y_00, 0x1 );
	y_1 = _mm256_extractf128_pd( y_11, 0x1 );
	
	y_0 = _mm_add_pd( y_0, _mm256_castpd256_pd128( y_00 ) );
	y_1 = _mm_add_pd( y_1, _mm256_castpd256_pd128( y_11 ) );
	
	//
	
	// bottom trinagle
	z_1  = _mm_load_sd( &x[1] );
	y_1  = _mm_hadd_pd( y_1, y_1 );
	a_11 = _mm_load_sd( &A[1+lda*1] );
	y_1  = _mm_sub_sd( z_1, y_1 );
	y_1  = _mm_mul_sd( y_1, a_11 );
	_mm_store_sd( &x[1], y_1 );

	a_10 = _mm_load_sd( &A[1+lda*0] );
	a_10 = _mm_mul_sd( a_10, y_1 );
	z_0  = _mm_load_sd( &x[0] );
	y_0  = _mm_hadd_pd( y_0, y_0 );
	z_0  = _mm_sub_sd( z_0, a_10 );
	a_00 = _mm_load_sd( &A[0+lda*0] );
	y_0  = _mm_sub_sd( z_0, y_0 );
	y_0  = _mm_mul_sd( y_0, a_00 );
	_mm_store_sd( &x[0], y_0 );

	}



// it moves vertically across blocks
void kernel_dtrsv_t_1_lib4(int kmax, double *A, int sda, double *x)
	{

	if(kmax<=0) 
		return;
	
	const int lda = 4;
	
/*	__builtin_prefetch( A + 0*lda );*/
/*	__builtin_prefetch( A + 2*lda );*/

	double *tA, *tx;
	tA = A;
	tx = x;

	int k;
/*	int ka = kmax-kna; // number from aligned positon*/
	
	__m256d
		zeros,
		tmp0,
		a_00_10_20_30,
		x_0_1_2_3,
		y_00;
	
	zeros = _mm256_setzero_pd();

	y_00 = _mm256_setzero_pd();
	
	// clean up at the beginning
	x_0_1_2_3 = _mm256_loadu_pd( &x[0] );
	x_0_1_2_3 = _mm256_blend_pd( x_0_1_2_3, zeros, 0x1 );

	a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
	
	tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
	y_00 = _mm256_add_pd( y_00, tmp0 );

	A += 4 + (sda-1)*lda;
	x += 4;

	k=4;
	for(; k<kmax-4; k+=8) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;


/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	for(; k<kmax; k+=4) // TODO correct end & mask !!!!!!!!!!!
		{
		
/*		__builtin_prefetch( A + sda*lda + 0*lda );*/
/*		__builtin_prefetch( A + sda*lda + 2*lda );*/

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		
		tmp0 = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, tmp0 );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	
	A = tA;
	x = tx;

	__m128d
/*		tmp,*/
		a_00,
		z_0,
		y_0;
	
	y_0 = _mm256_extractf128_pd( y_00, 0x1 );
	
	y_0 = _mm_add_pd( y_0, _mm256_castpd256_pd128( y_00 ) );
	
	// bottom trinagle
	z_0  = _mm_load_sd( &x[0] );
	y_0  = _mm_hadd_pd( y_0, y_0 );
	a_00 = _mm_load_sd( &A[0+lda*0] );
	y_0  = _mm_sub_sd( z_0, y_0 );
	y_0  = _mm_mul_sd( y_0, a_00 );
	_mm_store_sd( &x[0], y_0 );

	}

