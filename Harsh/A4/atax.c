void atax_opt(int n, double A[][n], double x[n], double y[n])
{ int i,j;
// Modify code to enable vectorization and improved performance
  double temp[n];
  for(i=0;i<n;i++) temp[i] = 0;
  
  for(j=0;j<n;j=j+1)
  {  
    for(i=0;i<n;i=i+8)
    {
      temp[j] += A[j][i]*x[i];
      temp[j] += A[j][i+1]*x[i+1];
      temp[j] += A[j][i+2]*x[i+2];
      temp[j] += A[j][i+3]*x[i+3];
      temp[j] += A[j][i+4]*x[i+4];
      temp[j] += A[j][i+5]*x[i+5];
      temp[j] += A[j][i+6]*x[i+6];
      temp[j] += A[j][i+7]*x[i+7];
    }
    for(i=0;i<n;i=i+8)
    {
      y[i] += A[j][i]*temp[j];
      y[i+1] += A[j][i+1]*temp[j];
      y[i+2] += A[j][i+2]*temp[j];
      y[i+3] += A[j][i+3]*temp[j];
      y[i+4] += A[j][i+4]*temp[j];
      y[i+5] += A[j][i+5]*temp[j];
      y[i+6] += A[j][i+6]*temp[j];
      y[i+7] += A[j][i+7]*temp[j];
    }
  }
// Next compute y = (A^T)temp
/*    for(j=0;j<n;j=j+1)
  for(i=0;i<n;i=i+1)
    {
      y[i] += A[j][i]*temp[j];
      //y[i+1] += A[j][i+1]*temp[j];
      //y[i] += A[j+1][i]*temp[j+1];
    }*/
}

