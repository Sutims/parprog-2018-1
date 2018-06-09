#define _CRT_SECURE_NO_WARNINGS

#include <omp.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
#include<iterator>
#include <algorithm>
using namespace std;

void QuickSort(double* arr, int size);
int Bin_Search_ind(const std::vector<double> arr, int left, int right, double key);//�������� ����� ������������� �������� ����� ������������ key
void ShareAndMerge(std::vector<double> vec1, std::vector<double> vec2, double* write_to);

int main(int argc, char * argv[])
{
	if (argc != 4) {
		std::cout << "Use 'omp_qs [threads] [input file] [output file]'" << std::endl;
		return 1;
	}

	int size, threads = atoi(argv[1]);
	double* arr;
	double fict_time;

	freopen(argv[2], "rb", stdin);
	fread(&fict_time, sizeof(fict_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	arr = new double[size];

	fread(arr, sizeof(*arr), size, stdin);

	double time = omp_get_wtime();
	int step;
	std::vector<double>* tempArray = new std::vector<double>[threads]; //������ 4� �������� 
	int *shift = new int[threads], *chunk = new int[threads]; //����� ������������ ������, ����� ������������ ������
#pragma omp parallel shared(arr, step, shift, chunk, tempArray) num_threads(threads) 
	{
		int tid, thread_index; //�� �������� ������ 
		tid = omp_get_thread_num();

		shift[tid] = tid * (size / threads); //������ � �������� ����� �����������

		chunk[tid] = (tid == threads - 1) ? size - tid * (size / threads) : size / threads;

		QuickSort(arr + shift[tid], chunk[tid]);

#pragma omp barrier //����� ��� ������

		step = 1; //��� ��������
		while (step < threads) {
			thread_index = (int)pow(2, step - 1); //��������� ����� ���������� �����

			for (int i = 0; i < chunk[tid]; ++i) { //��������� ������ ����� ��������� ������� � ������ ������
				tempArray[tid].push_back(*(arr + shift[tid] + i));
			}

#pragma omp barrier //���� ��� ������
			if (tid % (thread_index * 2) == 0) { //� ������ ���� ����� ����� 
				ShareAndMerge(tempArray[tid], tempArray[tid + thread_index], &arr[shift[tid]]);
				chunk[tid] += chunk[tid + thread_index];
				tempArray[tid].clear(); tempArray[tid].shrink_to_fit(); //�������� ������
				tempArray[tid + thread_index].clear(); tempArray[tid + thread_index].shrink_to_fit();
			}
#pragma omp single 
			{
				step *= 2;
			}
#pragma omp barrier
		}
	}
	delete[] tempArray;
	delete[] chunk;
	delete[] shift;

	time = omp_get_wtime() - time;

	printf("OpenMP time: %f\n", time);

	freopen(argv[3], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);

	return 0;

}