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

void d_zeros(double **pA, int row, int col);
void d_zeros_align(double **pA, int row, int col);
void d_eye(double **pA, int row);
void d_copy_mat(int row, int col, double *A, int lda, double *B, int ldb);
void d_copy_pmat(int row, int col, int bs, double *A, int sda, double *B, int sdb);
void d_copy_pmat_l(int row, int bs, double *A, int sda, double *B, int sdb);
//void d_transpose_pmat_lo(int row, int offset, double *A, int sda, double *B, int sdb);
void d_align_pmat(int row, int col, int offset, int bs, double *A, int sda, double *B, int sdb);
void d_cvt_mat2pmat(int row, int col, int offset, int bs, double *A, int lda, double *pA, int sda);
void d_cvt_tran_mat2pmat(int row, int col, int offset, int bs, double *A, int lda, double *pA, int sda);
void d_cvt_pmat2mat(int row, int col, int offset, int bs, double *pA, int sda, double *A, int lda);
void d_cvt_tran_pmat2mat(int row, int col, int offset, int bs, double *pA, int sda, double *A, int lda);
void d_print_mat(int row, int col, double *A, int lda);
void d_print_pmat(int row, int col, int bs, double *A, int sda);

