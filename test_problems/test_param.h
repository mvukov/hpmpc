// problem size (states, inputs, horizon)
//#define NX 30
//#define NU 14
//#define NN 10

// number of inequality constraints
#define NL 0
#define NB 2*NU+2*NX

// number of repetition for timing
#define NREP 100

// print results
#define PRINTRES 1

// print statistics
#define PRINTSTAT 1

// double/single/mixed ('d'/'s'/'m') precision
#define PREC 's'

// number of iterations of IP method
#define K_MAX 10

// tolerance in the duality measure
#define TOL 1e-20

// threshold in the duality measure to switch from single to double precision
#define SP_THR 1e5





//// solver for LQ control problem: 1 kernel_single, 2 kernel_multiple, 3 BLAS
//#define LQS 1

//// ip method: 1 primal-dual, 2 predictor-corrector primal-dual
//#define IP 2

//// compute lagrangian multiplier pi TODO not implemented, set to 0 for now
//#define PI 0

//// force double precision (exact IP)
//#define DP 1

//// choose mixed precision (instead of double) in the inexact IP
//#define MP 1

//// number of iterative refinement steps in mixed precision
//#define IT_REF 1



