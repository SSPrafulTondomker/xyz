void Merge_Sort_Par(int a[],int b[],int size, int nThreads)
{
  omp_set_num_threads(nThreads);
  if (size < 2) return;
#pragma omp parallel sections
        {
   #pragma omp section 
   Merge_Sort_Par(a, b,  size/2,nThreads/2);
   #pragma omp section 
   Merge_Sort_Par(a + size/2, b + size/2, size-size/2, nThreads-nThreads/2);
}
   #pragma omp taskwait
            {
    int i1 = 0;
	int i2 = size / 2;
	int it = 0,i;

	while(i1 < size/2 && i2 < size) {
		if (a[i1] <= a[i2]) {
			b[it] = a[i1];
			i1 += 1;
		}
		else {
			b[it] = a[i2];
			i2 += 1;
		}
		it += 1;
	}

	while (i1 < size/2) {
	    b[it] = a[i1];
	    i1++;
	    it++;
	}
	while (i2 < size) {
	    b[it] = a[i2];
	    i2++;
	    it++;
	}
	for(i=0;i<size;i++)
		a[i]=b[i];
}
}
