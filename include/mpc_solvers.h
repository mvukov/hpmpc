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

// MPC IP
int d_ip_box_mpc(int *kk, int k_max, double mu_tol, double alpha_min, int warm_start, double *sigma_par, double *stat, int nx, int nu, int N, int nb, double **pBAbt, double **pQ, double **db, double **ux, int compute_mult, double **pi, double **lam, double **t, double *work_memory);
int d_ip2_box_mpc(int *kk, int k_max, double mu_tol, double alpha_min, int warm_start, double *sigma_par, double *stat, int nx, int nu, int N, int nb, double **pBAbt, double **pQ, double **db, double **ux, int compute_mult, double **pi, double **lam, double **t, double *work_memory);
void d_res_ip_box_mpc(int nx, int nu, int N, int nb, double **hpBAbt, double **hpQ, double **hq, double **hux, double **hdb, double **hpi, double **hlam, double **ht, double **hrq, double **hrb, double **hrd, double *mu);
int s_ip_box_mpc(int *kk, int k_max, float mu_tol, float alpha_min, int warm_start, float *sigma_par, float *stat, int nx, int nu, int N, int nb, float **pBAbt, float **pQ, float **db, float **ux, int compute_mult, float **pi, float **lam, float **t, float *work_memory);
int s_ip2_box_mpc(int *kk, int k_max, float mu_tol, float alpha_min, int warm_start, float *sigma_par, float *stat, int nx, int nu, int N, int nb, float **pBAbt, float **pQ, float **db, float **ux, int compute_mult, float **pi, float **lam, float **t, float *work_memory);
void s_res_ip_box_mpc(int nx, int nu, int N, int nb, float **hpBAbt, float **hpQ, float **hq, float **hux, float **hdb, float **hpi, float **hlam, float **ht, float **hrq, float **hrb, float **hrd, float *mu);

// MPC ADMM
void d_admm_box_mpc(int *kk, int k_max, double tol_p, double tol_d, int warm_start, int compute_fact, double rho, double alpha, double *stat, int nx, int nu, int N, double **pBAbt, double **pQ, double **lb, double **ub, double **ux_u, double **ux_v, double **ux_w, int compute_mult, double **pi, double *work_memory);
void d_admm_soft_mpc(int *kk, int k_max, double tol_p, double tol_d, int warm_start, int compute_fact, double rho, double alpha, double *stat, int nx, int nu, int N, double **pBAbt, double **pQ, double **pS, double **lb, double **ub, double **ux_u, double **ux_v, double **ux_w, double **s_u, double **s_v, double **s_w, int compute_mult, double **pi, double *work_memory);
void s_admm_box_mpc(int *kk, int k_max, float tol_p, float tol_d, int warm_start, int compute_fact, float rho, float alpha, float *stat, int nx, int nu, int N, float **pBAbt, float **pQ, float **lb, float **ub, float **ux_u, float **ux_v, float **ux_w, int compute_mult, float **pi, float *work_memory);
void s_admm_soft_mpc(int *kk, int k_max, float tol_p, float tol_d, int warm_start, int compute_fact, float rho, float alpha, float *stat, int nx, int nu, int N, float **pBAbt, float **pQ, float **pS, float **lb, float **ub, float **ux_u, float **ux_v, float **ux_w, float **s_u, float **s_v, float **s_w, int compute_mult, float **pi, float *work_memory);

// MHE wrong
int d_ip_box_mhe_old(int *kk, int k_max, double mu_tol, double alpha_min, int warm_start, double *sigma_par, double *stat, int nx, int nu, int N, int nb, double **pBAbt, double **pQ, double **db, double **ux, int compute_mult, double **pi, double **lam, double **t, double *work_memory);
int d_ip2_box_mhe_old(int *kk, int k_max, double mu_tol, double alpha_min, int warm_start, double *sigma_par, double *stat, int nx, int nu, int N, int nb, double **pBAbt, double **pQ, double **db, double **ux, int compute_mult, double **pi, double **lam, double **t, double *work_memory);
void d_res_ip_box_mhe_old(int nx, int nu, int N, int nb, double **hpBAbt, double **hpQ, double **hq, double **hux, double **hdb, double **hpi, double **hlam, double **ht, double **hrq, double **hrb, double **hrd, double *mu);
int s_ip_box_mhe_old(int *kk, int k_max, float mu_tol, float alpha_min, int warm_start, float *sigma_par, float *stat, int nx, int nu, int N, int nb, float **pBAbt, float **pQ, float **db, float **ux, int compute_mult, float **pi, float **lam, float **t, float *work_memory);
int s_ip2_box_mhe_old(int *kk, int k_max, float mu_tol, float alpha_min, int warm_start, float *sigma_par, float *stat, int nx, int nu, int N, int nb, float **pBAbt, float **pQ, float **db, float **ux, int compute_mult, float **pi, float **lam, float **t, float *work_memory);
void s_res_ip_box_mhe_old(int nx, int nu, int N, int nb, float **hpBAbt, float **hpQ, float **hq, float **hux, float **hdb, float **hpi, float **hlam, float **ht, float **hrq, float **hrb, float **hrd, float *mu);
