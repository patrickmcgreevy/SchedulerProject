#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "Job.h"
#include "JobWaitQ.h"
#include "ProcPool.h"
#include "runningJobQueue.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;

class Scheduler
{
public:
	Scheduler(int nProcs);

	void run();
	void runTest();

private:
	ProcPool mProcessorPool;
	JobWaitQueue mJobWaitQueue;
	RunningJobQueue mRunningJobQueue;
	int nJobs;
	int nProcs;

	bool tick();
	bool testTick(istream & rInputStream);

	Job getJob();
	Job getJob(istream & rInputStream);
	void getDescription(string & rDesc);
	void getDescription(string & rDesc, istream & rinputStream);
	int getJobTicks();
	int getJobTicks(istream & rinputStream);
	int getJobProcs();
	int getJobProcs(istream & rinputStream);
	void insertJob(Job & rJob);
	bool checkAvailability();
	void decrTimer();
	void runJob();
};