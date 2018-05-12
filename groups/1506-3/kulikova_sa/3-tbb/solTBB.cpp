#include "Sole.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

int size_TBB = 0;

double vec_TBB(double * x, double * y) {
	double res = 0;
	for (int i = 0; i < size_TBB; i++)
		res += x[i] * y[i];
	return res;
}

void NonlinearConjugateGradient_TBB(Sole * S, int num) {
	tbb::task_scheduler_init init(num);
	size_TBB = S->N;//������� �������

	//��������� ������
	double * x = new double[size_TBB];//������ �����������
	double * d = new double[size_TBB];//������ �����������
	double * g = new double[size_TBB];//��������
	double s;//��������� ���, �������� �������� �� ��������� �����������
	double coef;//����������� �� 2 ����
	double * s_prev = new double[size_TBB];//������������ ������� ����������� � �������
	double * x_prev = new double[size_TBB];//���������� �����������
	double * d_prev = new double[size_TBB];//���������� ������ �����������
	double * g_prev = new double[size_TBB];//���������� ��������

	//����� ����������� ������ �������� x0 � d0 ���������� ������� ����
	// ��� ������� g0 ��������������� �������� -b
	tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
	[=, &x_prev, &d_prev, &g_prev](const tbb::blocked_range<int>& r) {
		for (int i = r.begin(); i != r.end(); i++) {
			x_prev[i] = 0;
			d_prev[i] = 0;
			g_prev[i] = S->b[i] * (-1);
		}
	}
	);

	//���� �� ���������� ��������
	for (int i = 0; i < size_TBB; i++) {
		//1. ���������� ���������
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &g](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				g[j] = vec_TBB(S->A[j], x_prev) - S->b[j];
		}
		);

		//2. ���������� ������� �����������
		coef = vec_TBB(g, g) / vec_TBB(g_prev, g_prev);
		if (isnan(coef)) coef = 0;
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &d](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				d[j] = coef * d_prev[j] - g[j];
		}
		);

		//3. ���������� �������� �������� �� ��������� �����������
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &s_prev](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				s_prev[j] = vec_TBB(S->A[j], d);
		}
		);
		s = vec_TBB(d, g) / vec_TBB(s_prev, d);
		if (isnan(s)) s = 0;

		//4. ���������� ������ �����������
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &x](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				x[j] = x_prev[j] - s * d[j];
		}
		);

		//������ ������� �� ����������
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &g_prev, &d_prev, &x_prev](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++) {
				g_prev[j] = g[j];
				d_prev[j] = d[j];
				x_prev[j] = x[j];
			}
		}
		);
	}

	//���������� ����������
	tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
		[=, &S](const tbb::blocked_range<int>& r) {
		for (int i = r.begin(); i != r.end(); i++)
			S->x[i] = x[i];
	}
	);

	//������������ ������
	delete[] x;
	delete[] d;
	delete[] g;
	delete[] s_prev;
	delete[] x_prev;
	delete[] d_prev;
	delete[] g_prev;
}
