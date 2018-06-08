#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <chrono>
#include <iostream>

using namespace std;

int n_tests[] = { 1, 2, 3, 4, 5, 6, 8, 10, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000,
50000000};
int main(int argc, char * argv[])
{
	if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20)
	{
		cout << "You use the \"Generator\" to create tests. Enter the arguments in the correct format !!" << endl;
		return 1;
	}
	int size = n_tests[atoi(argv[1]) - 1];
	double default_time = 0;
	
	// �������������� ����� stdout � ����
	freopen(argv[1], "wb", stdout);

	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	// ������ ����������� ������������� ��������� �������� ���� int � ���������
	// [-999, 999]
	uniform_int_distribution <int> distribution(-999, 999);

	fwrite(&default_time, sizeof(default_time), 1, stdout); // ����������� ���� ��� ������� � ����������� �����.
	fwrite(&size, sizeof(size), 1, stdout);

	int *arr = new int[size];
	for (int i = 0; i < size; i++) 
		arr[i] = distribution(generator);

	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}