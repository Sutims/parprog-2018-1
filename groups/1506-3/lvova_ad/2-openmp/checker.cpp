#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm> 
#include <iostream>
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
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
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
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}

	// �������� ��������� �� checker' a ������������.
	//  ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}

	// �������� ����������� ������� ����� ������ ��������� ���������,
	// ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ ( -7) ���

	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}

	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;
////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// ��������� ���� ������� ������, ���� �������� ������ � ����� ���������
	FILE * bui = fopen("../massiv.in", "rb");
	FILE * buo = fopen("../massiv.out", "rb");
	int size;
	double res_time;


	// ��������� ����� ������ ��������� ���������
	fread(&res_time, sizeof(res_time), 1, buo);

	// ��������� ����������� �������
	fread(&size, sizeof(size), 1, bui);
	fread(&size, sizeof(size), 1, buo);


	// �������� ������ ��� ������� ������ ���� � ������ ���������
	double * answer = new double[size], * result = new double[size];
	
	// ���������  ������ ���������
	fread(result, sizeof(*result), size, buo);

	// ��������� �������� ������ ��� �������� ����������� ��������
	fread(answer, sizeof(*answer), size, bui);

	//��������� �������� ������ ����������� std
	sort(answer, answer+size);

	//���������� ������
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (answer[i] != result[i])
		{
            double k = result[i];
            std::cout << std::endl << "Numbers isn't equal - " << i << ";" << answer[i] << ";" << k << std::endl;
			checker_result.write_message("WA. Output is not correct.");
			checker_result.write_verdict(verdict::WA);
			flag = true;
			break;
		}
	}
	if(!flag)
	{
		std::cout << std::endl << "Numbers are equal" << std::endl;
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	
	// ���������� ����� � ���������� ����������� ( ��������� �� 100 �� = 10 ^ (-7) ���).
	checker_result.write_time(res_time * 1e7);
	fclose(bui);
	fclose(buo);
	return 0;
}