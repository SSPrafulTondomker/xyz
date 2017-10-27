void p2opt(int n, double a[][n], double b[][n])
// make your changes to optimize this code 
{
  int i,j,k;
  for(i=0;i<n;i=i+8)
   for(j=0;j<n;j=j+1)
   {
/*   	for(k=0;k<4;k++)
    b[i][j+k] = 0.5*(a[i][j+k] + a[j+k][i]);
*/
	for(k=0;k<8;k++)
    b[i+k][j] = 0.5*(a[i+k][j] + a[j][i+k]);

   }
}
