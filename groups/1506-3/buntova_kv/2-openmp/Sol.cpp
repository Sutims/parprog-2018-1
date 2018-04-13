#include <cmath>
#include <omp.h>

//1-ln,	2-cos,	3-sin	,4-exp,	5-x^2,	6-x^3,	7-x^4,	8-x^5,	9-x^6,	10-x^1/2,	11-x^1/3,	12-x^1/4
double func(double* x, int *c, int *z, int k) //c-���-�� ����������, z-����� ����� �-�� �� ����������
{
	double res = 0;
	for (int i = 0; i < k; i++)
	{
		switch (c[i])
		{
		case 1:
			if (x[i] < 0)
			{
				return 1000000;
			}
			switch (z[i])
			{
			case 1:
				res += log(x[i]);
				break;
			case 2:
				res -= log(x[i]);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= log(x[i]);
				break;
			case 4:
				if (log(x[i]) == 0)
					return 1000000;
				if (res == 0)
					res = 1;
				res /= log(x[i]);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 2:
			switch (z[i])
			{
			case 1:
				res += cos(x[i]);
				break;
			case 2:
				res -= cos(x[i]);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= cos(x[i]);
				break;
			case 4:
				if (cos(x[i]) == 0)
					return 1000000;
				if (res == 0)
					res = 1;
				res /= cos(x[i]);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 3:
			switch (z[i])
			{
			case 1:
				res += sin(x[i]);
				break;
			case 2:
				res -= sin(x[i]);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= sin(x[i]);
				break;
			case 4:
				if (sin(x[i]) == 0)
					return 1000000;
				if (res == 0)
					res = 1;
				res /= sin(x[i]);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 4:
			switch (z[i])
			{
			case 1:
				res += exp(x[i]);
				break;
			case 2:
				res -= exp(x[i]);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= exp(x[i]);
				break;
			case 4:
				if (exp(x[i]) == 0)
					return 1000000;
				if (res == 0)
					res = 1;
				res /= exp(x[i]);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 5:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 2);
				break;
			case 2:
				res -= pow(x[i], 2);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 2);
				break;
			case 4:
				if (pow(x[i], 2) == 0)
					return 1000000;
				if (res == 0)
					res = 1;
				res /= pow(x[i], 2);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 6:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 3);
				break;
			case 2:
				res -= pow(x[i], 3);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 3);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 3) == 0)
					return 1000000;
				res /= pow(x[i], 3);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 7:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 4);
				break;
			case 2:
				res -= pow(x[i], 4);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 4);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 4) == 0)
					return 1000000;
				res /= pow(x[i], 4);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 8:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 5);
				break;
			case 2:
				res -= pow(x[i], 5);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 5);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 5) == 0)
					return 1000000;
				res /= pow(x[i], 5);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 9:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 6);
				break;
			case 2:
				res -= pow(x[i], 6);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 6);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 6) == 0)
					return 1000000;
				res /= pow(x[i], 6);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 10:
			if (x[i] < 0)
			{
				return 1000000;
			}
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 1.0 / 2.0);
				break;
			case 2:
				res -= pow(x[i], 1.0 / 2.0);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 1.0 / 2.0);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 1.0 / 2.0) == 0)
					return 1000000;
				res /= pow(x[i], 1.0 / 2.0);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 11:
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 1.0 / 3.0);
				break;
			case 2:
				res -= pow(x[i], 1.0 / 3.0);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 1.0 / 3.0);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 1.0 / 3.0) == 0)
					return 1000000;
				res /= pow(x[i], 1.0 / 3.0);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		case 12:
			if (x[i] < 0)
			{
				return 1000000;
			}
			switch (z[i])
			{
			case 1:
				res += pow(x[i], 1.0 / 4.0);
				break;
			case 2:
				res -= pow(x[i], 1.0 / 4.0);
				break;
			case 3:
				if (res == 0)
					res = 1;
				res *= pow(x[i], 1.0 / 4.0);
				break;
			case 4:
				if (res == 0)
					res = 1;
				if (pow(x[i], 1.0 / 4.0) == 0)
					return 1000000;
				res /= pow(x[i], 1.0 / 4.0);
				break;
			default:
				return 1000000;
				break;
			}
			break;
		default:
			return 1000000;
			break;
		}
	}
	return res;
}

double solver(double* a, double *b, int* f, int* z, int n, int kol)
{
	double *h = new double[kol];
	double res = (double)0;//s
	double* c = new double[kol];
	for (int i = 0; i < kol; i++)
	{
		h[i] = (b[i] - a[i]) / n;
		c[i] = a[i] + h[i] / 2;
	}
	for (int i = 0; i < pow(n, kol - 1); i++)
	{
		for (int j = 0; j < n; j++)
		{
			double m = func(c, f, z, kol);
			if (m == 1000000)
			{
				res = 1000000;
				return res;
			}
			else
			{
				res += m;
			}
			c[kol - 1] += h[kol - 1];
		}
		for (int j = kol-1; j >= 0; j--)
		{
			if (c[j] > b[j])
			{
				c[j - 1] += h[j - 1];
				c[j] = a[j] + h[j] / 2;
			}
		}
	}
	for (int i = 0; i < kol; i++)
	{
		res *= h[i];
	}
	//delete[]h;
	//delete[]c;
	return res;
}

double iter(double* a, double *b, double *h,double *c, int* f, int* z, int n,int kol,int num)
{
	double res=0;
	c[0] = a[0] + h[0] / 2 + num * h[0];
	if (kol == 1)
	{
		double m = func(c, f, z, kol);
		if (m == 1000000)
		{
			res = 1000000;
			return res;
		}
		else
		{
			res += m;
		}
		return res;
	}
	for (int i = 0; i < pow(n, kol - 2); i++)
	{
		for (int j = 0; j < n; j++)
		{
			double m = func(c, f, z, kol);
			if (m == 1000000)
			{
				res = 1000000;
				return res;
			}
			else
			{
				res += m;
			}
			c[kol - 1] += h[kol - 1];
		}
		for (int j = kol-1; j > 0; j--)
		{
			if (c[j] > b[j])
			{
				c[j - 1] += h[j - 1];
				c[j] = a[j] + h[j] / 2;
			}
		}
	}
	
	return res;
}
double solver_par(double* a, double *b, int* f, int* z, int n, int kol,int num_threads)
{
	double *h = new double[kol];
	double res = (double)0;//s
	double* c = new double[kol];
	for (int i = 0; i < kol; i++)
	{
		h[i] = (b[i] - a[i]) / n;
		c[i] = a[i] + h[i] / 2;
	}

	#pragma omp parallel for num_threads(num_threads)  schedule(dynamic,3) reduction(+:res)
	for (int i = 0; i < n; i++)
		res+=iter(a, b, h, c, f, z, n, kol,i);

	#pragma omp parallel for num_threads(num_threads)  schedule(dynamic,3) reduction(*:res)
	for (int i = 0; i < kol; i++)
		res *= h[i];

	//delete[]h;
	//delete[]c;
	return res;
}