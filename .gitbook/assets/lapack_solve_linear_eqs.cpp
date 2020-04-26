//https://software.intel.com/sites/products/documentation/doclib/mkl_sa/11/mkl_lapack_examples/sgesv_ex.c.htm
//
// Solve the following linear equations
// AX=B
// A = 0 5 5
//     2 9 0
//     6 8 8
// B = 1 1
//     2 4
//     3 0
// pivot: [2,1,3]

#include <iostream>

using namespace std;

// C wrapper for the LAPACK library
extern "C" {
extern void sgesv_(int*,int*,float*,int*,int*,float*,int*,int*);
}


int main(int argc, char** argv){

    int n= 3;
    int nrhs = 2;
    float A[] = {0,2,6,5,9,8,5,0,8};
    int lda = n;
    int ipiv[n];  //pivot indices. Array indice starts from 0 in Fortran
    float B[] = {1,2,3,1,4,0}; 
    int ldb = n;
    int info;
    
    //solve AX=B
    sgesv_(&n,&nrhs,A,&lda,ipiv,B,&ldb,&info);

    if(info == 0){
    //ipiv = {3,2,3}
    //swap 1st row with the 3th row
    //swap 2nd row with 2nd row
    //swap 3rd row with 3rd row
    cout << endl << "Pivot indices" << endl;
    for (int i=0; i<n; i++){
        cout << ipiv[i] << " ";
    }
    cout << endl;
    
    //print solution X which is stored in B
    cout << endl << "Solution" << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<nrhs; j++){
            cout << B[i + j*n] << " ";
        }
        cout << endl;
    }
    cout << endl;
    }
}

