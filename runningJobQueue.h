#pragma once
#include "Job.h"
#include "ProcPool.h"
#include "processor.h"
#include <list>
#include <iostream>

using std::list;
using std::cout;
using std::endl;

class RunningJobQueue
{
public:
	RunningJobQueue();
	RunningJobQueue(ProcPool * pPool);
	~RunningJobQueue();

	void decrementTimer();
	bool addJob(Job & rJob);
	void setpPool(ProcPool *pP);

	bool isEmpty();

private:
	list<Job> mJobList;
	ProcPool * mpProcPool;

	void endJob(list<Job>::iterator & rIt);
	void returnProcs(int nProcs);
};