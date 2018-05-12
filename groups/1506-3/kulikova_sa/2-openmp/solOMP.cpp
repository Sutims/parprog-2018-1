#include <omp.h>
#include "Sole.h"

int size_OMP = 0;

double vec_OMP(double * x, double * y) {
	double res = 0;
#pragma omp parallel for reduction(+:res)
	for (int i = 0; i < size_OMP; i++)
		res += x[i] * y[i];
	return res;
}

void NonlinearConjugateGradient_OMP(Sole * S, int num) {
	omp_set_num_threads(num);
	size_OMP = S->N;// ������� �������

				// ��������� ������
	double * x = new double[size_OMP];// ������ �����������
	double * d = new double[size_OMP];// ������ �����������
	double * g = new double[size_OMP];// ��������
	double s;// ��������� ���, �������� �������� �� ��������� �����������
	double coef;// ����������� �� 2 ����
	double * s_prev = new double[size_OMP];// ������������ ������� ����������� � �������
	double * x_prev = new double[size_OMP];// ���������� �����������
	double * d_prev = new double[size_OMP];// ���������� ������ �����������
	double * g_prev = new double[size_OMP];// ���������� ��������

									   // ����� ����������� ������ �������� x0 � d0 ���������� ������� ����
									   // ��� ������� g0 ��������������� �������� -b
#pragma omp parallel for
	for (int i = 0; i < size_OMP; i++) {
		x_prev[i] = 0;
		d_prev[i] = 0;
		g_prev[i] = S->b[i] * (-1);
	}

	// ���� �� ���������� ��������
	for (int i = 0; i < size_OMP; i++) {
		// 1. ���������� ���������
#pragma omp parallel for
		for (int j = 0; j < size_OMP; j++)
			g[j] = vec_OMP(S->A[j], x_prev) - S->b[j];

		// 2. ���������� ������� �����������
		coef = vec_OMP(g, g) / vec_OMP(g_prev, g_prev);
		if (isnan(coef)) coef = 0;
#pragma omp parallel for
		for (int j = 0; j < size_OMP; j++)
			d[j] = coef * d_prev[j] - g[j];

		// 3. ���������� �������� �������� �� ��������� �����������
#pragma omp parallel for
		for (int j = 0; j < size_OMP; j++)
			s_prev[j] = vec_OMP(S->A[j], d);
		s = vec_OMP(d, g) / vec_OMP(s_prev, d);
		if (isnan(s)) s = 0;

		// 4. ���������� ������ �����������
#pragma omp parallel for
		for (int j = 0; j < size_OMP; j++)
			x[j] = x_prev[j] - s * d[j];

		// ������ ������� �� ����������
#pragma omp parallel for
		for (int j = 0; j < size_OMP; j++) {
			g_prev[j] = g[j];
			d_prev[j] = d[j];
			x_prev[j] = x[j];
		}
	}

	// ���������� ����������
#pragma omp parallel for
	for (int i = 0; i < size_OMP; i++)
		S->x[i] = x[i];

	// ������������ ������
	delete[] x;
	delete[] d;
	delete[] g;
	delete[] s_prev;
	delete[] x_prev;
	delete[] d_prev;
	delete[] g_prev;
}
