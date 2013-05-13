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
	u64 n= 1UL<<m;
	cout<<m<<"\t"<<n<<endl;
	//int n=1u<<30;
	//n=200;
	u64* bitvec=new u64[n/D+1];
	memset(bitvec,0,sizeof(u64)*(n/D+1));
	for(u64 i=0;i<n;i++)
	{
		if(i%10==0)
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

	cout<<r.rank(0);
	for(u64 i=1;i<n;i++)
	{
		if(i%10 == (r.rank(i)-r.rank(i-1)))
			cout<<i<<endl;
		//cout<<r.rank(i)<<endl;
	}

	delete[] bitvec;
	return 0;
}
