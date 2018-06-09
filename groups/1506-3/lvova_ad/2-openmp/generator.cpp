#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;
int n_tests[] = { 1, 10, 50, 100,300, 500, 750, 1000, 1500, 2500, 5000, 7000,8500, 10000, 15000, 20000 , 25000 ,500000, 700000 ,1000000 };

int main(int argc, char * argv[])
{
	// �������������� ����� stdout � ���� matr. in
	FILE *output_file = fopen("../massiv.in", "wb");
	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// ������ ����������� ������������� ��������� �������� ���� double � ���������
	// [ -10000, 10000]
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// ����� ������ ������� �� ���������
	int n = 1;
	// ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests
	if (argc > 1)
		n = n_tests[atoi(argv[1])];
	// ���������� � �������� ���� ����������� ������
	fwrite(&n, sizeof(n), 1, output_file);
	// ������ ��������� ������ ��� ������ �������
	double * current = new double[n];
	// ���������� ������
	for (int i = 0; i < n; i++)
	{
		// ��������� ���������� ������� ������ �� ������������ �������������
		current[i] = distribution(generator);
	}
	// ���������� ������ � �������� ���� � ����
	fwrite(current, sizeof(*current), n, output_file);

	fclose(output_file);
	return 0;
}
