void parallel_mmt(int n,float c[][n],float a[][n], float b[][n]){
  int i,j,k;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      for(k=0;k<n;k++)
	c[j][i] = c[j][i] + a[k][i]*b[k][j];
}
