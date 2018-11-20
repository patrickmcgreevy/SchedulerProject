#pragma once
#include "Job.h"
#include <queue>
#include <functional>

using std::priority_queue;

class JobWaitQueue
{
public:
	JobWaitQueue();
	~JobWaitQueue();

	bool enqueueJob(Job & rJ);
	bool deleteMinJob(Job & returnJob); // Return by reference
	int getMinJobProcs();
	bool isEmpty();
private:
	priority_queue<Job, std::vector<Job>, std::greater<Job> > mJobQueue; // Sorts with shortest job at top
};