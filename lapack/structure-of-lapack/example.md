---
description: >-
  To better understanding the structure we dissect the LAPACK subroutine which
  solve a set of linear equations. We first briefly review this problem.
---

# Example: solving real linear equations



### Problem review

Given real linear equation

$$
AX=B,
$$

we want to solve $$X$$given$$A$$ and $$B$$. Instead of inverting matrix $$A$$ which is costly, the common approach is to do a LU decomposition of $$A$$:

$$
A = LU.
$$

Here $$L(U)$$is a lower \(upper\) triangular matrix.  Sometime the resulting $$L(U)$$matrix could be singular, which will be a problem for later application. For singular matrix $$A$$, it turns out this is just a procedural problem, which can be avoided by a row permutation. This procedure is called LU decomposition with partial pivoting and it gives

$$
PA = LU.
$$

Substitute above factorization into our linear equation at the beginning, we have

$$
LUX = B',\\
B ' = PB.
$$

Now $$X$$can be solved easily by 

1. solving $$LY=B'$$for $$Y$$,
2. solving $$UX=Y $$for $$X$$.

Each of the step can be done by forward or backward substitution \(if you still can't see it, think of $$X$$and$$Y$$as collections of column vectors\).

### LAPACK implementation

The drive subroutine to solve real linear equations is `SGESV()`. Here is a good place to review LAPACK's naming scheme. **SV** represents solving, **GE** means the matrix $$A$$ in consideration is a general matrix, i.e., without any special structure. Finally, **S** indicates the linear system to be solved is real. The source code of this subroutine can be found [here](http://www.netlib.org/lapack/lapack-3.1.1/html/sgesv.f.html) . Below we put out the most important part of it:

```text
*
*     Compute the LU factorization of A.
*
      CALL SGETRF( N, N, A, LDA, IPIV, INFO )
      IF( INFO.EQ.0 ) THEN
*
*        Solve the system A*X = B, overwriting B with X.
*
         CALL SGETRS( 'No transpose', N, NRHS, A, LDA, IPIV, B, LDB,
     $                INFO )
      END IF
      RETURN
```

As we can see, it calls another two computation routines: `SGETRF()` and `SGETRS()`. `SGETRF()` carries out the LU factorization of $$A$$, replaces $$A$$ by  $$L+U-I$$\(the diagonal elements of $$L$$ can always be chosen to be 1\), and store the permutation indices in variable `IPIV`.  These output are then fed into `SGETRF()`, in where $$X$$is solved and replaces $$B$$.

The `SGETRF()` subroutine is tedious to explain. The only thing to remember is that it implements a block algorithm, i.e., it partitions input matrices into block size \(obtained by calling an auxiliary subroutine `ILAENV()`\) such that most of its operations calling Level-3 BLAS. 

Since the implementation of `SGETRS()` is pretty simple, we use it to illustrate how the BLAS subroutines are called by the computation subroutines. Again, below we show the most important part of [sgetrs.f](http://www.netlib.org/lapack/lapack-3.1.1/html/sgetrs.f.html#SGETRS.1):

```text
*
*        Solve A * X = B.
*
*        Apply row interchanges to the right hand sides.
*
         CALL SLASWP( NRHS, B, LDB, 1, N, IPIV, 1 )
*
*        Solve L*X = B, overwriting B with X.
*
         CALL STRSM( 'Left', 'Lower', 'No transpose', 'Unit', N, NRHS,
     $               ONE, A, LDA, B, LDB )
*
*        Solve U*X = B, overwriting B with X.
*
         CALL STRSM( 'Left', 'Upper', 'No transpose', 'Non-unit', N,
     $               NRHS, ONE, A, LDA, B, LDB )
```

`SLASWP()` is a LAPACK auxiliary routine, which performs a sequence of row permutations according to `IPIV`. This gives $$B'=PB $$. It then calls twice the `STRSM()` , a Level-3 BLAS subroutine, which solves equation like $$TX=aB$$ , where $$T$$ is either an upper or a lower triangular matrix. Documentation of `STRSM()` can be found at [here](http://www.netlib.org/lapack/explore-html/db/dc9/group__single__blas__level3_ga9893cceb3ffc7ce400eee405970191b3.html#ga9893cceb3ffc7ce400eee405970191b3).

