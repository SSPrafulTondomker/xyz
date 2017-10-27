void parallel_mmt(int n,float c[][n],float a[][n], float b[][n],int nThreads)
{
        int i,j,k,kt,l,chunk=100,T=16,tile_size = 16,ii,jj,kk,sum;
        omp_set_num_threads(nThreads);
        int t_id     = omp_get_thread_num(),p=0,m=0;
        int b_size = 1024 / omp_get_num_threads();
        #pragma omp parallel for private(i,l,k,j,m)
        for (j = t_id * b_size; j < (t_id+1) * b_size; j=j+1)
        {
                for(kt=0;kt<n;kt=kt+T)
                for(k=kt;k<kt+T;k=k+8)
                {
                        for(i=0;i<n;i=i+8)
                        {
                                for(m=0;m<8;m++)
                                for(l=0;l<8;l++)
                                {
                                        c[j+p][i+l]+=  a[k+m][i+l]*b[k+m][j+p];
                                }       
                        }
                }
        }
}
