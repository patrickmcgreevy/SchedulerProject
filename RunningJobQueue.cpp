#pragma once
#include "runningJobQueue.h"

RunningJobQueue::RunningJobQueue() 
{
	mpProcPool = nullptr;
}
RunningJobQueue::RunningJobQueue(ProcPool * pPool)
{
	mpProcPool = pPool;
}

RunningJobQueue::~RunningJobQueue()
{
	mpProcPool = nullptr;
}

void RunningJobQueue::decrementTimer() // Decrements all the ticks of jobs and ends the job if it is expired
{
	int numProcs = 0;
	for (list<Job>::iterator it = mJobList.begin(); it != mJobList.end();)
	{
		if (it->decrTics(numProcs))
		{
			endJob(it);
			returnProcs(numProcs);
		}
		else
		{
			++it;
		}
	}
}

bool RunningJobQueue::addJob(Job & rJob) // Adds a job to the running queue
{
	cout << "Job " << rJob.getId() << " started." << endl;
	mpProcPool->take_nProcs(rJob.getnProcs());
	mJobList.push_back(rJob);
	return true;
}

bool RunningJobQueue::isEmpty()
{
	return mJobList.empty();
}


// Private
void RunningJobQueue::endJob(list<Job>::iterator & rIt) // Removes expired job from the running queue
{
	cout << "Job " << rIt->getId() << " done." << endl;
	rIt = mJobList.erase(rIt);
}

void RunningJobQueue::returnProcs(int nProcs)
{
	mpProcPool->returnProcs(nProcs);
}

void RunningJobQueue::setpPool(ProcPool *pP)
{
	mpProcPool = pP;
}