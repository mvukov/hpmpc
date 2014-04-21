/**************************************************************************************************
*                                                                                                 *
* This file is part of HPMPC.                                                                     *
*                                                                                                 *
* HPMPC -- Library for High-Performance implementation of solvers for MPC.                        *
* Copyright (C) 2014 by Technical Univeristy of Denmark. All rights reserved.                     *
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

#include <stdio.h>

#include "../problem_size.h"
#include "../include/block_size.h"

#define NZ NX+NU+1
#define PNZ D_MR*((NZ+D_MR-NU%D_MR+D_MR-1)/D_MR);



/* computes the lower triangular Cholesky factor of pC, */
/* and copies its transposed in pL                      */
void dpotrf_p_dcopy_p_t_code_generator(FILE *f, int n, int nna)
	{

	int i, j;
	
	const int bs = 2;
	
	const int sdc = PNZ;
	const int sdl = PNZ;
	
	j = 0;
	if(j<nna-1)
		{
fprintf(f, "	kernel_dpotrf_dtrsv_2x2_lib2(%d, &pC[%d], %d, info);\n", n-j-2, j*bs+j*sdc, sdc);
fprintf(f, "	if(*info!=0) return;\n");
	            	j += 2;     
	            	for(; j<nna-1; j+=2)
	            		{     
	            		i = j;     
	            		for(; i<n; i+=2)     
	            			{     
fprintf(f, "	kernel_dgemm_pp_nt_2x2_lib2(%d, &pC[%d], &pC[%d], &pC[%d], %d, -1);\n", j, i*sdc, j*sdc, j*bs+i*sdc, bs);
	            			}     
fprintf(f, "	kernel_dpotrf_dtrsv_2x2_lib2(%d, &pC[%d], %d, info);\n", n-j-2, j*bs+j*sdc, sdc);
fprintf(f, "	if(*info!=0) return;\n");
	            		}     
		}
	int j0 = j;
	if(j==0) // assume that n>0
		{
fprintf(f, "	kernel_dpotrf_dtrsv_dcopy_2x2_lib2(%d, &pC[%d], %d, %d, &pL[%d], %d, info);\n", n-j-2, j*bs+j*sdc, sdc, (bs-nna%bs)%bs, (j-j0)*bs+((j-j0)/bs)*bs*sdc, sdl);
fprintf(f, "	if(*info!=0) return;\n");
		j += 2;
		}
	for(; j<n-1; j+=2)
		{
		i = j;
		for(; i<n; i+=2)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x2_lib2(%d, &pC[%d], &pC[%d], &pC[%d], %d, -1);\n", j, i*sdc, j*sdc, j*bs+i*sdc, bs);
			}
fprintf(f, "	kernel_dpotrf_dtrsv_dcopy_2x2_lib2(%d, &pC[%d], %d, %d, &pL[%d], %d, info);\n", n-j-2, j*bs+j*sdc, sdc, (bs-nna%bs)%bs, (j-j0)*bs+((j-j0)/bs)*bs*sdc, sdl);
fprintf(f, "	if(*info!=0) return;\n");
		}
	if(n-j==1)
		{
		i = j;
fprintf(f, "	kernel_dgemm_pp_nt_2x1_lib2(%d, &pC[%d], &pC[%d], &pC[%d], %d, -1);\n", j, i*sdc, j*sdc, j*bs+i*sdc, bs);
fprintf(f, "	corner_dpotrf_dtrsv_dcopy_1x1_lib2(&pC[%d], %d, %d, &pL[%d], %d, info);\n", j*bs+j*sdc, sdc, (bs-nna%bs)%bs, (j-j0)*bs+((j-j0)/bs)*bs*sdc, sdl);
fprintf(f, "	if(*info!=0) return;\n");
		}

	}



/* computes an mxn band of the lower triangular Cholesky factor of pC, supposed to be aligned */
void dpotrf_p_code_generator(FILE *f, int m, int n)
	{

	int i, j;
	
	const int bs = 2;
	
	const int sdc = PNZ;

	j = 0;
	for(; j<n-1; j+=2)
		{
		i = j;
		for(; i<m; i+=2)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x2_lib2(%d, &pC[%d], &pC[%d], &pC[%d], %d, -1);\n", j, i*sdc, j*sdc, j*bs+i*sdc, bs);
			}
fprintf(f, "	kernel_dpotrf_dtrsv_2x2_lib2(%d, &pC[%d], %d, info);\n", m-j-2, j*bs+j*sdc, sdc);
fprintf(f, "	if(*info!=0) return;\n");
		}
	if(n-j==1)
		{
		i = j;
		for(; i<m; i+=2)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x1_lib2(%d, &pC[%d], &pC[%d], &pC[%d], %d, -1);\n", j, i*sdc, j*sdc, j*bs+i*sdc, bs);
			}
fprintf(f, "	kernel_dpotrf_dtrsv_1x1_lib2(%d, &pC[%d], %d, info);\n", m-j-1, j*bs+j*sdc, sdc);
fprintf(f, "	if(*info!=0) return;\n");
		}

	}



/* preforms                                          */
/* C  = A * B'                                       */
/* where A, B and C are packed with block size 2,    */
/* and B is upper triangular                         */
void dtrmm_ppp_code_generator(FILE *f, int m, int n, int offset)
	{
	
	int i, j;
	
	const int bs = 2;
	
	const int sda = PNZ;
	const int sdb = PNZ;
	const int sdc = PNZ;

	if(offset%bs!=0)
fprintf(f, "	pB = pB+%d;\n", bs*sdb+bs*bs);
	
	i = 0;
	for(; i<m; i+=2)
		{
		j = 0;
		for(; j<n-1; j+=2)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x2_lib2(%d, &pA[%d], &pB[%d], &pC[%d], %d, 0);\n", n-j, j*bs+i*sda, j*bs+j*sdb, j*bs+i*sdc, bs);
			}
		if(n-j==1)
			{
fprintf(f, "	corner_dtrmm_pp_nt_2x1_lib2(&pA[%d], &pB[%d], &pC[%d], %d);\n", j*bs+i*sda, j*bs+j*sdb, j*bs+i*sdc, bs);
			}
		}

	// add to the last row
	for(j=0; j<n; j++)
		{
fprintf(f, "	pC[%d] += pB[%d];\n", (m-1)%bs+j*bs+((m-1)/bs)*bs*sdc, j%bs+n*bs+(j/bs)*bs*sdb);
		
		}

/*	fprintf(f, "	\n");*/

	}



/* preforms                                          */
/* C  = A * A'                                       */
/* where A, C are packed with block size 2           */
void dsyrk_ppp_code_generator(FILE *f, int m, int n, int k)
	{
	
	int i, j, j_end;
	
	const int bs = 2;
	
	const int sda = PNZ;
/*	const int sdb = PNZ;*/
	const int sdc = PNZ;
	
	i = 0;
	for(; i<m; i+=2)
		{
		j = 0;
		j_end = i+2;
		if(n-1<j_end)
			j_end = n-1;
		for(; j<j_end; j+=2)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x2_lib2(%d, &pA[%d], &pA[%d], &pC[%d], %d, 1);\n", k, i*sda, j*sda, j*bs+i*sdc, bs);
			}
		if(n-j==1)
			{
fprintf(f, "	kernel_dgemm_pp_nt_2x1_lib2(%d, &pA[%d], &pA[%d], &pC[%d], %d, 1);\n", k, i*sda, j*sda, j*bs+i*sdc, bs);
			}
		}

/*	fprintf(f, "	\n");*/

	}



void dgemv_p_t_code_generator(FILE *f, int n, int m, int offset, int alg)
	{
	
	const int bs = 2;
	
	const int sda = PNZ;

	int nna = (bs-offset%bs)%bs;
	
	int j;
	
	j=0;
	for(; j<m-1; j+=2)
		{
fprintf(f, "	kernel_dgemv_t_2_lib2(%d, %d, pA+%d, %d, x, y+%d, %d);\n", n, nna, j*bs, sda, j, alg);
		}
	for(; j<m; j++)
		{
fprintf(f, "	kernel_dgemv_t_1_lib2(%d, %d, pA+%d, %d, x, y+%d, %d);\n", n, nna, j*bs, sda, j, alg);
		}

/*	fprintf(f, "	\n");*/
	}



void dtrsv_p_t_code_generator(FILE *f, int n)
	{
	
	const int bs = 2;
	
	const int sda = PNZ;

	int i, j;
	
	int rn = n%bs;
	int qn = n/bs;
	int ri, qi;
	
/*	fprintf(f, "	double *ptrA, *ptrx;\n");*/
	
	// clean up stuff at the end
	j = 0;
fprintf(f, "	ptrA = pA + %d;\n", qn*bs*(sda+bs));
fprintf(f, "	ptrx = x + %d;\n", qn*bs);

	if(rn==1)
		{
		i = rn-1-j;
fprintf(f, "	kernel_dgemv_t_1_lib2(%d, %d, &ptrA[%d], %d, &ptrx[%d], &ptrx[%d], -1);\n", j, j, i+1+bs*(i+0), sda, i+1, i);
fprintf(f, "	ptrx[%d] = (ptrx[%d]) / ptrA[%d];\n", i+0, i+0, i+0+bs*(i+0));
		j++;
		}

	// blocks of 2
	for(; j<qn; j++)
		{
		
		// first 2 rows
fprintf(f, "	ptrA = pA + %d;\n", (qn-j-1)*bs*(sda+bs));
fprintf(f, "	ptrx = x  + %d;\n", (qn-j-1)*bs);
	
fprintf(f, "	kernel_dgemv_t_2_lib2(%d, 0, ptrA+%d, sda, ptrx+2, ptrx, -1);\n", rn+j*bs, bs*sda);
fprintf(f, "	ptrx[1] = (ptrx[1]) / ptrA[%d];\n", 1+bs*1);
fprintf(f, "	ptrx[0] = (ptrx[0] - ptrA[%d]*ptrx[1]) / ptrA[%d];\n", 1+bs*0, 0+bs*0);

		}

/*	fprintf(f, "	\n");*/

	}