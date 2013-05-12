#include "rrr.h"
#include <string.h>
u64 popcount(u64 x)
{
    u64 r;

    r = x;
    r = ((r & 0xaaaaaaaaaaaaaaaa)>>1) + (r & 0x5555555555555555);
    r = ((r & 0xcccccccccccccccc)>>2) + (r & 0x3333333333333333);
    r = ((r>>4) + r) & 0x0f0f0f0f0f0f0f0f;

    r *= 0x0101010101010101;
    r >>= 64-8;

    return r;
}

int cal(int n, int m)
{
    int i, a, b, p;
    if(n<m){i=m;m=n;n=i;}
    p=1;
    a=n-m<m?n-m:m;
    b=n-m>m?n-m:m;
    for(i=1; i<=a; i++)
        p+=p*b/i;
    return p;
}

int blog(i64 x) //求整数x的对数
{
    if(x==0)
        return 0;
    int l;
    l = -1;
    while (x>0) {
        x>>=1;
        l++;
    }
    return l;
}
void rrr::makecmap()
{
	u64 total=1UL<<u;
	this->cmap=new int[total];
	int* sum=new int[u+1];
	memset(sum,0,sizeof(int)*(u+1));
	for(u64 i=1;i<total;i++)
	{
		this->cmap[i]=sum[popcount(i)]++;
	}
	delete[] sum;
}


void rrr::initE()
{
	int* kind=new int[u+1];
	kind[0]=1;
	for(int i=1;i<=u;i++)
	{
		kind[i]=kind[i-1]+cal(u,i);
	}
	for(int i=0;i<(1U<<u);i++)
	{
		int c=popcount(i);
		int o=cmap[i];
		E[kind[c-1]+o]=(u16)i;
	}
	delete[] kind;
}

void rrr::makeblogmap()
{
	blogmap=new int[u+1];
	memset(blogmap,0,sizeof(int)*(u+1));
	blogmap[u]=0;
	for(int i=1;i<u;i++)
	{
		blogmap[i]=blog(cal(u,i))+1;
	}
}

void rrr::initRS(int n,u64* bitvec)
{
	int width=4;

	int k=0;
	u64 count=0;
	u64 offset=0;

	u32* sumR_temp=new u32[(n/u+1)/sample+1];
	u32* posS_temp=new u32[(n/u+1)/sample+1];
	memset(sumR_temp,0,sizeof(u32)*((n/u+1)/sample+1));
	memset(posS_temp,0,sizeof(u32)*((n/u+1)/sample+1));

	for(int index=0;index<n;index+=u)
	{
		int i=index/D;
		int j=index%D;
		int hole=D-j;
		u64 v;
		if(hole >= u)
		{
			v = (bitvec[i] >> j)&((0UL-1) >> (D-u));

		}
		else
		{
			u64 v_low = (bitvec[i] >> j);
			u64 v_high;
			if((i+1)>(n/D))
				v_high=0;
			else
				v_high = (bitvec[i+1] & ((0-1UL)>>(D-u+hole))) << hole;
			v = v_low + v_high;

		}
		int c = popcount(v);
		int o = cmap[v];
		if(c==0 || c==15)
		{
			R.setbits(width,c);
		}
		else
		{
			R.setbits(width,c);
			S.setbits(blogmap[c],o);
		}

		k++;
		count += c;
		offset += S.getsize();
		if(k%sample==0)
		{
			sumR_temp[k/sample]=count;
			posS_temp[k/sample]=offset;
		}
	}
	sumR = new compactIntArray(sumR_temp,(n/u+1)/sample,count);
	posS = new compactIntArray(posS_temp,(n/u+1)/sample,offset);
}
rrr::rrr()
{
	size=0;
	sample==0;
	sumR=NULL;
	posS=NULL;
	cmap=NULL;
	blogmap=NULL;
}

rrr::rrr(int n, u64* bitvec)
{
	this->size=n;
	this->sample=150;
	this->makecmap();
	this->makeblogmap();
	this->initE();
	this->initRS(n, bitvec);
}

rrr::~rrr()
{
	size=0;
	sample=0;
	delete sumR;
	delete posS;
	delete cmap;
	delete blogmap;
}

bool rrr::write(ofstream& fout)
{
	fout.write((char*)&size, sizeof(int));
	fout.write((char*)&sample, sizeof(int));
	fout.write((char*)E, sizeof(u16)*(1U<<u));
	R.write(fout);
	S.write(fout);
	sumR->write(fout);
	posS->write(fout);

}
