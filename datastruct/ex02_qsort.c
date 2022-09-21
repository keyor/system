#include <stdio.h>

void qsort(int *arr, int low, int high)
{
	if(low < high)
	{
		int i = low;
		int j = high;
		int k = arr[i];
		while(i < j)
		{
			while(i < j && arr[j] >= k)
				j--;
			if(i < j)
				arr[i++] = arr[j];
			while(i < j && arr[i] <= k)
				i++;
			if(i < j)
				arr[j--] = arr[i];
		}
		arr[j] = k;
		qsort(arr, low, i - 1);
		qsort(arr, i + 1, high);
	}
}

int main(void)
{
	int arr[5] = {5,4,3,2,1};

	qsort(arr, 0, 4);

	int i;
	
	for(i = 0; i < 5; i++)
	{
		printf("%3d\n", arr[i]);
	}

	return 0;
}
