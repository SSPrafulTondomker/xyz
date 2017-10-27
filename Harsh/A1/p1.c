void p1opt(int n, double A[][n], double x[n], double y[n], double z[n])
{
        int i,j,k,div=5,l,T=500,it,jt;

        for(jt=0;jt<n;jt=jt+T)
                for(it=0;it<n;it=it+T)
                        for(j=jt;j<jt+T;j=j+div)
                        {
                                for(i=it;i<it+T;i=i+div)
                                {
                                        for(l=0;l<div;l++)
                                        {
                                                for(k=0;k<div;k++)
                                                {
                                                        y[i+k] = y[i+k] + A[j+l][i+k]*x[j+l];
                                                }
                                        }
                                }
                        }
        for(it=0;it<n;it=it+T)
                for(jt=0;jt<n;jt=jt+T)
                        for(i=it;i<it+T;i=i+div)
                        {
                                for(j=jt;j<jt+T;j=j+div)
                                {
                                        for(l=0;l<div;l++)
                                        {
                                                for(k=0;k<div;k++)
                                                {
                                                        z[i+k] = z[i+k] + A[i+k][j+l]*x[j+l];
                                                }
                                        }
                                }
                        }
}

