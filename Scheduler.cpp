#pragma once
#include "Scheduler.h"

Scheduler::Scheduler(int procs)
{
	nJobs = 0;
	nProcs = procs;
	mProcessorPool.setFreeProcs(procs);
	mRunningJobQueue.setpPool(&mProcessorPool);
}

void Scheduler::run()
{
	while (testTick(cin)) // Will run until both running and waiting queues are empty. Use tick() to run indefinitly
	{
	}
}

void Scheduler::runTest()
{
	ifstream input("testinput.txt", ifstream::in);
	
	while (testTick(input))
	{

	}
}

// Private
bool Scheduler::testTick(istream & rInputStream)
{
	static int tickNum = 1;
	cout << "Tick Number " << tickNum << endl;
	++tickNum;
	decrTimer(); // Decriments ticks for all acrive jobs
	if (!rInputStream.eof()) // Tries to get a new job if the istream is not at the end of the stream
	{
		Job newJob = getJob(rInputStream);

		if (newJob.getDesc() == "exit") // Checks for exit job
			return false;
		insertJob(newJob); // Adds job to WaitQueue
	}

	while (checkAvailability()) // Checks that the WaitQueue is not empty and that the minimum job in the queue
		// does not require too many processors
	{
		runJob(); // Deletes min job from WaitQueue and adds it to the RunningQueue
	}

	if (mJobWaitQueue.isEmpty() && mRunningJobQueue.isEmpty()) // Cehcks that running and waiting queues are empty
	{
		cout << "No Jobs waiting, and no Jobs running. Program exiting." << endl;
		return false;
	}

	return true;
}

bool Scheduler::tick()
{
	decrTimer(); // Decriments ticks for each running job
	Job newJob = getJob(); // Gets new job from the user
	
	if (newJob.getDesc() == "exit")
		return false;
	insertJob(newJob); // Adds job to WaitQueue

	while (checkAvailability()) // Checks that the WaitQueue is not empty, and that the min item of
		// the waitqueue does not require more processors than are available
	{
		runJob(); // Deletes min item of the waitQueue and adds it to the RunningQueue
	}

	return true;
}

Job Scheduler::getJob(istream & rInputStream)
{
	int jobTicks = 0, jobProcs = 0;
	string jobDesc = "NULL";
	getDescription(jobDesc, rInputStream); // Gets description from the istream

	if (jobDesc != "NULL")
	{
		jobProcs = getJobProcs(rInputStream); // Get processor and tick numbers
		jobTicks = getJobTicks(rInputStream);
	}

	Job newJob(nJobs, jobProcs, jobTicks, jobDesc);

	return newJob;
}

Job Scheduler::getJob()
{
	int jobTicks = 0, jobProcs = 0;
	string jobDesc = "NULL";
	getDescription(jobDesc); // Get description from the user

	if (jobDesc != "NULL")
	{
		jobProcs = getJobProcs(); // Get processor and tick numbers from the user
		jobTicks = getJobTicks();
	}

	Job newJob(nJobs, jobProcs, jobTicks, jobDesc);

	return newJob;
}


void Scheduler::getDescription(string & rDesc, istream & rinputStream)
{
	cout << "Please enter the description of this job: ";
	std::getline(rinputStream, rDesc);
	cout << endl;
}

void Scheduler::getDescription(string & rDesc)
{
	cout << "Please enter the description of this job: ";
	std::getline(cin, rDesc);
	cout << endl;
}

int Scheduler::getJobTicks(istream & rInputStream)
{
	int n = 0;
	string temp;
	while (n <= 0)
	{
		cout << "Please enter the number of ticks for this job ( ticks > 0): ";
		std::getline(rInputStream, temp);
		std::stringstream(temp) >> n;
	}
	cout << endl;

	return n;
}

int Scheduler::getJobTicks()
{
	int n = 0;
	string temp;
	while (n <= 0)
	{
		cout << "Please enter the number of ticks for this job ( ticks > 0): ";
		//cin >> n;
		std::getline(cin, temp);
		std::stringstream(temp) >> n;
	}
	cout << endl;

	return n;
}

int Scheduler::getJobProcs(istream & rInputStream)
{
	int n = 0;
	string temp;
	while (n <= 0 || n > nProcs)
	{
		cout << "Please enter the number of procs for this job ( 0 < procs <= " << nProcs << "): ";
		std::getline(rInputStream, temp);
		std::stringstream(temp) >> n;
	}
	cout << endl;

	return n;
}

int Scheduler::getJobProcs()
{
	int n = 0;
	string temp;
	while (n <= 0 || n > nProcs)
	{
		cout << "Please enter the number of procs for this job ( 0 < procs <= " << nProcs << "): ";
		std::getline(cin, temp);
		std::stringstream(temp) >> n;
	}
	cout << endl;

	return n;
}

void Scheduler::insertJob(Job & rJob)
{
	if (rJob.getDesc() != "NULL")
	{
		mJobWaitQueue.enqueueJob(rJob);
		++nJobs;
	}
}

bool Scheduler::checkAvailability()
{
	// Checks that the WaitQueue is not empty and that the number of processors required by the min job does
	// not exceed the number of available processors
	return !mJobWaitQueue.isEmpty() && mJobWaitQueue.getMinJobProcs() <= mProcessorPool.getnFreeProcs();
}

void Scheduler::decrTimer()
{
	mRunningJobQueue.decrementTimer();
}

void Scheduler::runJob()
{
	Job j;

	if (!mJobWaitQueue.isEmpty())
	{
		mJobWaitQueue.deleteMinJob(j); // Delete the min item from the WaitingQueue and put it on the
		mRunningJobQueue.addJob(j);		// runningQueue
	}
}
