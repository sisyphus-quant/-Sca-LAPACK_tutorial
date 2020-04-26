---
description: A tutorial on SCALAPACK and LAPACK
---

# SCALAPACK

Many C++ HPC libraries that I need to use in  work are built on SCALAPACK. When I try to teach myself about SCALAPACK I couldn't find any beginner-friendly tutorial on it, and it's official user guide is quite cryptic to me. Plus the fact that SCALAPACK is written in Fortran, which makes it even more incomprehensible for me. This is why I want to share my understanding of SCALAPACK here. 

During my self-learning process, I found that the best way to understand SCALAPACK is to first get a solid knowledge on LAPACK -- it's non-distributed version. Therefore, this is the approach we take in this tutorial. We first learn the implementation structure of LAPACK, its routine naming scheme, its relation with BLAS, and how to call LAPACK routine in C++. With such solid foundation, understanding SCALAPACK becomes very straightforward.

