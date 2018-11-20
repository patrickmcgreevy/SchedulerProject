#pragma once
#include "ProcPool.h"

ProcPool::ProcPool()
{
	nFreeProcs = 0;
}

ProcPool::ProcPool(int nTotProcs)
{
	nFreeProcs = nTotProcs;
}

int ProcPool::getnFreeProcs()
{
	return nFreeProcs;
}

bool ProcPool::take_nProcs(int n) // Ensures that there are enough processors for the Job
{
	if (nFreeProcs >= n)
	{
		cout << n << " processors taken." << endl;
		nFreeProcs -= n;
		return true;
	}
	return false;
}

bool ProcPool::returnProcs(int n) // Returns processors to the pool
{
	cout << n << " processors returned." << endl;
	nFreeProcs += n;
	return true;
}

void ProcPool::setFreeProcs(int n)
{
	nFreeProcs = n;
}