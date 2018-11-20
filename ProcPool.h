#pragma once
#include <iostream>

using std::cout;
using std::endl;

class ProcPool
{
public:
	ProcPool();
	ProcPool(int nTotProcs);

	int getnFreeProcs();

	bool take_nProcs(int n);
	bool returnProcs(int n);

	void setFreeProcs(int n);
private:
	int nFreeProcs;
};