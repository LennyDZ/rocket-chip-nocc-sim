#include <stddef.h>

#include "dataset.h"


void thread_entry(int cid, int nc)
{
  static data_t res_data[ARRAY_SIZE];
  matmul(cid, nc, DIM_SIZE, input1_data, input2_data, res_data);
  
  complete(ARRAY_SIZE, res_data, verify_data);
}


//multiply a part of the matrix
void matmul(const size_t coreid, const size_t ncores, const size_t dim,  const data_t A[], const data_t B[], data_t C[])
{
  size_t i, j, k;
  size_t block = dim / ncores;
  size_t start = block * coreid;
 
  for (i = 0; i < dim; i++) {
    for (j = start; j < (start+block); j++) {
      data_t sum = 0;
      for (k = 0; k < dim; k++)
        sum += A[j*dim + k] * B[k*dim + i];
      C[i + j*dim] = sum;
    }
  }
}

//check if the result is correct
//out 0 mean it is
int verify(int n, const volatile int* test, const int* verify)
{
  int i;
  // Unrolled for faster verification
  for (i = 0; i < n/2*2; i+=2)
  {
    int t0 = test[i], t1 = test[i+1];
    int v0 = verify[i], v1 = verify[i+1];
    if (t0 != v0) fail();
    if (t1 != v1) fail();
  }
  if (n % 2 != 0 && test[n-1] != verify[n-1])
    fail();
  pass();
}