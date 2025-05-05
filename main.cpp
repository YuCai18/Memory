#include<stdlib.h>
#include"Alloctor.h"

int main()
{
	////1.
	//char* data1 = new char[128];
	//delete[] data1;
	////2.
	//char* data2 = new char;
	//delete data2;
	////3.
	//char* data3 = new char[64];
	//delete[] data3;

	char* data[120];
	for (size_t i = 0;i<120;++i)
	{
		data[i] = new char[rand()%1024+100];
	}

	for (size_t i = 0;i < 120;++i)
	{
		delete[] data[i];
	}

	return 0;
}