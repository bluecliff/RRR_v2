#ifndef RRR_H
#define RRR_H_

#include "typedef.h"
#include "bitvector.h"
#include "compactIntArray.h"
#include "fstream"
#define u 15

class rrr
{
public:
	rrr();
	rrr(int n, u64* bitvec);
	~rrr();
	void initE();
	void initRS(int n,u64* bitvec);
	int get(int index);
	u32 rank(int index);
	void makecmap();
	void makeblogmap();
	void makecalmap();
	bool write(ofstream& fout);

private:
	int size;
	int sample;
	u16 E[1U<<u];
	bitvec_t R;
	bitvec_t S;

	compactIntArray* sumR;
	compactIntArray* posS;

	int* cmap;
	int* blogmap;
	int* calmap;
};
#endif
