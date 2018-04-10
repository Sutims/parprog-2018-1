#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <ccomplex>

using namespace std;

/* // Checker ����� ������������� ��� ��� ��� ��������:
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
DE = Deadly Error = ������ ����������� ������� */

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r");
		else
			bur = fopen("result.txt", "w");
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
	//   ��������, ��� ������� ������, ��� ��������.
	//   ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}

	// �������� ����������� ������� ����� ������ ��������� ���������,
	//   ����������� � ������� before_code
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

int main(int argc, char* argv[]) {

	char* input = "matr.in";	
	char* output = "matr.out";	
	char* answer = "answer.txt";	


	if (argc > 1)
	{
		input = argv[1];
		if (argc > 2)
		{
			output = argv[2];
			if (argc > 3)
				answer = argv[3];
		}
	}
	

	// ��������� ���� ������� ������, ���� �������� ������ � ����� ���������
	FILE * bui = fopen(input, "rb"); 
	FILE * buo = fopen(output, "rb");
	FILE * bua = fopen(answer, "rb");

	double res_time;
	double ans_time;

	int n;
						// ��������� ����� ����������
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&ans_time, sizeof(ans_time), 1, bua);

	//��������� ����������� ������
	fread(&n, sizeof(n), 1, bui);

	int notNull;

	fread(&notNull, sizeof(notNull), 1, buo);

	// �������� ������ ��� ������� ������ ���� � ������ ���������
	vector<complex<int>> elements(notNull);
	vector<int> secondIndex(notNull);
	vector<int> position(n + 1);

	vector<vector<complex<int>>> MatrixO(n);
	vector<vector<complex<int>>> MatrixA(n);
	for (int i = 0; i < n; ++i)
	{
		MatrixO[i].resize(n);
		MatrixA[i].resize(n);
	}

	// ��������� ������� ���������
	fread(elements.data(), sizeof(elements[0]), notNull, buo);
	fread(secondIndex.data(), sizeof(secondIndex[0]), notNull, buo);
	fread(position.data(), sizeof(position[0]), n + 1, buo);

	// ��������� ������� ����
	for (int i = 0; i < n; ++i)
		fread(MatrixA[i].data(), sizeof(MatrixA[i][0]), n, bua);

	//��������� ������� ��������� � ����������� ���
	for (int i = 0; i < n; ++i)
	{
		int pos = position[i];
		while (pos < position[i + 1])
		{
			MatrixO[i][secondIndex[pos]] = elements[pos];
			pos++;
		}
	}

	// ��������� ������, ��� ������� ����� �������� �������
	complex<int> diff;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; ++j)
			diff += (MatrixA[i][j] - MatrixO[i][j]) * (MatrixA[i][j] - MatrixO[i][j]);
	complex<int> value;
	// ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������.
	if ((double)diff.real() < 1e-6)
	{
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}

	// ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���).
	checker_result.write_time(res_time * 1e7);

	fclose(bui);
	fclose(bua);
	fclose(buo);

	return 0;
}