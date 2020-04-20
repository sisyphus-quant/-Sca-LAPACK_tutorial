# Subroutines

Subroutines of LAPACK can be classified into three categories:

* Driver routines
* Computational routines
* BLAS and auxiliary routines

They are arranged in a top-down order -- a subroutine in each category calls various subroutines from the underlying category. Most of the lowest level operations, like matrix multiplications, are performed by the Basic Linear Subprograms \(BLAS\). Elementary operations that are not covered by the BLAS or those that are extensions of BLAS comprised the auxiliary routines.

The top two layers are designed mainly to simply the API and to organize the library. The underlying BLAS layer is central to the portability and the efficiency of LAPACK, since BLAS is usually highly optimized by the vendors for their machines. There are three levels of BLAS :

* Level 1 vector operations, such as $$ax+y$$
* Level 2 matrix- vector operators, such as $$aAx + by$$ 
* Level 3 matrix-matrix operations, such as $$aAB +bC$$ 

Since Level 3 operations achieve near-peak performance on most of the vector processors, the central idea behind LAPACK is to implement **block algorithms** for its subroutines such that most low level operations call Level 3 BLAS. This is perhaps the most point to remember about LAPACK.

