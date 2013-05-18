#include <iostream>
#include "rrr.h"
#include "typedef.h"
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{

	int m=atoi(argv[1]);
	u64 n= 1UL<<m;
	cout<<m<<"\t"<<n<<"\t";
	//int n=1u<<30;
	//n=200;
	u64* bitvec=new u64[n/D+1];
	u32* rank=new u32[n];
	memset(rank,0,sizeof(u32)*n);
	memset(bitvec,0,sizeof(u64)*(n/D+1));
	for(u64 i=0;i<n;i++)
	{
		if(i%10==0)
		{
			bitvec[i/D]|=(1UL<<(i%D));
			rank[i]=rank[i-1]+1;
		}
		else
			rank[i]=rank[i-1];
	}

	//u64* bitvec=new u64[n/64+1];
	//for(int i=0;i<n;i++)
	//{
	//	bitvec[i]=i+15;
	//}

	ofstream fout;
	fout.open("rrr.bin",ios::binary);
	rrr r(n,bitvec);

	if(!r.write(fout))
	{
		cout<<"error to write"<<endl;
		return -1;
	}

	u32 ressize=fout.tellp();
	cout<<ressize<<"\t"<<ressize*8.0/n<<"\t";
	fout.close();


	time_t start=time(NULL);

	for(u64 i=1;i<n;i++)
	{
		int v1 = (bitvec[i/D] & (1UL<<(i%D)))?1:0;
		int v2 = r.get(i);
		if(v1!=v2)
		{
			cout << i <<"\terror to get"<<endl;
			return -1;
		}
	}
	time_t end=time(NULL);
	double seconds = difftime(end,start);
	cout<<seconds<<"\t"<<seconds/n*1000000<<"\t";

	start=time(NULL);
	for(u64 i=0;i<n;i++)
	{
		if (rank[i]!=r.rank(i))
		{
			cout<<"\t rank erro "<<i<<endl;
			return -1;
		}
	}
	end=time(NULL);

	seconds=difftime(end,start);
	cout<<seconds<<"\t"<<seconds/n*1000000<<endl;

	delete[] bitvec;
	delete[] rank;
	return 0;
}
