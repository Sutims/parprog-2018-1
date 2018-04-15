#include <omp.h>

void HoaraQuickSort(int* arr, int first, int last)
{
	int i = first, j = last;
	int temp, mid = arr[(first + last) / 2];

	do {
		while (arr[i] < mid)
			i++;
		while (arr[j] > mid)
			j--;

		if (i == j)
		{
			i++;
			j--;
		}

		if (i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		i++;
		j--;

	} while (i <= j);

#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section 
			{
		if (i < last)
			HoaraQuickSort(arr, i, last);
			}
#pragma omp section
			{
		if (first < j)
			HoaraQuickSort(arr, first, j);
			}
		}
	}
}
	
	
