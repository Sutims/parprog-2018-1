
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>

#include <omp.h>
using namespace std;
// ������������ ��� �������������� � ����������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ����� ������������� ��� ��� ��� ��������:
AC = Accepted = ������� ����� ���������� ��������� �� ������ �����
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ �����
PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� �������������
NO = No verdict = ������� �����������
CE = Compilation Error = ������ ����������
ML = Memory Limit Exceeded = ��������� ����������� �� ������
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������
RE = Runtime Error = ������ ������� ���������� ���������
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ���������
DE = Deadly Error = ������ ����������� �������
*/

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r");
		else bur = fopen("result.txt", "w");
	}
	~result()
	{
		fclose(bur);
	}
	void write_type(ext_cls t)
	{
		fwrite(&t, sizeof(t), 1, bur);
	}
	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, bur);
	}
	// �������� ��������� �� checker'a ������������.
	// ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// �������� ����������� ������� ����� ������ ��������� ���������,
	// ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ (-7) ���
	void write_time(long long x)
	{
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof(x), 1, bur);
	}
	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;

void BubbleSort(double* data, int dataLength) //���������� ���������
{
	for (int i = 0; i < dataLength; i++)
		for (int j = 0; j < dataLength - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				double temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	bool result = true;

	FILE * in = fopen("1", "rb");
	FILE * out = fopen("1.ans", "rb");

	int size;
	fread(&size, sizeof(size), 1, in);

	double radixTime;
	double* radixResult = new double[size];
	fread(&radixTime, sizeof(radixTime), 1, out);
	fread(radixResult, sizeof(*radixResult), size, out);


	double* bubbleResult = new double[size];
	fread(bubbleResult, sizeof(*bubbleResult), size, in);

	//BubbleSort(bubbleResult, size);
	sort(bubbleResult, bubbleResult + size);

	for (int i = 0; i < size; i++)
		if (bubbleResult[i] != radixResult[i])
		{
			result = false;
			break;
		}

	delete[] radixResult;
	delete[] bubbleResult;

	if (result)
	{
		checker_result.write_message("AC. Output is correct. ");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("WA. Output is not correct. ");
		checker_result.write_verdict(verdict::WA);
	}

	checker_result.write_time(radixTime * 1e7);


	return 0;
}