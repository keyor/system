#include <stdio.h>

void bubblesort(int *arr, int len)
{
	int i, j, temp;
	for(i = len; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(void)
{
	int arr[5] = {5,4,3,2,1};

	bubblesort(arr, 5);

	int i;

	for(i = 0; i < 5; i++)
	{
		printf("%3d\n", arr[i]);
	}

	return 0;
}
