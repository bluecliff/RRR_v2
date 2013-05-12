#include "bitvector.h"
#include <cstdlib>

bitvec_t::bitvec_t()
{
    this->bit_size=0;
    bitvec.push_back(0);
}

void bitvec_t::setbits(int k, u64 v)
{
    int i = bit_size/D;
    int j = bit_size%D;

    int hole= D - j;

    if(hole >k)
    {
        bitvec[i] |= (v << j);
        bit_size+=k;
    }
    else if(hole == k)
    {
        bitvec[i] |= (v << j);
        bit_size+=k;
        bitvec.push_back(0);
    }
    else
    {
        bitvec.push_back(0);
        bitvec[i] |= (v << j);
        bitvec[i+1] |= (v >> hole);
        bit_size+=k;
    }
}

u64 bitvec_t::getbits(u64 index,int k)
{
    if(index > bit_size)
    {
        exit(-1);
    }
    int i = index/D;
    int j = index%D;

    int hole= D-j;

    if(hole >= k)
    {
        u64 res = bitvec[i] >> j;
        res &= ((0UL-1) >> (D-k));
        return res;
    }
    else
    {
        u64 res_low = bitvec[i] >> j;
        u64 res_high = bitvec[i+1] << hole;
        res_high &= ((0UL-1)>>(D-k));

        return res_low+res_high;
    }
}

int bitvec_t::getsize()
{
    return this->bit_size;
}

bool bitvec_t::write(ofstream& fout)
{
	if(fout.is_open())
	{
		fout.write((char*)&bit_size,sizeof(u64));
		for(size_t i=0;i<bitvec.size();i++)
		{
			fout.write((char*)&bitvec[i],sizeof(u64));
		}
		if(fout.bad() || fout.fail())
			return false;
		else
			return true;
	}
	else
	{
		return false;
	}
}
