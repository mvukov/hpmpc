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




// transpose an aligned upper triangular matrix in an aligned lower triangular matrix
void kernel_dtrtr_u_4_lib4(int kmax, double *A, double *C, int sdc)
	{

	const int bs = 4;

	int k;

	C[0+bs*0] = A[0+bs*0];

	C[1+bs*0] = A[0+bs*1];
	C[1+bs*1] = A[1+bs*1];

	C[2+bs*0] = A[0+bs*2];
	C[2+bs*1] = A[1+bs*2];
	C[2+bs*2] = A[2+bs*2];

	C[3+bs*0] = A[0+bs*3];
	C[3+bs*1] = A[1+bs*3];
	C[3+bs*2] = A[2+bs*3];
	C[3+bs*3] = A[3+bs*3];

	C += bs*sdc;
	A += bs*bs;

	k = 4;
	for( ; k<kmax-3; k+=4)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];
		C[0+bs*3] = A[3+bs*0];

		C[1+bs*0] = A[0+bs*1];
		C[1+bs*1] = A[1+bs*1];
		C[1+bs*2] = A[2+bs*1];
		C[1+bs*3] = A[3+bs*1];

		C[2+bs*0] = A[0+bs*2];
		C[2+bs*1] = A[1+bs*2];
		C[2+bs*2] = A[2+bs*2];
		C[2+bs*3] = A[3+bs*2];

		C[3+bs*0] = A[0+bs*3];
		C[3+bs*1] = A[1+bs*3];
		C[3+bs*2] = A[2+bs*3];
		C[3+bs*3] = A[3+bs*3];

		C += bs*sdc;
		A += bs*bs;
		}
	
	for( ; k<kmax; k++)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];
		C[0+bs*3] = A[3+bs*0];

		C += 1;
		A += bs;
		}

	}



// transposed of general matrices, read along panels, write across panels TODO test if it is the best way
void kernel_dgetr_4_lib4(int kmax, int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;
	
	int k;

	k = 0;
	if(kna>0)
		{
		for( ; k<kna; k++)
			{
			C[0+bs*0] = A[0+bs*0];
			C[0+bs*1] = A[1+bs*0];
			C[0+bs*2] = A[2+bs*0];
			C[0+bs*3] = A[3+bs*0];

			C += 1;
			A += bs;
			}
		C += bs*(sdc-1);
		}
	
	for( ; k<kmax-3; k+=4)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];
		C[0+bs*3] = A[3+bs*0];

		C[1+bs*0] = A[0+bs*1];
		C[1+bs*1] = A[1+bs*1];
		C[1+bs*2] = A[2+bs*1];
		C[1+bs*3] = A[3+bs*1];

		C[2+bs*0] = A[0+bs*2];
		C[2+bs*1] = A[1+bs*2];
		C[2+bs*2] = A[2+bs*2];
		C[2+bs*3] = A[3+bs*2];

		C[3+bs*0] = A[0+bs*3];
		C[3+bs*1] = A[1+bs*3];
		C[3+bs*2] = A[2+bs*3];
		C[3+bs*3] = A[3+bs*3];

		C += bs*sdc;
		A += bs*bs;
		}
	for( ; k<kmax; k++)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];
		C[0+bs*3] = A[3+bs*0];

		C += 1;
		A += bs;
		}

	}



// transposed of general matrices, read along panels, write across panels TODO test if it is the best way
void kernel_dgetr_3_lib4(int kmax, int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;
	
	int k;

	k = 0;
	if(kna>0)
		{
		for( ; k<kna; k++)
			{
			C[0+bs*0] = A[0+bs*0];
			C[0+bs*1] = A[1+bs*0];
			C[0+bs*2] = A[2+bs*0];

			C += 1;
			A += bs;
			}
		C += bs*(sdc-1);
		}
	
	for( ; k<kmax-3; k+=4)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];

		C[1+bs*0] = A[0+bs*1];
		C[1+bs*1] = A[1+bs*1];
		C[1+bs*2] = A[2+bs*1];

		C[2+bs*0] = A[0+bs*2];
		C[2+bs*1] = A[1+bs*2];
		C[2+bs*2] = A[2+bs*2];

		C[3+bs*0] = A[0+bs*3];
		C[3+bs*1] = A[1+bs*3];
		C[3+bs*2] = A[2+bs*3];

		C += bs*sdc;
		A += bs*bs;
		}
	for( ; k<kmax; k++)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];
		C[0+bs*2] = A[2+bs*0];

		C += 1;
		A += bs;
		}

	}



// transposed of general matrices, read along panels, write across panels TODO test if it is the best way
void kernel_dgetr_2_lib4(int kmax, int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;
	
	int k;

	k = 0;
	if(kna>0)
		{
		for( ; k<kna; k++)
			{
			C[0+bs*0] = A[0+bs*0];
			C[0+bs*1] = A[1+bs*0];

			C += 1;
			A += bs;
			}
		C += bs*(sdc-1);
		}
	
	for( ; k<kmax-3; k+=4)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];

		C[1+bs*0] = A[0+bs*1];
		C[1+bs*1] = A[1+bs*1];

		C[2+bs*0] = A[0+bs*2];
		C[2+bs*1] = A[1+bs*2];

		C[3+bs*0] = A[0+bs*3];
		C[3+bs*1] = A[1+bs*3];

		C += bs*sdc;
		A += bs*bs;
		}
	for( ; k<kmax; k++)
		{
		C[0+bs*0] = A[0+bs*0];
		C[0+bs*1] = A[1+bs*0];

		C += 1;
		A += bs;
		}

	}



// transposed of general matrices, read along panels, write across panels TODO test if it is the best way
void kernel_dgetr_1_lib4(int kmax, int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;
	
	int k;

	k = 0;
	if(kna>0)
		{
		for( ; k<kna; k++)
			{
			C[0+bs*0] = A[0+bs*0];

			C += 1;
			A += bs;
			}
		C += bs*(sdc-1);
		}
	
	for( ; k<kmax-3; k+=4)
		{
		C[0+bs*0] = A[0+bs*0];

		C[1+bs*0] = A[0+bs*1];

		C[2+bs*0] = A[0+bs*2];

		C[3+bs*0] = A[0+bs*3];

		C += bs*sdc;
		A += bs*bs;
		}
	for( ; k<kmax; k++)
		{
		C[0+bs*0] = A[0+bs*0];

		C += 1;
		A += bs;
		}

	}



void kernel_dtran_4_lib4(int kmax, int kna, double *A, int sda, double *C) // TODO 8 ???
	{
	
	// kmax is at least 4 !!!
	
	int k;

	const int bs = 4;
	
	__m128d
		u0, u1, u2, u3, u4, u5, u6, u7;

	__m256d
		v0, v1, v2, v3, v4, v5, v6, v7;
	
	k=0;

	if(kna==0)
		{
		
		// top 2x2 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );
		u1 = _mm_load_sd( &A[1+bs*0] ); // 10
		u1 = _mm_loadh_pd( u1, &A[1+bs*1] ); // 10 11
		_mm_store_pd( &C[0+bs*1], u1 );
		
		// 2x2 square
		u2 = _mm_load_pd( &A[2+bs*0] ); // 20 30
		u3 = _mm_load_pd( &A[2+bs*1] ); // 21 31
		u4 = _mm_unpacklo_pd( u2, u3 ); // 20 21
		u5 = _mm_unpackhi_pd( u2, u3 ); // 30 31
		_mm_store_pd( &C[0+bs*2], u4 );
		_mm_store_pd( &C[0+bs*3], u5 );
		
		// low 2x2 triangle
		u0 = _mm_load_sd( &A[2+bs*2] ); // 22
		_mm_store_sd( &C[2+bs*2], u0 );
		u1 = _mm_load_sd( &A[3+bs*2] ); // 32
		u1 = _mm_loadh_pd( u1, &A[3+bs*3] ); // 32 33
		_mm_store_pd( &C[2+bs*3], u1 );
		
		A += 4*sda;
		C += 4*bs;
		k += 4;
		
		}
	else if(kna==1)
		{
		
		// top 1x1 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );
		
		A += 1 + bs*(sda-1);
		C += bs;
		k += 1;

		// bottom 1x1 triangle
		u0 = _mm_load_sd( &A[1+bs*2] ); // 00
		_mm_store_sd( &C[2+bs*1], u0 );

		// 4x4
		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		u2 = _mm_load_pd( &A[2+bs*2] ); // 22 32
		u3 = _mm_load_pd( &A[2+bs*3] ); // 23 33

		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		u4 = _mm_unpacklo_pd( u2, u3 ); // 22 23
		u5 = _mm_unpackhi_pd( u2, u3 ); // 32 33

		_mm_store_pd( &C[0+bs*0], _mm256_castpd256_pd128( v4 ) );
		_mm_store_pd( &C[0+bs*1], _mm256_castpd256_pd128( v5 ) );
		v2 = _mm256_permute2f128_pd( v4, _mm256_castpd128_pd256( u4 ), 0x21 );
		v3 = _mm256_permute2f128_pd( v5, _mm256_castpd128_pd256( u5 ), 0x21 );
		_mm256_store_pd( &C[0+bs*2], v2 );
		if(kmax==4)
			return;
		_mm256_store_pd( &C[0+bs*3], v3 );

		A += bs*sda;
		C += 4*bs;
		k += 4;

		}
	else if(kna==2)
		{

		// top 2x2 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );
		u1 = _mm_load_sd( &A[1+bs*0] ); // 10
		u1 = _mm_loadh_pd( u1, &A[1+bs*1] ); // 10 11
		_mm_store_pd( &C[0+bs*1], u1 );

		A += 2 + bs*(sda-1);
		C += 2*bs;
		k += 2;

		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		v2 = _mm256_load_pd( &A[0+bs*2] ); // 02 12 22 32
		v3 = _mm256_load_pd( &A[0+bs*3] ); // 03 13 23 33
		
		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		v6 = _mm256_unpacklo_pd( v2, v3 ); // 02 03 22 23
		v7 = _mm256_unpackhi_pd( v2, v3 ); // 12 13 32 33
		
		v0 = _mm256_permute2f128_pd( v4, v6, 0x20 ); // 00 01 02 03
		v2 = _mm256_permute2f128_pd( v4, v6, 0x31 ); // 20 21 22 23
		v1 = _mm256_permute2f128_pd( v5, v7, 0x20 ); // 10 11 12 13
		v3 = _mm256_permute2f128_pd( v5, v7, 0x31 ); // 30 31 32 33
		
		//_mm256_store_pd( &C[0+bs*0], v0 );
		_mm_store_pd( &C[0+bs*0], _mm256_castpd256_pd128( v0 ) );
		_mm_storel_pd( &C[2+bs*0], _mm256_extractf128_pd( v0, 0x1 ) );
		_mm256_store_pd( &C[0+bs*1], v1 );
		if(kmax==4)
			return;
		_mm256_store_pd( &C[0+bs*2], v2 );
		if(kmax==5)
			return;
		_mm256_store_pd( &C[0+bs*3], v3 );

		A += bs*sda;
		C += 4*bs;
		k += 4;

		}
	else // if(kna==3)
		{

		// top 1x1 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );

		// 2x2 square
		u2 = _mm_load_pd( &A[1+bs*0] ); // 20 30
		u3 = _mm_load_pd( &A[1+bs*1] ); // 21 31
		u4 = _mm_unpacklo_pd( u2, u3 ); // 20 21
		u5 = _mm_unpackhi_pd( u2, u3 ); // 30 31
		_mm_store_pd( &C[0+bs*1], u4 );
		_mm_store_pd( &C[0+bs*2], u5 );

		// low 1x1 triangle
		u0 = _mm_load_sd( &A[2+bs*2] ); // 22
		_mm_store_sd( &C[2+bs*2], u0 );

		A += 3 + bs*(sda-1);
		C += 3*bs;
		k += 3;

		}

	for(; k<kmax-7; k+=8)
		{
		
		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		v2 = _mm256_load_pd( &A[0+bs*2] ); // 02 12 22 32
		v3 = _mm256_load_pd( &A[0+bs*3] ); // 03 13 23 33
		v6 = _mm256_unpacklo_pd( v2, v3 ); // 02 03 22 23
		v7 = _mm256_unpackhi_pd( v2, v3 ); // 12 13 32 33
		
		A += bs*sda;

		v0 = _mm256_permute2f128_pd( v4, v6, 0x20 ); // 00 01 02 03
		_mm256_store_pd( &C[0+bs*0], v0 );
		v2 = _mm256_permute2f128_pd( v4, v6, 0x31 ); // 20 21 22 23
		_mm256_store_pd( &C[0+bs*2], v2 );
		v1 = _mm256_permute2f128_pd( v5, v7, 0x20 ); // 10 11 12 13
		_mm256_store_pd( &C[0+bs*1], v1 );
		v3 = _mm256_permute2f128_pd( v5, v7, 0x31 ); // 30 31 32 33
		_mm256_store_pd( &C[0+bs*3], v3 );
		
		C += 4*bs;

		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		v2 = _mm256_load_pd( &A[0+bs*2] ); // 02 12 22 32
		v3 = _mm256_load_pd( &A[0+bs*3] ); // 03 13 23 33
		v6 = _mm256_unpacklo_pd( v2, v3 ); // 02 03 22 23
		v7 = _mm256_unpackhi_pd( v2, v3 ); // 12 13 32 33
		
		A += bs*sda;

		v0 = _mm256_permute2f128_pd( v4, v6, 0x20 ); // 00 01 02 03
		_mm256_store_pd( &C[0+bs*0], v0 );
		v2 = _mm256_permute2f128_pd( v4, v6, 0x31 ); // 20 21 22 23
		_mm256_store_pd( &C[0+bs*2], v2 );
		v1 = _mm256_permute2f128_pd( v5, v7, 0x20 ); // 10 11 12 13
		_mm256_store_pd( &C[0+bs*1], v1 );
		v3 = _mm256_permute2f128_pd( v5, v7, 0x31 ); // 30 31 32 33
		_mm256_store_pd( &C[0+bs*3], v3 );
		
		C += 4*bs;

		}
	for(; k<kmax-3; k+=4)
		{
		
		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		v2 = _mm256_load_pd( &A[0+bs*2] ); // 02 12 22 32
		v3 = _mm256_load_pd( &A[0+bs*3] ); // 03 13 23 33
		v6 = _mm256_unpacklo_pd( v2, v3 ); // 02 03 22 23
		v7 = _mm256_unpackhi_pd( v2, v3 ); // 12 13 32 33
		
		A += bs*sda;

		v0 = _mm256_permute2f128_pd( v4, v6, 0x20 ); // 00 01 02 03
		_mm256_store_pd( &C[0+bs*0], v0 );
		v2 = _mm256_permute2f128_pd( v4, v6, 0x31 ); // 20 21 22 23
		_mm256_store_pd( &C[0+bs*2], v2 );
		v1 = _mm256_permute2f128_pd( v5, v7, 0x20 ); // 10 11 12 13
		_mm256_store_pd( &C[0+bs*1], v1 );
		v3 = _mm256_permute2f128_pd( v5, v7, 0x31 ); // 30 31 32 33
		_mm256_store_pd( &C[0+bs*3], v3 );
		
		C += 4*bs;

		}

	if(k==kmax)
		return;

	if(kmax-k==1)
		{
		
		u0 = _mm_load_sd( &A[0+bs*0] );
		u0 = _mm_loadh_pd( u0, &A[0+bs*1] );
		_mm_store_pd( &C[0+bs*0], u0 );

		u0 = _mm_load_sd( &A[0+bs*2] );
		u0 = _mm_loadh_pd( u0, &A[0+bs*3] );
		_mm_store_pd( &C[2+bs*0], u0 );

		}
	else if(kmax-k==2)
		{
		
		u0 = _mm_load_pd( &A[0+bs*0] ); //      
		u1 = _mm_load_pd( &A[0+bs*1] ); //      
		u2 = _mm_load_pd( &A[0+bs*2] ); //      
		u3 = _mm_load_pd( &A[0+bs*3] ); //      

		u4 = _mm_unpacklo_pd( u0, u1 ); //      
		u5 = _mm_unpackhi_pd( u0, u1 ); //      
		u6 = _mm_unpacklo_pd( u2, u3 ); //      
		u7 = _mm_unpackhi_pd( u2, u3 ); //      

		v0 = _mm256_permute2f128_pd( _mm256_castpd128_pd256( u4 ), _mm256_castpd128_pd256( u6 ), 0x20 ); // 00 01 02 03
		v1 = _mm256_permute2f128_pd( _mm256_castpd128_pd256( u5 ), _mm256_castpd128_pd256( u7 ), 0x20 ); // 10 11 12 13

		_mm256_store_pd( &C[0+bs*0], v0 );
		_mm256_store_pd( &C[0+bs*1], v1 );

		}
	else // if(kmax-k==3)
		{

		v0 = _mm256_load_pd( &A[0+bs*0] ); // 00 10 20 30
		v1 = _mm256_load_pd( &A[0+bs*1] ); // 01 11 21 31
		v2 = _mm256_load_pd( &A[0+bs*2] ); // 02 12 22 32
		v3 = _mm256_load_pd( &A[0+bs*3] ); // 03 13 23 33
		
		v4 = _mm256_unpacklo_pd( v0, v1 ); // 00 01 20 21
		v5 = _mm256_unpackhi_pd( v0, v1 ); // 10 11 30 31
		v6 = _mm256_unpacklo_pd( v2, v3 ); // 02 03 22 23
		v7 = _mm256_unpackhi_pd( v2, v3 ); // 12 13 32 33
		
		v0 = _mm256_permute2f128_pd( v4, v6, 0x20 ); // 00 01 02 03
		v2 = _mm256_permute2f128_pd( v4, v6, 0x31 ); // 20 21 22 23
		v1 = _mm256_permute2f128_pd( v5, v7, 0x20 ); // 10 11 12 13
//		v3 = _mm256_permute2f128_pd( v5, v7, 0x31 ); // 30 31 32 33

		_mm256_store_pd( &C[0+bs*0], v0 );
		_mm256_store_pd( &C[0+bs*1], v1 );
		_mm256_store_pd( &C[0+bs*2], v2 );
//		_mm256_store_pd( &C[0+bs*3], v3 );

		}

	return;
	
	}



void corner_dtran_3_lib4(int kna, double *A, int sda, double *C)
	{

	const int bs = 4;
	
	__m128d
		u0, u1, u2, u3, u4, u5;

/*	k=0;*/

	if(kna==0)
		{
		
		u0 = _mm_load_sd( &A[0+bs*0] );
		_mm_store_sd( &C[0+bs*0], u0 );
		
		u1 = _mm_load_sd( &A[1+bs*0] );
		u1 = _mm_loadh_pd( u1, &A[1+bs*1] );
		_mm_store_pd( &C[0+bs*1], u1 );

		u2 = _mm_load_sd( &A[2+bs*0] );
		u2 = _mm_loadh_pd( u2, &A[2+bs*1] );
		_mm_store_pd( &C[0+bs*2], u2 );

		u3 = _mm_load_sd( &A[2+bs*2] );
		_mm_store_sd( &C[2+bs*2], u3 );

		}
	else if(kna==1)
		{
		
		// top 1x1 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );
		
		A += 1 + bs*(sda-1);
		C += bs;
//		k += 1;

		// 2x2
		u0 = _mm_load_pd( &A[0+bs*0] ); // 
		u1 = _mm_load_pd( &A[0+bs*1] ); // 

		u4 = _mm_unpacklo_pd( u0, u1 ); // 
		u5 = _mm_unpackhi_pd( u0, u1 ); // 

		_mm_store_pd( &C[0+bs*0], u4 );
		_mm_store_pd( &C[0+bs*1], u5 );

		// bottom 1x1 triangle
		u0 = _mm_load_sd( &A[1+bs*2] ); // 00
		_mm_store_sd( &C[2+bs*1], u0 );
//		printf("\n%f\n", C[2+bs*1]);

		}
	else if(kna==2)
		{

		u0 = _mm_load_sd( &A[0+bs*0] );
		_mm_store_sd( &C[0+bs*0], u0 );
		
		u1 = _mm_load_sd( &A[1+bs*0] );
		u1 = _mm_loadh_pd( u1, &A[1+bs*1] );
		_mm_store_pd( &C[0+bs*1], u1 );

		A += 2 + bs*(sda-1);
		C += 2*bs;
//		k += 2;

		u2 = _mm_load_sd( &A[0+bs*0] );
		u2 = _mm_loadh_pd( u2, &A[0+bs*1] );
		_mm_store_pd( &C[0+bs*0], u2 );

		u3 = _mm_load_sd( &A[0+bs*2] );
		_mm_store_sd( &C[2+bs*0], u3 );

		}
	else // if(kna==3)
		{

		// top 1x1 triangle
		u0 = _mm_load_sd( &A[0+bs*0] ); // 00
		_mm_store_sd( &C[0+bs*0], u0 );
		
		// 2x2
		u0 = _mm_load_pd( &A[1+bs*0] ); // 
		u1 = _mm_load_pd( &A[1+bs*1] ); // 

		u4 = _mm_unpacklo_pd( u0, u1 ); // 
		u5 = _mm_unpackhi_pd( u0, u1 ); // 

		_mm_store_pd( &C[0+bs*1], u4 );
		_mm_store_pd( &C[0+bs*2], u5 );

		// bottom 1x1 triangle
		u0 = _mm_load_sd( &A[2+bs*2] ); // 00
		_mm_store_sd( &C[2+bs*2], u0 );

		}

	}



void corner_dtran_2_lib4(int kna, double *A, int sda, double *C)
	{

	const int bs = 4;
	
	__m128d
		u0, u1, u2, u3, u4, u5;

/*	k=0;*/

	if(kna==1)
		{

		u0 = _mm_load_sd( &A[0+bs*0] );
		_mm_store_sd( &C[0+bs*0], u0 );
		
		A += 1 + bs*(sda-1);
		C += bs;
//		k += 1;

		u1 = _mm_load_sd( &A[0+bs*0] );
		u1 = _mm_loadh_pd( u1, &A[0+bs*1] );
		_mm_store_pd( &C[0+bs*0], u1 );

		}
	else // if(kna==3)
		{
		
		u0 = _mm_load_sd( &A[0+bs*0] );
		_mm_store_sd( &C[0+bs*0], u0 );
		
		u1 = _mm_load_sd( &A[1+bs*0] );
		u1 = _mm_loadh_pd( u1, &A[1+bs*1] );
		_mm_store_pd( &C[0+bs*1], u1 );

		}

	}



// mis-align a triangolar matrix; it moves across panels; read aligned, write mis-aligned
void kernel_dtrma_4_lib4(int kmax, int kna, double *A, int sda, double *C, int sdc)
	{

	// assume kmax >= 4 !!!

	const int bs = 4;

	int k;

	if(kna==0) // same alignment
		{

		// triangle at the beginning
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];
		C[2+bs*0] = A[2+bs*0];
		C[3+bs*0] = A[3+bs*0];

		C[1+bs*1] = A[1+bs*1];
		C[2+bs*1] = A[2+bs*1];
		C[3+bs*1] = A[3+bs*1];

		C[2+bs*2] = A[2+bs*2];
		C[3+bs*2] = A[3+bs*2];

		C[3+bs*3] = A[3+bs*3];

		A += bs*sda;
		C += bs*sdc;
		k = 4;

		// main loop
		for( ; k<kmax-3; k+=4)
			{
			C[0+bs*0] = A[0+bs*0];
			C[1+bs*0] = A[1+bs*0];
			C[2+bs*0] = A[2+bs*0];
			C[3+bs*0] = A[3+bs*0];

			C[0+bs*1] = A[0+bs*1];
			C[1+bs*1] = A[1+bs*1];
			C[2+bs*1] = A[2+bs*1];
			C[3+bs*1] = A[3+bs*1];

			C[0+bs*2] = A[0+bs*2];
			C[1+bs*2] = A[1+bs*2];
			C[2+bs*2] = A[2+bs*2];
			C[3+bs*2] = A[3+bs*2];

			C[0+bs*3] = A[0+bs*3];
			C[1+bs*3] = A[1+bs*3];
			C[2+bs*3] = A[2+bs*3];
			C[3+bs*3] = A[3+bs*3];

			A += bs*sda;
			C += bs*sdc;
			}

		// clean-up loop
		for( ; k<kmax; k++)
			{
			C[0+bs*0] = A[0+bs*0];

			C[0+bs*1] = A[0+bs*1];

			C[0+bs*2] = A[0+bs*2];

			C[0+bs*3] = A[0+bs*3];

			A += 1;
			C += 1;
			}

		return;

		}
	else if(kna==1)
		{

		// one row in the first C panel
		C[0+bs*0] = A[0+bs*0];

		C += 1 + bs*(sdc-1);

		C[0+bs*0] = A[1+bs*0];
		C[1+bs*0] = A[2+bs*0];
		C[2+bs*0] = A[3+bs*0];

		C[0+bs*1] = A[1+bs*1];
		C[1+bs*1] = A[2+bs*1];
		C[2+bs*1] = A[3+bs*1];

		C[1+bs*2] = A[2+bs*2];
		C[2+bs*2] = A[3+bs*2];

		C[2+bs*3] = A[3+bs*3];

		A += bs*sda;
		k = 4;
	
		// main loop
		for( ; k<kmax-3; k+=4)
			{
			C[3+bs*0] = A[0+bs*0];

			C[3+bs*1] = A[0+bs*1];

			C[3+bs*2] = A[0+bs*2];

			C[3+bs*3] = A[0+bs*3];

			C += bs*sdc;

			C[0+bs*0] = A[1+bs*0];
			C[1+bs*0] = A[2+bs*0];
			C[2+bs*0] = A[3+bs*0];

			C[0+bs*1] = A[1+bs*1];
			C[1+bs*1] = A[2+bs*1];
			C[2+bs*1] = A[3+bs*1];

			C[0+bs*2] = A[1+bs*2];
			C[1+bs*2] = A[2+bs*2];
			C[2+bs*2] = A[3+bs*2];

			C[0+bs*3] = A[1+bs*3];
			C[1+bs*3] = A[2+bs*3];
			C[2+bs*3] = A[3+bs*3];

			A += bs*sda;
			}

		if(k>=kmax)
			{
			return;
			}

		C[3+bs*0] = A[0+bs*0];

		C[3+bs*1] = A[0+bs*1];

		C[3+bs*2] = A[0+bs*2];

		C[3+bs*3] = A[0+bs*3];

		k++;

		if(k==kmax)
			{
			return;
			}

		C += bs*sdc;

		C[0+bs*0] = A[1+bs*0];

		C[0+bs*1] = A[1+bs*1];

		C[0+bs*2] = A[1+bs*2];

		C[0+bs*3] = A[1+bs*3];

		k++;

		if(k==kmax)
			{
			return;
			}

		C[1+bs*0] = A[2+bs*0];

		C[1+bs*1] = A[2+bs*1];

		C[1+bs*2] = A[2+bs*2];

		C[1+bs*3] = A[2+bs*3];

		return;

		}
	else if(kna==2)
		{

		// two rows in the first C panel
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];

		C[1+bs*1] = A[1+bs*1];

		C += 2 + bs*(sdc-1);

		C[0+bs*0] = A[2+bs*0];
		C[1+bs*0] = A[3+bs*0];

		C[0+bs*1] = A[2+bs*1];
		C[1+bs*1] = A[3+bs*1];

		C[0+bs*2] = A[2+bs*2];
		C[1+bs*2] = A[3+bs*2];

		C[1+bs*3] = A[3+bs*3];

		A += bs*sda;
		k = 4;
	
		// main loop
		for( ; k<kmax-3; k+=4)
			{
			C[2+bs*0] = A[0+bs*0];
			C[3+bs*0] = A[1+bs*0];

			C[2+bs*1] = A[0+bs*1];
			C[3+bs*1] = A[1+bs*1];

			C[2+bs*2] = A[0+bs*2];
			C[3+bs*2] = A[1+bs*2];

			C[2+bs*3] = A[0+bs*3];
			C[3+bs*3] = A[1+bs*3];

			C += bs*sdc;

			C[0+bs*0] = A[2+bs*0];
			C[1+bs*0] = A[3+bs*0];

			C[0+bs*1] = A[2+bs*1];
			C[1+bs*1] = A[3+bs*1];

			C[0+bs*2] = A[2+bs*2];
			C[1+bs*2] = A[3+bs*2];

			C[0+bs*3] = A[2+bs*3];
			C[1+bs*3] = A[3+bs*3];

			A += bs*sda;
			}

		if(k>=kmax)
			{
			return;
			}

		C[2+bs*0] = A[0+bs*0];

		C[2+bs*1] = A[0+bs*1];

		C[2+bs*2] = A[0+bs*2];

		C[2+bs*3] = A[0+bs*3];

		k++;

		if(k==kmax)
			{
			return;
			}

		C[3+bs*0] = A[1+bs*0];

		C[3+bs*1] = A[1+bs*1];

		C[3+bs*2] = A[1+bs*2];

		C[3+bs*3] = A[1+bs*3];

		k++;

		if(k==kmax)
			{
			return;
			}

		C += bs*sdc;

		C[0+bs*0] = A[3+bs*0];

		C[0+bs*1] = A[3+bs*1];

		C[0+bs*2] = A[3+bs*2];

		C[0+bs*3] = A[3+bs*3];

		return;

		}
	else  //if(kna==3)
		{

		// three rows in the first C panel
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];
		C[2+bs*0] = A[2+bs*0];

		C[1+bs*1] = A[1+bs*1];
		C[2+bs*1] = A[2+bs*1];

		C[2+bs*2] = A[2+bs*2];

		C += 3 + bs*(sdc-1);

		C[0+bs*0] = A[3+bs*0];

		C[0+bs*1] = A[3+bs*1];

		C[0+bs*2] = A[3+bs*2];

		C[0+bs*3] = A[3+bs*3];

		A += bs*sda;
		k = 4;

		// main loop
		for( ; k<kmax-3; k+=4)
			{
			C[1+bs*0] = A[0+bs*0];
			C[2+bs*0] = A[1+bs*0];
			C[3+bs*0] = A[2+bs*0];

			C[1+bs*1] = A[0+bs*1];
			C[2+bs*1] = A[1+bs*1];
			C[3+bs*1] = A[2+bs*1];

			C[1+bs*2] = A[0+bs*2];
			C[2+bs*2] = A[1+bs*2];
			C[3+bs*2] = A[2+bs*2];

			C[1+bs*3] = A[0+bs*3];
			C[2+bs*3] = A[1+bs*3];
			C[3+bs*3] = A[2+bs*3];

			C += bs*sdc;

			C[0+bs*0] = A[3+bs*0];

			C[0+bs*1] = A[3+bs*1];

			C[0+bs*2] = A[3+bs*2];

			C[0+bs*3] = A[3+bs*3];

			A += bs*sda;
			}

		if(k>=kmax)
			{
			return;
			}

		C[1+bs*0] = A[0+bs*0];

		C[1+bs*1] = A[0+bs*1];

		C[1+bs*2] = A[0+bs*2];

		C[1+bs*3] = A[0+bs*3];

		k++;


		if(k==kmax)
			{
			return;
			}

		C[2+bs*0] = A[1+bs*0];

		C[2+bs*1] = A[1+bs*1];

		C[2+bs*2] = A[1+bs*2];

		C[2+bs*3] = A[1+bs*3];

		k++;


		if(k==kmax)
			{
			return;
			}

		C[3+bs*0] = A[2+bs*0];

		C[3+bs*1] = A[2+bs*1];

		C[3+bs*2] = A[2+bs*2];

		C[3+bs*3] = A[2+bs*3];

		return;

		}

	}



// mis-align a triangolar matrix; it moves across panels; read aligned, write mis-aligned
void corner_dtrma_3_lib4(int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;

	if(kna==0 || kna==3)
		{
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];
		C[2+bs*0] = A[2+bs*0];

		C[1+bs*1] = A[1+bs*1];
		C[2+bs*1] = A[2+bs*1];

		C[2+bs*2] = A[2+bs*2];

		return;
		}
	else if(kna==1)
		{
		C[0+bs*0] = A[0+bs*0];

		C += 1 + bs*(sdc-1);

		C[0+bs*0] = A[1+bs*0];
		C[1+bs*0] = A[2+bs*0];

		C[0+bs*1] = A[1+bs*1];
		C[1+bs*1] = A[2+bs*1];

		C[1+bs*2] = A[2+bs*2];

		return;
		}
	else //if(kna==2)
		{
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];

		C[1+bs*1] = A[1+bs*1];

		C += 2 + bs*(sdc-1);

		C[0+bs*0] = A[2+bs*0];

		C[0+bs*1] = A[2+bs*1];

		C[0+bs*2] = A[2+bs*2];

		return;
		}

	}




// mis-align a triangolar matrix; it moves across panels; read aligned, write mis-aligned
void corner_dtrma_2_lib4(int kna, double *A, double *C, int sdc)
	{

	const int bs = 4;

	if(kna==0 || kna==2 || kna==3)
		{
		C[0+bs*0] = A[0+bs*0];
		C[1+bs*0] = A[1+bs*0];

		C[1+bs*1] = A[1+bs*1];

		return;
		}
	else //if(kna==1)
		{
		C[0+bs*0] = A[0+bs*0];

		C += 1 + bs*(sdc-1);

		C[0+bs*0] = A[1+bs*0];

		C[0+bs*1] = A[1+bs*1];

		return;
		}
	
	}

