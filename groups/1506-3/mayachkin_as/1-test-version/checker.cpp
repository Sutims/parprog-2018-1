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
		switch (t)
		{
		case NO:
			fprintf(bur, "%s", "NO ");
			break;
		case VERDICT:
			fprintf(bur, "%s", "VERDICT ");
			break;
		case MESSAGE:
			fprintf(bur, "%s", "MESSAGE ");
			break;
		case TIME:
			fprintf(bur, "%s", "TIME ");
			break;
		case MEMORY:
			fprintf(bur, "%s", "MEMORY ");
			break;
		}
		//fwrite(&t, sizeof(t), 1, bur);
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
	void write_time(double x)
	{
		fprintf(bur, " ");
		write_type(ext_cls::TIME);
		fprintf(bur, " %f sec ", x);
		//fwrite(&x, sizeof(x), 1, bur);
	}
	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;

////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	result checker_result;

	int n = 20;
	string nameFile;
	bool result;

	for (int i = 1; i <= n; i++)
	{
		result = true;
		nameFile = to_string((long long)i);

		FILE* fRadixResult = fopen(("./tests/" + nameFile + ".ans").c_str(), "rb");
		FILE* fParallelResult = fopen(("./tests/" + nameFile + "_par.ans").c_str(), "rb");

		int sizeSeq;
		fread(&sizeSeq, sizeof(sizeSeq), 1, fRadixResult);

		double timeSeq;
		fread(&timeSeq, sizeof(timeSeq), 1, fRadixResult);

		double* RadixResult = new double[sizeSeq];
		fread(RadixResult, sizeof(*RadixResult), sizeSeq, fRadixResult);

		int sizePar;
		fread(&sizePar, sizeof(sizePar), 1, fParallelResult);

		double timePar;
		fread(&timePar, sizeof(timePar), 1, fParallelResult);

		double* ParallelResult = new double[sizePar];
		fread(ParallelResult, sizeof(*ParallelResult), sizePar, fParallelResult);

		if (sizeSeq != sizePar)
			result = false;
		else
		{
			for (int i = 0; i < sizeSeq; i++)
				if (ParallelResult[i] != RadixResult[i])
				{
					result = false;
					break;
				}
		}

		delete[] RadixResult;
		delete[] ParallelResult;

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

		checker_result.write_time(timeSeq);
		checker_result.write_time(timePar);
		fclose(fRadixResult);
		fclose(fParallelResult);
	}

	return 0;
}