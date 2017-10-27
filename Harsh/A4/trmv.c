void trmv_opt(int n, double A[][n], double x[n], double y[n])
{ 
// To be modified to achieve vectorization; additional transformations
// to improve performance should also be considered

  int i,j;
  for(i=0;i<n;i=i+2)
  {
    for(j=0;j<i+1;j=j+4)
    {
	      y[j] = y[j] + A[i][j]*x[i];
	      if (j+1<i+1)
	      {
	      	y[j+1] = y[j+1] + A[i][j+1]*x[i];
	      }
	      if (j+2<i+1)
	      {
	      	y[j+2] = y[j+2] + A[i][j+2]*x[i];
	      }
          if (j+3<i+1)
	      {
	      	y[j+3] = y[j+3] + A[i][j+3]*x[i];
	      }/*
	      if (j+4<i+1)
	      {
	      	y[j+4] = y[j+4] + A[i][j+4]*x[i];
	      }
	      if (j+5<i+1)
	      {
	      	y[j+5] = y[j+5] + A[i][j+5]*x[i];
	      }
          if (j+6<i+1)
	      {
	      	y[j+6] = y[j+6] + A[i][j+6]*x[i];
	      }
	      if (j+7<i+1)
	      {
	      	y[j+7] = y[j+7] + A[i][j+7]*x[i];
	      }*/
	}
	for(j=0;j<i+2;j=j+4)
    {
	      y[j] = y[j] + A[i+1][j]*x[i+1];
	      if (j+1<i+2)
	      {
	      	y[j+1] = y[j+1] + A[i+1][j+1]*x[i+1];
	      }
	      if (j+2<i+2)
	      {
	      	y[j+2] = y[j+2] + A[i+1][j+2]*x[i+1];
	      }
          if (j+3<i+2)
	      {
	      	y[j+3] = y[j+3] + A[i+1][j+3]*x[i+1];
	      }
	      /*if (j+4<i+2)
	      {
	      	y[j+4] = y[j+4] + A[i+1][j+4]*x[i+1];
	      }
	      if (j+5<i+2)
	      {
	      	y[j+5] = y[j+5] + A[i+1][j+5]*x[i+1];
	      }
          if (j+6<i+2)
	      {
	      	y[j+6] = y[j+6] + A[i+1][j+6]*x[i+1];
	      }
	      if (j+7<i+2)
	      {
	      	y[j+7] = y[j+7] + A[i+1][j+7]*x[i+1];
	      }*/
	    }
	}
}

