#include <cstdio>
#include <cmath>
#include <string>
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
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������ RE = Runtime Error = ������ ������� ���������� ���������
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
		if (read) freopen_s(&bur, "result.txt", "rb", stdin); else freopen_s(&bur,"result.txt", "wb",stdout);
	} ~result() { fclose(bur); }
	void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }
	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}
	// �������� ��������� �� checker'a ������������.
	//   ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// �������� ����������� ������� ����� ������ ��������� ���������,
	//   ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ (-7) ���
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

FILE *stream;

int main(int argc, char * argv[]) {
	// ��������� ���� ������� ������, ���� �������� ������ � ����� ���������
	const char* vx = "1";
	const char* ans_ser = "1.ans";
	const char* ans_par = "1_omp.ans";
	char er;
	int n;
	double *a;
	double *b;
	if (argc > 1)
		vx = argv[1];
	if (argc > 2)
		ans_ser = argv[2];
	if (argc > 3)
		ans_par = argv[3];
	freopen_s(&stream, vx, "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	a = new double[n];
	b = new double[n];
	double *dop = new double[n];
	fread(dop, sizeof(*dop), n, stdin);
	fread(a, sizeof(*a), n, stdin);
	fread(b, sizeof(*b), n, stdin);
	fclose(stream);

	double ans, res, ans_time, res_time; //ans-���������������� res-������������

	freopen_s(&stream, ans_ser, "rb", stdin);
	fread(&ans_time, sizeof(ans_time), 1, stdin);
	fread(&ans, sizeof(ans), 1, stdin);
	fread(&er, sizeof(char), 1, stdin);
	fclose(stream);

	freopen_s(&stream, ans_par, "rb", stdin);
	fread(&res_time, sizeof(res_time), 1, stdin);
	fread(&res, sizeof(ans), 1, stdin);
	fclose(stream);
	// ��������� ������
	double eps = 0;
	for (int i = 0; i < n; i++)
	{
		eps += (double)pow((b[i] - a[i]), 3)*pow(b[i], 4) / (24 * pow(50, 2));
	}
	// ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������.
	
	if (er != 'e')
	{
		if (abs(res - ans) <= eps)
		{
			checker_result.write_message("AC. Numbers are equal.");
			checker_result.write_verdict(verdict::AC);
		}
		else
		{
			checker_result.write_message("WA. Output is not correct.");
			checker_result.write_verdict(verdict::WA);
		}
	}
	else
	{
		checker_result.write_message("NO. Intput is not correct.");
		checker_result.write_verdict(verdict::NO);
	}
	// ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���).
	checker_result.write_time((ans_time - res_time) * 1e7);
	return 0;
}