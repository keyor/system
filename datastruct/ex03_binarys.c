#include <stdio.h>

int binarySearch(int arr[], int len, int val)
{
	int low, high, mid;
	low = 0;
	high = len - 1;
	while(low < high)
	{
		mid = (low + high) / 2;
		if(arr[mid] == val)
			return mid;
		else if(arr[mid] > val)
			high = mid;
		else if(arr[mid] < val)
			low = mid;
	}
}

int main(void)
{
	int arr[5] = {1,2,3,6,9};

	int i = -1;
	i = binarySearch(arr, 5, 6);

	if(i != -1)
		printf("%d\n", arr[i]);
	
	return 0;
}
