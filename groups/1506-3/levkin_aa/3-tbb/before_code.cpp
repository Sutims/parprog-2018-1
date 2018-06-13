// before_code.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h" //������ ��� ������

#include <fstream>
#include <string>

#include <omp.h>
using namespace std;

void qsortBatcher(int* a, int size);
void qsortBatcher2(int* a, int size, int numThreads);
void qsortBatcher3(int* a, int size, int numThreads);

int _tmain(int argc, _TCHAR* argv[])
{
	//�������� �� ���������, ���� ������ �� ����� ������
	int n = 20;
	int sizeMass = 256;
	int numThreads = 4;
	string nameFile;

	if (argc >= 2)
	{
		n = (int)(stod(argv[1]));// = stoi(argv[1]);
		if (argc == 3)
			numThreads = (int)(stod(argv[2]));
	}

	for(int i=1;i<=n;i++)
	{
		nameFile =to_string((long long)i);
		FILE* fTestMass = fopen(("./tests/"+ nameFile).c_str(), "rb");
		FILE* fResMass = fopen(("./tests/"+ nameFile + ".ans").c_str(), "wb");

		//���������� ������� � ��� ������
		fread(&sizeMass, sizeof (sizeMass), 1, fTestMass);
		int *data=new int[sizeMass];
		fread(data, sizeof (*data), sizeMass, fTestMass);
		
		auto timeWork = omp_get_wtime();
		qsortBatcher3(data, sizeMass, numThreads);
		timeWork = omp_get_wtime() - timeWork;

		//���������� ��� ������ � ����(������ ������ ������ � ��� ������)
		fwrite(&sizeMass, sizeof(sizeMass), 1, fResMass);
		fwrite(&timeWork, sizeof(timeWork), 1, fResMass);
		fwrite(data, sizeof (*data), sizeMass, fResMass);

		delete []data;
		fclose(fTestMass);
		fclose(fResMass);
	}
	return 0;
	
}

