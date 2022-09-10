#include <stdio.h>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

int main()
{
    ublas::compressed_matrix<double, ublas::column_major, 0> A(3, 3, 9);
    // ublas::matrix<double> A(3, 3);

    for (int j=0; j<3; j++) {
        for (int k=0; k<3; k++) {
            A(j, k) = 0.0;
            if  (j == k) {
                A(j, k) = k * 1.0 + 1.0;
            }
        }
    }


    ublas::vector<double> y(3);
    y(0) =  1;
    y(1) =  2;
    y(2) =  3;

    ublas::permutation_matrix<size_t> pm(A.size1());
    lu_factorize(A, pm);
    lu_substitute(A, pm, y);

    for (int i=0; i<3; i++) printf("y[%d] = %13.7e\n", i, y[i]);
}
