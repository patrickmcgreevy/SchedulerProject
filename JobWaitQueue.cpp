#pragma once
#include "JobWaitQ.h"

JobWaitQueue::JobWaitQueue()
{

}

JobWaitQueue::~JobWaitQueue()
{
	mJobQueue.empty();
}

bool JobWaitQueue::enqueueJob(Job & rJ) // Adds job to the min heap
{
	mJobQueue.push(rJ);

	return true;
}

bool JobWaitQueue::deleteMinJob(Job & returnJob) // Return by reference
{
	returnJob = mJobQueue.top(); // Passes min job

	mJobQueue.pop();
	return true;
}

int JobWaitQueue::getMinJobProcs() // Checks how many processors the job requires
{
	return mJobQueue.top().getnProcs();
}

bool JobWaitQueue::isEmpty()
{
	return mJobQueue.empty();
}