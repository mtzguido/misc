
void smallest(int* arr, int len, int m)
{
	int p;
	int i,j;
	int t;
	
	p = arr[0];
	j = 0; //1..j menores a p
		   //j+1..i mayoresiguales a p
	
	for(i=1;i<len;++i)
	{
		if(arr[i]<p)
		{
			j++;
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	
	t = arr[j];
	arr[j] = arr[0];
	arr[0] = t;
	
	if(m > j+1)
	{
		smallest(arr+j+1,len-j-1,m-j-1);
	} else if(m < j+1) {
		smallest(arr,j+1,m);
	}
}

