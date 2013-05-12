#include <iostream>
#include "rrr.h"
#include "typedef.h"
#include <cstdlib>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
//	int n=100000000;

	int m=atoi(argv[1]);
	int n= 1U<<m;
	cout<<m<<n<<endl;
	//int n=1u<<30;
	u64* bitvec=new u64[n/D+1];
	memset(bitvec,0,sizeof(u64)*(n/D+1));
	for(int i=0;i<n;i++)
	{
		if(i%10)
		{
			bitvec[i/D]|=(1UL<<(i%D));
		}
	}

	//u64* bitvec=new u64[n/64+1];
	//for(int i=0;i<n;i++)
	//{
	//	bitvec[i]=i+15;
	//}

	ofstream fout;
	fout.open("rrr.bin",ios::binary);
	rrr r(n,bitvec);

	r.write(fout);
	fout.close();
	delete[] bitvec;
	return 0;
}
