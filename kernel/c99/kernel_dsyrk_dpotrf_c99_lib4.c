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

#include <math.h>

#include "../../include/block_size.h"



void kernel_dsyrk_dpotrf_nt_4x4_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1, b_2, b_3,
		c_00=0, 
		c_10=0, c_11=0, 
		c_20=0, c_21=0, c_22=0, 
		c_30=0, c_31=0, c_32=0, c_33=0;
		
	for(k=0; k<kadd-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_33 += a_3 * b_3;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_33 += a_3 * b_3;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		b_2 = B[2+bs*2];
		b_3 = B[3+bs*2];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_33 += a_3 * b_3;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		b_2 = B[2+bs*3];
		b_3 = B[3+bs*3];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_33 += a_3 * b_3;
		
		
		A += 16;
		B += 16;

		}
	for(; k<kadd; k++)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;

		c_22 += a_2 * b_2;
		c_32 += a_3 * b_2;

		c_33 += a_3 * b_3;


		A += 4;
		B += 4;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		b_2 = B[2+bs*0];
		b_3 = B[3+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		b_2 = B[2+bs*1];
		b_3 = B[3+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		b_2 = B[2+bs*2];
		b_3 = B[3+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_33 -= a_3 * b_3;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		b_2 = B[2+bs*3];
		b_3 = B[3+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;

		c_22 -= a_2 * b_2;
		c_32 -= a_3 * b_2;

		c_33 -= a_3 * b_3;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];

		c_22 += C[2+bs*2];
		c_32 += C[3+bs*2];

		c_33 += C[3+bs*3];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		c_20 *= c_00;
		c_30 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		c_20 = 0.0;
		c_30 = 0.0;
		}
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		c_21 -= c_20*c_10;
		c_31 -= c_30*c_10;
		c_21 *= c_11;
		c_31 *= c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		c_21 = 0.0;
		c_31 = 0.0;
		}
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;

	// third column
	c_22 -= c_20*c_20;
	c_22 -= c_21*c_21;
	if(c_22 > 1e-15)
		{
		c_22 = sqrt(c_22);
		D[2+bs*2] = c_22;
		c_22 = 1.0/c_22;
		c_32 -= c_30*c_20;
		c_32 -= c_31*c_21;
		c_32 *= c_22;
		}
	else
		{
		c_22 = 0.0;
		D[2+bs*2] = c_22;
		c_32 = 0.0;
		}
	D[3+bs*2] = c_32;

	// fourth column
	c_33 -= c_30*c_30;
	c_33 -= c_31*c_31;
	c_33 -= c_32*c_32;
	if(c_33 > 1e-15)
		{
		c_33 = sqrt(c_33);
		D[3+bs*3] = c_33;
		c_33 = 1.0/c_33;
		}
	else
		{
		c_33 = 0.0;
		D[3+bs*3] = c_33;
		}
	
	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[3] = c_20;
	fact[6] = c_30;
	fact[2] = c_11;
	fact[4] = c_21;
	fact[7] = c_31;
	fact[5] = c_22;
	fact[8] = c_32;
	fact[9] = c_33;

	}



void kernel_dsyrk_dpotrf_nt_4x2_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		b_0, b_1,
		c_00=0, 
		c_10=0, c_11=0, 
		c_20=0, c_21=0,  
		c_30=0, c_31=0;
		
	for(k=0; k<kadd-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;
		
		
		A += 16;
		B += 16;

		}
	for(; k<kadd; k++)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;
		c_20 += a_2 * b_0;
		c_30 += a_3 * b_0;

		c_11 += a_1 * b_1;
		c_21 += a_2 * b_1;
		c_31 += a_3 * b_1;


		A += 4;
		B += 4;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;
		c_20 -= a_2 * b_0;
		c_30 -= a_3 * b_0;

		c_11 -= a_1 * b_1;
		c_21 -= a_2 * b_1;
		c_31 -= a_3 * b_1;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		c_20 *= c_00;
		c_30 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		c_20 = 0.0;
		c_30 = 0.0;
		}
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		c_21 -= c_20*c_10;
		c_31 -= c_30*c_10;
		c_21 *= c_11;
		c_31 *= c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		c_21 = 0.0;
		c_31 = 0.0;
		}
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;

	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[3] = c_20;
	fact[6] = c_30;
	fact[2] = c_11;
	fact[4] = c_21;
	fact[7] = c_31;

	}



void kernel_dsyrk_dpotrf_nt_2x2_lib4(int kadd, int ksub, double *A, double *B, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1,
		b_0, b_1,
		c_00=0, 
		c_10=0, c_11=0;
		
	for(k=0; k<kadd-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_11 += a_1 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_11 += a_1 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_11 += a_1 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_11 += a_1 * b_1;
		
		
		A += 16;
		B += 16;

		}
	for(; k<kadd; k++)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 += a_0 * b_0;
		c_10 += a_1 * b_0;

		c_11 += a_1 * b_1;


		A += 4;
		B += 4;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			B += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		b_0 = B[0+bs*0];
		b_1 = B[1+bs*0];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		b_0 = B[0+bs*1];
		b_1 = B[1+bs*1];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		
		b_0 = B[0+bs*2];
		b_1 = B[1+bs*2];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_11 -= a_1 * b_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		
		b_0 = B[0+bs*3];
		b_1 = B[1+bs*3];
		
		c_00 -= a_0 * b_0;
		c_10 -= a_1 * b_0;

		c_11 -= a_1 * b_1;
		
		
		A += 16;
		B += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_11 += C[1+bs*1];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		}
	D[1+bs*0] = c_10;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		}

	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[2] = c_11;

	}




// A is upper triangular and it coincides with B
void kernel_dtsyrk_dpotrf_nt_4x4_lib4(int kadd, int ksub, double *A, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		c_00=0, 
		c_10=0, c_11=0, 
		c_20=0, c_21=0, c_22=0, 
		c_30=0, c_31=0, c_32=0, c_33=0;

	// initialize loop counter
	k = 0;

	if(kadd>=4)
		{

		// initial triangle

		// k = 0
		a_0 = A[0+bs*0];
		
		c_00 += a_0 * a_0;


		// k = 1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;

		c_11 += a_1 * a_1;


		// k = 2
		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;
		c_20 += a_2 * a_0;

		c_11 += a_1 * a_1;
		c_21 += a_2 * a_1;

		c_22 += a_2 * a_2;


		// k = 3
		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
			
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;
		c_20 += a_2 * a_0;
		c_30 += a_3 * a_0;

		c_11 += a_1 * a_1;
		c_21 += a_2 * a_1;
		c_31 += a_3 * a_1;

		c_22 += a_2 * a_2;
		c_32 += a_3 * a_2;

		c_33 += a_3 * a_3;

		A += 16;
		k = 4;

				
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;

			c_22 += a_2 * a_2;
			c_32 += a_3 * a_2;

			c_33 += a_3 * a_3;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			a_2 = A[2+bs*1];
			a_3 = A[3+bs*1];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;

			c_22 += a_2 * a_2;
			c_32 += a_3 * a_2;

			c_33 += a_3 * a_3;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			a_2 = A[2+bs*2];
			a_3 = A[3+bs*2];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;

			c_22 += a_2 * a_2;
			c_32 += a_3 * a_2;

			c_33 += a_3 * a_3;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			a_2 = A[2+bs*3];
			a_3 = A[3+bs*3];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;

			c_22 += a_2 * a_2;
			c_32 += a_3 * a_2;

			c_33 += a_3 * a_3;
			
			
			A += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;

			c_22 += a_2 * a_2;
			c_32 += a_3 * a_2;

			c_33 += a_3 * a_3;


			A += 4;

			}

		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
		
		c_00 += a_0 * a_0;

		A += 4;
		k += 1;

		if(kadd>1)
			{

			// k = 1
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;

			A += 4;
			k += 1;

			if(kadd>2)
				{

				// k = 2
				a_0 = A[0+bs*0];
				a_1 = A[1+bs*0];
				a_2 = A[2+bs*0];
				
				c_00 += a_0 * a_0;
				c_10 += a_1 * a_0;
				c_20 += a_2 * a_0;

				c_11 += a_1 * a_1;
				c_21 += a_2 * a_1;

				c_22 += a_2 * a_2;

				A += 4;
				k += 1;

				}

			}

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;

		c_22 -= a_2 * a_2;
		c_32 -= a_3 * a_2;

		c_33 -= a_3 * a_3;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;

		c_22 -= a_2 * a_2;
		c_32 -= a_3 * a_2;

		c_33 -= a_3 * a_3;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;

		c_22 -= a_2 * a_2;
		c_32 -= a_3 * a_2;

		c_33 -= a_3 * a_3;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;

		c_22 -= a_2 * a_2;
		c_32 -= a_3 * a_2;

		c_33 -= a_3 * a_3;
		
		
		A += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];

		c_22 += C[2+bs*2];
		c_32 += C[3+bs*2];

		c_33 += C[3+bs*3];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		c_20 *= c_00;
		c_30 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		c_20 = 0.0;
		c_30 = 0.0;
		}
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		c_21 -= c_20*c_10;
		c_31 -= c_30*c_10;
		c_21 *= c_11;
		c_31 *= c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		c_21 = 0.0;
		c_31 = 0.0;
		}
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;

	// third column
	c_22 -= c_20*c_20;
	c_22 -= c_21*c_21;
	if(c_22 > 1e-15)
		{
		c_22 = sqrt(c_22);
		D[2+bs*2] = c_22;
		c_22 = 1.0/c_22;
		c_32 -= c_30*c_20;
		c_32 -= c_31*c_21;
		c_32 *= c_22;
		}
	else
		{
		c_22 = 0.0;
		D[2+bs*2] = c_22;
		c_32 = 0.0;
		}
	D[3+bs*2] = c_32;

	// fourth column
	c_33 -= c_30*c_30;
	c_33 -= c_31*c_31;
	c_33 -= c_32*c_32;
	if(c_33 > 1e-15)
		{
		c_33 = sqrt(c_33);
		D[3+bs*3] = c_33;
		c_33 = 1.0/c_33;
		}
	else
		{
		c_33 = 0.0;
		D[3+bs*3] = c_33;
		}
	
	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[3] = c_20;
	fact[6] = c_30;
	fact[2] = c_11;
	fact[4] = c_21;
	fact[7] = c_31;
	fact[5] = c_22;
	fact[8] = c_32;
	fact[9] = c_33;

	}



// A is upper triangular and it coincides with B
void kernel_dtsyrk_dpotrf_nt_4x2_lib4(int kadd, int ksub, double *A, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		c_00=0, 
		c_10=0, c_11=0, 
		c_20=0, c_21=0,
		c_30=0, c_31=0;

	// initialize loop counter
	k = 0;

	if(kadd>=4)
		{

		// initial triangle

		// k = 0
		a_0 = A[0+bs*0];
			
		c_00 += a_0 * a_0;


		// k = 1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;

		c_11 += a_1 * a_1;


		// k = 2
		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
			
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;
		c_20 += a_2 * a_0;

		c_11 += a_1 * a_1;
		c_21 += a_2 * a_1;


		// k = 3
		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
			
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;
		c_20 += a_2 * a_0;
		c_30 += a_3 * a_0;

		c_11 += a_1 * a_1;
		c_21 += a_2 * a_1;
		c_31 += a_3 * a_1;

		A += 16;
		k = 4;
			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			a_2 = A[2+bs*1];
			a_3 = A[3+bs*1];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			a_2 = A[2+bs*2];
			a_3 = A[3+bs*2];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			a_2 = A[2+bs*3];
			a_3 = A[3+bs*3];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;
			
			
			A += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			a_2 = A[2+bs*0];
			a_3 = A[3+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;
			c_20 += a_2 * a_0;
			c_30 += a_3 * a_0;

			c_11 += a_1 * a_1;
			c_21 += a_2 * a_1;
			c_31 += a_3 * a_1;


			A += 4;

			}

		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
		
		c_00 += a_0 * a_0;

		A += 4;
		k += 1;

		if(kadd>1)
			{

			// k = 1
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;

			A += 4;
			k += 1;

			if(kadd>2)
				{

				// k = 2
				a_0 = A[0+bs*0];
				a_1 = A[1+bs*0];
				a_2 = A[2+bs*0];
				
				c_00 += a_0 * a_0;
				c_10 += a_1 * a_0;
				c_20 += a_2 * a_0;

				c_11 += a_1 * a_1;
				c_21 += a_2 * a_1;

				A += 4;
				k += 1;

				}

			}

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		a_2 = A[2+bs*0];
		a_3 = A[3+bs*0];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		a_2 = A[2+bs*1];
		a_3 = A[3+bs*1];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		a_2 = A[2+bs*2];
		a_3 = A[3+bs*2];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		a_2 = A[2+bs*3];
		a_3 = A[3+bs*3];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;
		c_20 -= a_2 * a_0;
		c_30 -= a_3 * a_0;

		c_11 -= a_1 * a_1;
		c_21 -= a_2 * a_1;
		c_31 -= a_3 * a_1;
		
		
		A += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];
		c_20 += C[2+bs*0];
		c_30 += C[3+bs*0];

		c_11 += C[1+bs*1];
		c_21 += C[2+bs*1];
		c_31 += C[3+bs*1];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		c_20 *= c_00;
		c_30 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		c_20 = 0.0;
		c_30 = 0.0;
		}
	D[1+bs*0] = c_10;
	D[2+bs*0] = c_20;
	D[3+bs*0] = c_30;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		c_21 -= c_20*c_10;
		c_31 -= c_30*c_10;
		c_21 *= c_11;
		c_31 *= c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		c_21 = 0.0;
		c_31 = 0.0;
		}
	D[2+bs*1] = c_21;
	D[3+bs*1] = c_31;
	
	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[3] = c_20;
	fact[6] = c_30;
	fact[2] = c_11;
	fact[4] = c_21;
	fact[7] = c_31;

	}



// A is upper triangular and it coincides with B
void kernel_dtsyrk_dpotrf_nt_2x2_lib4(int kadd, int ksub, double *A, double *C, double *D, double *fact, int alg)
	{

	const int bs = 4;
	const int d_ncl = D_NCL;

	int k;

	double
		a_0, a_1, a_2, a_3,
		c_00=0, 
		c_10=0, c_11=0; 

	// initialize loop counter
	k = 0;

	if(kadd>=2)
		{

		// initial triangle

		// k = 0
		a_0 = A[0+bs*0];
			
		c_00 += a_0 * a_0;


		// k = 1
		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
			
		c_00 += a_0 * a_0;
		c_10 += a_1 * a_0;

		c_11 += a_1 * a_1;


		A += 8;
		k = 2;
			
		for(; k<kadd-3; k+=4)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;


			a_0 = A[0+bs*1];
			a_1 = A[1+bs*1];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;


			a_0 = A[0+bs*2];
			a_1 = A[1+bs*2];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;


			a_0 = A[0+bs*3];
			a_1 = A[1+bs*3];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;
			
			
			A += 16;

			}
		for(; k<kadd; k++)
			{
			
			a_0 = A[0+bs*0];
			a_1 = A[1+bs*0];
			
			c_00 += a_0 * a_0;
			c_10 += a_1 * a_0;

			c_11 += a_1 * a_1;


			A += 4;

			}

		}
	else if(kadd>0)
		{

		// k = 0
		a_0 = A[0+bs*0];
		
		c_00 += a_0 * a_0;

		A += 4;
		k += 1;

		}

	if(ksub>0)
		{
		if(kadd>0)
			{
			A += bs*((d_ncl-kadd%d_ncl)%d_ncl);
			}
		}

	for(k=0; k<ksub-3; k+=4)
		{
		
		a_0 = A[0+bs*0];
		a_1 = A[1+bs*0];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;

		c_11 -= a_1 * a_1;


		a_0 = A[0+bs*1];
		a_1 = A[1+bs*1];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;

		c_11 -= a_1 * a_1;


		a_0 = A[0+bs*2];
		a_1 = A[1+bs*2];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;

		c_11 -= a_1 * a_1;


		a_0 = A[0+bs*3];
		a_1 = A[1+bs*3];
		
		c_00 -= a_0 * a_0;
		c_10 -= a_1 * a_0;

		c_11 -= a_1 * a_1;
		
		
		A += 16;

		}

	if(alg!=0)
		{
		c_00 += C[0+bs*0];
		c_10 += C[1+bs*0];

		c_11 += C[1+bs*1];
		}
	
	// dpotrf
	
	// first column
	if(c_00 > 1e-15)
		{
		c_00 = sqrt(c_00);
		D[0+bs*0] = c_00;
		c_00 = 1.0/c_00;
		c_10 *= c_00;
		}
	else
		{
		c_00 = 0.0;
		D[0+bs*0] = c_00;
		c_10 = 0.0;
		}
	D[1+bs*0] = c_10;
	
	// second column
	c_11 -= c_10*c_10;
	if(c_11 > 1e-15)
		{
		c_11 = sqrt(c_11);
		D[1+bs*1] = c_11;
		c_11 = 1.0/c_11;
		}
	else
		{
		c_11 = 0.0;
		D[1+bs*1] = c_11;
		}
	
	// save factorized matrix with reciprocal of diagonal
	fact[0] = c_00;
	fact[1] = c_10;
	fact[2] = c_11;

	}





