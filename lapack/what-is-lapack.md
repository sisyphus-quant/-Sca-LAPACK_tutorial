---
description: >-
  LAPACK is a library of Fortran 77 which includes various standard linear
  algebra subroutines.
---

# Introduction

### Data type and precision

For most computations there are matching routines, one for real and one for complex data.

All routines are provided in both single and double precision versions.

### Naming Scheme

The name of each LAPACK subroutine is encoding a brief description of the computation it performs. It sometimes can be confusing and daunting for new beginners. However, its naming scheme is pretty straightforward and once understood can be very convenient to help you understand LAPACK codes.

All driver and computational routines have names of the format **XYYZZZ**. Only the last three letters indicate the computation performed, and thus they are parts of the name that you should pay most of the attention. Below are few examples of the meanings of **ZZZ**:

| ZZZ | Computation |
| :--- | :--- |
| LLS | Linear Least Square |
| SEP | Symmetric Eigenproblems |
| SVD | Singular Value Decomposition |

The two letters in the middle **YY** indicates the type \(structure\) of the matrix on which its computation apply. 

| YY | Type of matrix |
| :--- | :--- |
| DI | Diagonal |
| GE | General |
| OR | Orthogonal |
| TB | Triangular Band |

Finally, the first letter **X** specifies the data type and the precision:

| X | Precision & Data type |
| :--- | :--- |
| S | Real, Single precision |
| D | Real, Double precision |
| C | Complex, Single precision |
| Z | Complex, Double precision |

 In summary, a good practice is to read the name code backward. Usually, for fast reading code, just understand the last three letters is enough. Actually, it's a common practice to using xyyZZZ  to refer to all ZZZ subroutines. A list of Driver routines can be found at [here](http://sites.science.oregonstate.edu/~landaur/nacphy/lapack/simple.html).

