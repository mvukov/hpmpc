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

#include <stdio.h>
#include <stdlib.h>

/* ACADO auto-generated header */
/*#include "acado_common.h"*/
/* HPMPC configuration */
/*#include "hpmpc_pro/target.h"*/
/*#include "hpmpc_pro/block_size.h"*/
/*#include "hpmpc_pro/aux_d.h"*/
/*#include "hpmpc_pro/aux_s.h"*/
/*#include "hpmpc_pro/mpc_solvers.h"*/

#include "../../problem_size.h"
#include "../../include/target.h"
#include "../../include/block_size.h"
#include "../../include/aux_d.h"
#include "../../include/aux_s.h"
#include "../../include/mpc_solvers.h"

// problem size (states, inputs, horizon)
/*#define NX ACADO_NX*/
/*#define NU ACADO_NU*/
/*#define NN ACADO_N*/

#define NZ (NX+NU+1)

// number of inequality constraints
#define NB (NU+NX)

// double constants
#define D_NAL (D_MR*D_NCL)
#define D_PNZ (D_MR*((NZ+D_MR-1)/D_MR))
#define D_PNX (D_MR*((NX+D_MR-1)/D_MR))
#define D_CNZ (D_NCL*((NZ+D_NCL-1)/D_NCL))
#define D_CNX (D_NCL*((NX+D_NCL-1)/D_NCL))
#define D_PNB (D_MR*((2*NB+D_MR-1)/D_MR))
#define D_PAD ((D_NCL-NX%D_NCL)%D_NCL) // packing between BAbtL & P
#define D_CNL (D_CNZ<D_CNX+D_NCL ? NX+D_PAD+D_CNX+D_NCL : NX+D_PAD+D_CNZ)
#define D_ANZ (D_NAL*((NZ+D_NAL-1)/(D_NAL)))
#define D_ANX (D_NAL*((NX+D_NAL-1)/(D_NAL)))
#define D_ANB (D_NAL*((2*NB+D_NAL-1)/(D_NAL)))

// float constants
#define S_NAL (S_MR*S_NCL)
#define S_PNZ (S_MR*((NZ+S_MR-1)/S_MR))
#define S_PNX (S_MR*((NX+S_MR-1)/S_MR))
#define S_CNZ (S_NCL*((NZ+S_NCL-1)/S_NCL))
#define S_CNX (S_NCL*((NX+S_NCL-1)/S_NCL))
#define S_PNB (S_MR*((2*NB+S_MR-1)/S_MR))
#define S_PAD ((S_NCL-NX%S_NCL)%S_NCL) // packing between BAbtL & P
#define S_CNL (S_CNZ<S_CNX+S_NCL ? NX+S_PAD+S_CNX+S_NCL : NX+S_PAD+S_CNZ)
#define S_ANZ (S_NAL*((NZ+S_NAL-1)/(S_NAL)))
#define S_ANX (S_NAL*((NX+S_NAL-1)/(S_NAL)))
#define S_ANB (S_NAL*((2*NB+S_NAL-1)/(S_NAL)))

// free initial state: 0 mpc, 1 mhe
#define FREE_X0 0

// ip method: 1 primal-dual, 2 predictor-corrector primal-dual
#define IP 2

// warm-start with user-provided solution (otherwise initialize x and u with 0 or something feasible)
#define WARM_START 0

// double/single ('d'/'s') precision
#define PREC 'd'

// number of iterations of IP method
/*#define K_MAX 20*/

// tolerance in the duality measure
/*#define MU_TOL 1e-4*/

// minimum accepted step length
#define ALPHA_MIN 1e-8

/*// threshold in the duality measure to switch from single to double precision*/
/*#define SP_THR 1e5*/

// Debug flag
#ifndef PC_DEBUG
#define PC_DEBUG 0
#endif /* PC_DEBUG */

/* version dealing with equality constratins: is lb=ub, then fix the variable (corresponding column in A or B set to zero, and updated b) */
int c_order_static_mem_ip_wrapper(	int k_max, double mu_tol,
                                    const int nx2, const int nu2, const int N2,
                                    double* A, double* B, double* b, 
                                    double* Q, double* Qf, double* S, double* R, 
                                    double* q, double* qf, double* r, 
                                    double* lb, double* ub, 
                                    double* x, double* u,
                                    int* nIt, double *stat )

	{
	
	if(nx2!=NX || nu2!=NU || N2!=NN)
		{
		printf("ERROR: library build for a different problem size: nx=%d, nu=%d, N=%d\n\n", NX, NU, NN);
		return 1;
		}

/*printf("\nstart of wrapper\n");*/

	int hpmpc_status = -1;

    char prec = PREC;

    if(prec=='d')
	    {
	    
	    const int nx = NX;
	    const int nu = NU;
	    const int N = NN;

		const int bs = D_MR; //d_get_mr();
		const int ncl = D_NCL;
		const int nal = D_MR*D_NCL;
	
		const int nz = NZ;//nx+nu+1;
		const int pnz = D_PNZ;//bs*((nz+bs-1)/bs);
		const int pnx = D_PNX;//bs*((nx+bs-1)/bs);
		const int cnz = D_CNZ;//ncl*((nx+nu+1+ncl-1)/ncl);
		const int cnx = D_CNX;//ncl*((nx+ncl-1)/ncl);
		const int anz = D_ANZ;//bs*((nz+bs-1)/bs);
		const int anx = D_ANX;//bs*((nx+bs-1)/bs);

		const int pad = D_PAD;//(ncl-nx%ncl)%ncl; // packing between BAbtL & P
		const int cnl = D_CNL;//cnz<cnx+ncl ? nx+pad+cnx+ncl : nx+pad+cnz;

		const int nb = NB; // number of box constraints
//		const int pnb = D_PNB;//bs*((2*nb+bs-1)/bs);
		const int anb = D_ANB;

/*		const int nz = nx+nu+1;*/
/*		const int pnz = bs*((nz+bs-1)/bs);*/
/*		const int pnx = bs*((nx+bs-1)/bs);*/
/*		const int cnz = ncl*((nx+nu+1+ncl-1)/ncl);*/
/*		const int cnx = ncl*((nx+ncl-1)/ncl);*/
/*		const int anz = nal*((nz+nal-1)/nal);*/
/*		const int anx = nal*((nx+nal-1)/nal);*/

/*		const int pad = (ncl-nx%ncl)%ncl; // packing between BAbtL & P*/
/*		const int cnl = cnz<cnx+ncl ? nx+pad+cnx+ncl : nx+pad+cnz;*/

/*		const int nb = nx+nu; // number of box constraints*/
/*//	const int pnb = bs*((2*nb+bs-1)/bs);*/
/*		const int anb = nal*((2*nb+nal-1)/nal);*/

        /*	double sp_thr = SP_THR; // threshold to switch between double and single precision*/
/*        int k_max = K_MAX; // maximum number of iterations in the IP method*/
/*        double mu_tol = MU_TOL; // tolerance in the duality measure*/
		double alpha_min = ALPHA_MIN; // minimum accepted step length
        static double sigma_par[] = {0.4, 0.1, 0.001}; // control primal-dual IP behaviour
/*        static double stat[5*K_MAX]; // statistics from the IP routine*/
        static double work0[8 + (NN+1)*(D_PNZ*D_CNX + D_PNZ*D_CNZ + D_PNZ*D_CNL + 5*D_ANZ + 3*D_ANX + 7*D_ANB) + 3*D_ANZ];
/*        double *work0 = (double *) malloc((8 + (N+1)*(pnz*cnx + pnz*cnz + pnz*cnl + 5*anz + 2*anx + 7*anb) + 3*anz)*sizeof(double));*/
        int warm_start = WARM_START;
        int compute_mult = 1; // compute multipliers
        
        int info = 0;

        int i, ii, jj, ll;


        /* align work space */
        size_t align = 64;
        size_t addr = (size_t) work0;
        size_t offset = addr % 64;
        double *ptr = work0 + offset / 8;

        /* array or pointers */
        double *(hpBAbt[N]);
        double *(hpQ[N + 1]);
        double *(hux[N + 1]);
        double *(hdb[N + 1]);
        double *(hpi[N + 1]);
        double *(hlam[N + 1]);
        double *(ht[N + 1]);

        for(ii=0; ii<N; ii++)
	        {
            hpBAbt[ii] = ptr;
            ptr += pnz*cnx;
	        }

        for(ii=0; ii<=N; ii++) // time variant and copied again internally in the IP !!!
	        {
            hpQ[ii] = ptr;
            ptr += pnz*cnz;
	        }

        for(ii=0; ii<=N; ii++)
	        {
            hux[ii] = ptr;
            ptr += anz;
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hdb[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }



        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hpi[ii] = ptr;
            ptr += anx; // for alignment of ptr
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hlam[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            ht[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }

        /* pack matrices 	*/

        // dynamic system
        for(ii=0; ii<N; ii++)
	        {
            d_cvt_mat2pmat(nu, nx, 0, bs, B+ii*nu*nx, nu, hpBAbt[ii], cnx);
            d_cvt_mat2pmat(nx, nx, nu, bs, A+ii*nx*nx, nx, hpBAbt[ii]+nu/bs*cnx*bs+nu%bs, cnx);
            for (jj = 0; jj<nx; jj++)
                hpBAbt[ii][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+jj*bs] = b[ii*nx+jj];
/*            d_print_pmat(nx+nu, nx, bs, hpBAbt[ii], cnx);*/
	        }
/*return 1;*/
        // cost function
        for(jj=0; jj<N; jj++)
	        {
            d_cvt_mat2pmat(nu, nu, 0, bs, R+jj*nu*nu, nu, hpQ[jj], cnz);
            d_cvt_mat2pmat(nx, nu, nu, bs, S+jj*nx*nu, nx, hpQ[jj]+nu/bs*cnz*bs+nu%bs, cnz);
            d_cvt_mat2pmat(nx, nx, nu, bs, Q+jj*nx*nx, nx, hpQ[jj]+nu/bs*cnz*bs+nu%bs+nu*bs, cnz);
            for(ii=0; ii<nu; ii++)
                hpQ[jj][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+ii*bs] = r[ii+jj*nu];
            for(ii=0; ii<nx; ii++)
                hpQ[jj][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+(nu+ii)*bs] = q[ii+nx*jj];
/*            hpQ[jj][(nx+nu)/bs*pnz*bs+(nx+nu)%bs+(nx+nu)*bs] = 1e35;*/
	        }

        for(jj=0; jj<nu; jj++)
            for(ii=0; ii<nz; ii+=bs)
                for(i=0; i<bs; i++)
                    hpQ[N][ii*cnz+i+jj*bs] = 0.0;
        for(jj=0; jj<nu; jj++)
            hpQ[N][jj/bs*cnz*bs+jj%bs+jj*bs] = 1.0;
        d_cvt_mat2pmat(nx, nx, nu, bs, Qf, nx, hpQ[N]+nu/bs*cnz*bs+nu%bs+nu*bs, cnz);
        for(jj=0; jj<nx; jj++)
            hpQ[N][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+(nu+jj)*bs] = qf[jj];
/*        hpQ[N][(nx+nu)/bs*pnz*bs+(nx+nu)%bs+(nx+nu)*bs] = 1e35;*/

		// input constraints
		for(jj=0; jj<N; jj++)
			{
			for(ii=0; ii<nu; ii++)
				{
				if(lb[ii+nu*jj]!=ub[ii+nu*jj]) // equality constraint
					{
					hdb[jj][2*ii+0] =   lb[ii+nu*jj];
					hdb[jj][2*ii+1] = - ub[ii+nu*jj];
					}
				else
					{
					for(ll=0; ll<nx; ll++)
						{
						// update linear term
						hpBAbt[jj][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+ll*bs] += hpBAbt[jj][ii/bs*cnx*bs+ii%bs+ll*bs]*lb[ii+nu*jj];
						// zero corresponding B column
						hpBAbt[jj][ii/bs*cnx*bs+ii%bs+ll*bs] = 0;
						}
					
					// inactive box constraints
					hdb[jj][2*ii+0] =   lb[ii+nu*jj] + 1e3;
					hdb[jj][2*ii+1] = - ub[ii+nu*jj] - 1e3;

/*		            d_print_pmat(nx+nu, nx, bs, hpBAbt[jj], cnx);*/
					}
				}
			}
		// state constraints 
		if(FREE_X0==0) // mpc
			{
			for(jj=0; jj<N; jj++)
				{
				for(ii=0; ii<nx; ii++)
					{
/*					if(lb[N*nu+ii+nx*jj]!=ub[N*nu+ii+nx*jj]) // inequality constraint*/
/*						{*/
						hdb[jj+1][2*nu+2*ii+0] =   lb[N*nu+ii+nx*jj];
						hdb[jj+1][2*nu+2*ii+1] = - ub[N*nu+ii+nx*jj];
/*						}*/
/*					else // equality constraint WRONG !!! unfeasible solution, the dynamic should be reformulated instead*/
/*						{*/
/*						for(ll=0; ll<nx; ll++)*/
/*							{*/
/*							// update linear term*/
/*							hpBAbt[jj][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+ll*bs] += hpBAbt[jj][(nu+ii)/bs*cnx*bs+(nu+ii)%bs+ll*bs]*lb[N*nu+ii+nx*jj];*/
/*							// zero corresponding B column*/
/*							hpBAbt[jj][(nu+ii)/bs*cnx*bs+(nu+ii)%bs+ll*bs] = 0;*/
/*							}*/
/*					*/
/*						// inactive box constraints*/
/*						hdb[jj+1][2*nu+2*ii+0] =   lb[N*nu+ii+nx*jj] + 1e3;*/
/*						hdb[jj+1][2*nu+2*ii+1] = - ub[N*nu+ii+nx*jj] - 1e3;*/

/*			            d_print_pmat(nx+nu, nx, bs, hpBAbt[jj], cnx);*/
/*						}*/
					}
				}
			}
		else // mhe
			{
			for(jj=0; jj<=N; jj++)
				{
				for(ii=0; ii<nx; ii++)
					{
/*					if(lb[N*nu+ii+nx*jj]!=ub[N*nu+ii+nx*jj]) // inequality constraint*/
/*						{*/
						hdb[jj][2*nu+2*ii+0] =   lb[N*nu+ii+nx*jj];
						hdb[jj][2*nu+2*ii+1] = - ub[N*nu+ii+nx*jj];
/*						}*/
/*					else // equality constraint*/
/*						{*/
/*						for(ll=0; ll<nx; ll++)*/
/*							{*/
/*							// update linear term*/
/*							hpBAbt[jj][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+ll*bs] += hpBAbt[jj][(nu+ii)/bs*cnx*bs+(nu+ii)%bs+ll*bs]*lb[N*nu+ii+nx*jj];*/
/*							// zero corresponding B column*/
/*							hpBAbt[jj][(nu+ii)/bs*cnx*bs+(nu+ii)%bs+ll*bs] = 0;*/
/*							}*/
/*					*/
/*						// inactive box constraints*/
/*						hdb[jj][2*nu+2*ii+0] =   lb[N*nu+ii+nx*jj] + 1e3;*/
/*						hdb[jj][2*nu+2*ii+1] = - ub[N*nu+ii+nx*jj] - 1e3;*/

	/*		            d_print_pmat(nx+nu, nx, bs, hpBAbt[jj], cnx);*/
/*						}*/
					}
				}
			}



        // initial guess
        for(jj=0; jj<N; jj++)
            for(ii=0; ii<nu; ii++)
                hux[jj][ii] = u[ii+nu*jj];

        for(jj=0; jj<=N; jj++)
            for(ii=0; ii<nx; ii++)
                hux[jj][nu+ii] = x[ii+nx*jj];



/*printf("\nstart of ip solver\n");*/

        // call the IP solver
		if(FREE_X0==0) // mpc
			{
		    if(IP==1)
		        hpmpc_status = d_ip_box_mpc(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    else
		        hpmpc_status = d_ip2_box_mpc(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    }
		else // mhe
			{
		    if(IP==1)
		        hpmpc_status = d_ip_box_mhe_old(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    else
		        hpmpc_status = d_ip2_box_mhe_old(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    }

/*printf("\nend of ip solver\n");*/


        // copy back inputs and states
        for(jj=0; jj<N; jj++)
            for(ii=0; ii<nu; ii++)
                u[ii+nu*jj] = hux[jj][ii];

        for(jj=0; jj<=N; jj++)
            for(ii=0; ii<nx; ii++)
                x[ii+nx*jj] = hux[jj][nu+ii];

		// check for input and states equality constraints
		for(jj=0; jj<N; jj++)
			{
			for(ii=0; ii<nu; ii++)
				{
				if(lb[ii+nu*jj]==ub[ii+nu*jj]) // equality constraint
					{
	                u[ii+nu*jj] = lb[ii+nu*jj];
					}
				}
			}
		// WRONG test states eq.c.
/*		if(FREE_X0==0) // mpc*/
/*			{*/
/*			for(jj=0; jj<N; jj++)*/
/*				{*/
/*				for(ii=0; ii<nx; ii++)*/
/*					{*/
/*					if(lb[N*nu+ii+nx*jj]==ub[N*nu+ii+nx*jj]) // inequality constraint*/
/*						{*/
/*						x[ii+nx*(jj+1)] = lb[N*nu+ii+nx*jj];*/
/*						}*/
/*					}*/
/*				}*/
/*			}*/
/*		else // mhe*/
/*			{*/
/*			for(jj=0; jj<=N; jj++)*/
/*				{*/
/*				for(ii=0; ii<nx; ii++)*/
/*					{*/
/*					if(lb[N*nu+ii+nx*jj]==ub[N*nu+ii+nx*jj]) // inequality constraint*/
/*						{*/
/*						x[ii+nx*jj] = lb[N*nu+ii+nx*jj];*/
/*						}*/
/*					}*/
/*				}*/
/*			}*/


#if PC_DEBUG == 1
        for (jj = 0; jj < *nIt; jj++)
            printf("k = %d\tsigma = %f\talpha = %f\tmu = %f\t\tmu = %e\n", jj,
                   stat[5 * jj], stat[5 * jj + 1], stat[5 * jj + 2],
                   stat[5 * jj + 2]);
        printf("\n");
#endif /* PC_DEBUG == 1 */

	    }
    else if(prec=='s')
	    {
	    
	    const int nx = NX;
	    const int nu = NU;
	    const int N = NN;

		const int bs = S_MR; //d_get_mr();
		const int ncl = S_NCL;
		const int nal = S_MR*S_NCL;
	
		const int nz = NZ;//nx+nu+1;
		const int pnz = S_PNZ;//bs*((nz+bs-1)/bs);
		const int pnx = S_PNX;//bs*((nx+bs-1)/bs);
		const int cnz = S_CNZ;//ncl*((nx+nu+1+ncl-1)/ncl);
		const int cnx = S_CNX;//ncl*((nx+ncl-1)/ncl);
		const int anz = S_ANZ;//bs*((nz+bs-1)/bs);
		const int anx = S_ANX;//bs*((nx+bs-1)/bs);

		const int pad = S_PAD;//(ncl-nx%ncl)%ncl; // packing between BAbtL & P
		const int cnl = S_CNL;//cnz<cnx+ncl ? nx+pad+cnx+ncl : nx+pad+cnz;

		const int nb = NB; // number of box constraints
//		const int pnb = S_PNB;//bs*((2*nb+bs-1)/bs);
		const int anb = S_ANB;

/*		const int nz = nx+nu+1;*/
/*		const int pnz = bs*((nz+bs-1)/bs);*/
/*		const int pnx = bs*((nx+bs-1)/bs);*/
/*		const int cnz = ncl*((nx+nu+1+ncl-1)/ncl);*/
/*		const int cnx = ncl*((nx+ncl-1)/ncl);*/
/*		const int anz = nal*((nz+nal-1)/nal);*/
/*		const int anx = nal*((nx+nal-1)/nal);*/

/*		const int pad = (ncl-nx%ncl)%ncl; // packing between BAbtL & P*/
/*		const int cnl = cnz<cnx+ncl ? nx+pad+cnx+ncl : nx+pad+cnz;*/

/*		const int nb = nx+nu; // number of box constraints*/
/*//		const int pnb = bs*((2*nb+bs-1)/bs);*/
/*		const int anb = nal*((2*nb+nal-1)/nal);*/

        /*	float sp_thr = SP_THR; // threshold to switch between float and single precision*/
/*        int k_max = K_MAX; // maximum number of iterations in the IP method*/
/*        float mu_tol = MU_TOL; // tolerance in the duality measure*/
		float alpha_min = ALPHA_MIN; // minimum accepted step length
        static float sigma_par[] = {0.4, 0.1, 0.01}; // control primal-dual IP behaviour
/*        static float stat[5*K_MAX]; // statistics from the IP routine*/
        static float work0[16 + (NN+1)*(S_PNZ*S_CNX + S_PNZ*S_CNZ + S_PNZ*S_CNL + 5*S_ANZ + 3*S_ANX + 7*S_ANB) + 3*S_ANZ];
/*        float *work0 = (float *) malloc((8 + (N+1)*(pnz*cnx + pnz*cnz + pnz*cnl + 5*anz + 2*anx + 7*anb) + 3*anz)*sizeof(float));*/
        int warm_start = WARM_START;
        int compute_mult = 1; // compute multipliers
        
        int info = 0;

        int i, ii, jj, ll;


        /* align work space */
        size_t align = 64;
        size_t addr = (size_t) work0;
        size_t offset = addr % 64;
        float *ptr = work0 + offset / 4;

        /* array or pointers */
        float *(hpBAbt[N]);
        float *(hpQ[N + 1]);
        float *(hux[N + 1]);
        float *(hdb[N + 1]);
        float *(hpi[N + 1]);
        float *(hlam[N + 1]);
        float *(ht[N + 1]);

        for(ii=0; ii<N; ii++)
	        {
            hpBAbt[ii] = ptr;
            ptr += pnz*cnx;
	        }

        for(ii=0; ii<=N; ii++) // time variant and copied again internally in the IP !!!
	        {
            hpQ[ii] = ptr;
            ptr += pnz*cnz;
	        }

        for(ii=0; ii<=N; ii++)
	        {
            hux[ii] = ptr;
            ptr += anz;
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hdb[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }



        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hpi[ii] = ptr;
            ptr += anx; // for alignment of ptr
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            hlam[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }

        for(ii=0; ii<=N; ii++) // time Variant box constraints
	        {
            ht[ii] = ptr;
            ptr += anb; //nb; // for alignment of ptr
	        }

        /* pack matrices 	*/

        // dynamic system
        for(ii=0; ii<N; ii++)
	        {
            cvt_d2s_mat2pmat(nu, nx, 0, bs, B+ii*nu*nx, nu, hpBAbt[ii], cnx);
            cvt_d2s_mat2pmat(nx, nx, nu, bs, A+ii*nx*nx, nx, hpBAbt[ii]+nu/bs*cnx*bs+nu%bs, cnx);
            for (jj = 0; jj<nx; jj++)
                hpBAbt[ii][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+jj*bs] = (float) b[ii*nx+jj];
	        }

        // cost function
        for(jj=0; jj<N; jj++)
	        {
            cvt_d2s_mat2pmat(nu, nu, 0, bs, R+jj*nu*nu, nu, hpQ[jj], cnz);
            cvt_d2s_mat2pmat(nx, nu, nu, bs, S+jj*nx*nu, nx, hpQ[jj]+nu/bs*cnz*bs+nu%bs, cnz);
            cvt_d2s_mat2pmat(nx, nx, nu, bs, Q+jj*nx*nx, nx, hpQ[jj]+nu/bs*cnz*bs+nu%bs+nu*bs, cnz);
            for(ii=0; ii<nu; ii++)
                hpQ[jj][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+ii*bs] = (float) r[ii+jj*nu];
            for(ii=0; ii<nx; ii++)
                hpQ[jj][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+(nu+ii)*bs] = (float) q[ii+nx*jj];
/*            hpQ[jj][(nx+nu)/bs*pnz*bs+(nx+nu)%bs+(nx+nu)*bs] = 1e35;*/
	        }

        for(jj=0; jj<nu; jj++)
            for(ii=0; ii<nz; ii+=bs)
                for(i=0; i<bs; i++)
                    hpQ[N][ii*cnz+i+jj*bs] = 0.0;
        for(jj=0; jj<nu; jj++)
            hpQ[N][jj/bs*cnz*bs+jj%bs+jj*bs] = 1.0;
        cvt_d2s_mat2pmat(nx, nx, nu, bs, Qf, nx, hpQ[N]+nu/bs*cnz*bs+nu%bs+nu*bs, cnz);
        for(jj=0; jj<nx; jj++)
            hpQ[N][(nx+nu)/bs*cnz*bs+(nx+nu)%bs+(nu+jj)*bs] = (float) qf[jj];
/*        hpQ[N][(nx+nu)/bs*pnz*bs+(nx+nu)%bs+(nx+nu)*bs] = 1e35;*/

		// input constraints
/*		for(jj=0; jj<N; jj++)*/
/*			{*/
/*			for(ii=0; ii<nu; ii++)*/
/*				{*/
/*				hdb[jj][2*ii+0] = (float)   lb[ii+nu*jj];*/
/*				hdb[jj][2*ii+1] = (float) - ub[ii+nu*jj];*/
/*				}*/
/*			}*/
		for(jj=0; jj<N; jj++)
			{
			for(ii=0; ii<nu; ii++)
				{
				if(lb[ii+nu*jj]!=ub[ii+nu*jj]) // equality constraint
					{
					hdb[jj][2*ii+0] = (float)   lb[ii+nu*jj];
					hdb[jj][2*ii+1] = (float) - ub[ii+nu*jj];
					}
				else
					{
					for(ll=0; ll<nx; ll++)
						{
						// update linear term
						hpBAbt[jj][(nx+nu)/bs*cnx*bs+(nx+nu)%bs+ll*bs] += hpBAbt[jj][ii/bs*cnx*bs+ii%bs+ll*bs]*lb[ii+nu*jj];
						// zero corresponding B column
						hpBAbt[jj][ii/bs*cnx*bs+ii%bs+ll*bs] = 0;
						}
					
					// inactive box constraints
					hdb[jj][2*ii+0] = (float)   lb[ii+nu*jj] + 1e3;
					hdb[jj][2*ii+1] = (float) - ub[ii+nu*jj] - 1e3;

/*		            d_print_pmat(nx+nu, nx, bs, hpBAbt[jj], cnx);*/
					}
				}
			}
		// state constraints
		if(FREE_X0==0) // mpc
			{
			for(jj=0; jj<N; jj++)
				{
				for(ii=0; ii<nx; ii++)
					{
					hdb[jj+1][2*nu+2*ii+0] = (float)   lb[N*nu+ii+nx*jj];
					hdb[jj+1][2*nu+2*ii+1] = (float) - ub[N*nu+ii+nx*jj];
					}
				}
			}
		else // mhe
			{
			for(jj=0; jj<=N; jj++)
				{
				for(ii=0; ii<nx; ii++)
					{
					hdb[jj][2*nu+2*ii+0] = (float)   lb[N*nu+ii+nx*jj];
					hdb[jj][2*nu+2*ii+1] = (float) - ub[N*nu+ii+nx*jj];
					}
				}
			}



        // initial guess
        for(jj=0; jj<N; jj++)
            for(ii=0; ii<nu; ii++)
                hux[jj][ii] = (float) u[ii+nu*jj];

        for(jj=0; jj<=N; jj++)
            for(ii=0; ii<nx; ii++)
                hux[jj][nu+ii] = (float) x[ii+nx*jj];



        // call the IP solver
		if(FREE_X0==0) // mpc
			{
		    if(IP==1)
		        hpmpc_status = s_ip_box_mpc(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, (float *) stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    else
		        hpmpc_status = s_ip2_box_mpc(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, (float *) stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    }
		else // mhe
			{
		    if(IP==1)
		        hpmpc_status = s_ip_box_mhe_old(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, (float *) stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    else
		        hpmpc_status = s_ip2_box_mhe_old(nIt, k_max, mu_tol, alpha_min, warm_start, sigma_par, (float *) stat, nx, nu, N, nb, hpBAbt, hpQ, hdb, hux, compute_mult, hpi, hlam, ht, ptr);
		    }



/*		 convert stat into double */
		float *ptr_stat = (float *) stat;
		for(ii=5*k_max-1; ii>=0; ii--)
			{
			stat[ii] = (double) ptr_stat[ii];
			}



        // copy back inputs and states
        for(jj=0; jj<N; jj++)
            for(ii=0; ii<nu; ii++)
                u[ii+nu*jj] = (double) hux[jj][ii];

        for(jj=0; jj<=N; jj++)
            for(ii=0; ii<nx; ii++)
                x[ii+nx*jj] = (double) hux[jj][nu+ii];

		// check for input equality constraints
		for(jj=0; jj<N; jj++)
			{
			for(ii=0; ii<nu; ii++)
				{
				if(lb[ii+nu*jj]==ub[ii+nu*jj]) // equality constraint
					{
	                u[ii+nu*jj] = lb[ii+nu*jj];
					}
				}
			}


#if PC_DEBUG == 1
        for (jj = 0; jj < *nIt; jj++)
            printf("k = %d\tsigma = %f\talpha = %f\tmu = %f\t\tmu = %e\n", jj,
                   stat[5 * jj], stat[5 * jj + 1], stat[5 * jj + 2],
                   stat[5 * jj + 2]);
        printf("\n");
#endif /* PC_DEBUG == 1 */

 	   }

/*printf("\nend of wrapper\n");*/

    return hpmpc_status;

}
