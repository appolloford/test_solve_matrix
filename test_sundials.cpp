// #include <cvode/cvode.h>  // prototypes for CVODE fcts., consts.
/* */
#include <nvector/nvector_serial.h>      // access to serial N_Vector
#include <sunlinsol/sunlinsol_dense.h>  // access to dense SUNLinearSolver
// #include <sunlinsol/sunlinsol_klu.h>     // access to KLU sparse direct solver
// #include <sunmatrix/sunmatrix_sparse.h>  // access to sparse SUNMatrix
/* */

#define Ith(v,i)                 NV_Ith_S(v,i)         /* Ith numbers components 1..NEQ */
#define IJth(A, i, j)            SM_ELEMENT_D(A, i, j)

int main() {

    // double a[2] = {1.0, 1.0e-3};
    double *a = new double [3];
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;

    // N_Vector b = N_VMake_Serial(2, a);
    N_Vector b = N_VNewEmpty_Serial(3);
    // N_Vector b = N_VNew_Serial(3);
    N_Vector r = N_VNew_Serial(3);
    SUNMatrix A = SUNDenseMatrix(3, 3);

    N_VConst(0.0, r);
    N_VSetArrayPointer(a, b);

    // for (int i=0; i<3; i++) {
    //     Ith(b, i) = i * 1.0 + 1.0;
    //     printf("Ith(b, %d) = %13.7e \n", i, Ith(b, i));
    // }

    // IJth(A, 0, 0) = 1.0;
    // IJth(A, 0, 1) = 0.0;
    // IJth(A, 0, 2) = 0.0;
    // IJth(A, 1, 0) = 0.0;
    // IJth(A, 1, 1) = 2.0;
    // IJth(A, 1, 2) = 0.0;
    // IJth(A, 2, 0) = 0.0;
    // IJth(A, 2, 1) = 0.0;
    // IJth(A, 2, 2) = 3.0;

    for (int j=0; j<3; j++) {
        realtype *colj = SUNDenseMatrix_Column(A, j);
        for (int k=0; k<3; k++) {
            colj[k] = 0.0;
            if  (j == k) {
                colj[k] = k * 1.0 + 1.0;
            }
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%13.7e ", IJth(A, i, j));
        }
        printf("\n");
    }

    SUNLinearSolver LS = SUNLinSol_Dense(r, A);

    int flag = SUNLinSolSetup(LS, A);
    flag = SUNLinSolSolve(LS, A, r, b, 0.0);

    printf("flag = %d\n", flag);

    double *rptr = N_VGetArrayPointer(r);
    double *bptr = N_VGetArrayPointer(b);

    for (int i = 0; i < 3; i++) {
        printf("rptr[%d] = %13.7e\n", i, rptr[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("bptr[%d] = %13.7e\n", i, bptr[i]);
    }

    return 0;
}

