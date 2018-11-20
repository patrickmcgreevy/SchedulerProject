#pragma once
#include "Job.h"

Job::Job()
{
	id = 0;
	nProcs = 0;
	nTicks = 0;
	jobDescription = "NULL";
}

Job::Job(int jId, int jProcs, int jTicks, const string & jDesc)
{
	id = jId;
	nProcs = jProcs;
	nTicks = jTicks;
	jobDescription = jDesc;
}

Job::Job(const Job & rOtherJob)
{
	id = rOtherJob.id;
	nProcs = rOtherJob.nProcs;
	nTicks = rOtherJob.nTicks;
	jobDescription = rOtherJob.jobDescription;
}

Job::~Job()
{

}

int Job::getId() const
{
	return id;
}

int Job::getnProcs() const
{
	return nProcs;
}

int Job::getnTicks() const
{
	return nTicks;
}

string& Job::getDesc()
{
	return jobDescription;
}

bool Job::decrTics(int & rNumProcs) // true if Job is expired
{
	rNumProcs = nProcs;
	--nTicks; // Counts down number of remaining ticks

	return !nTicks;
}

bool Job::operator>(const Job & rhs)
{
	return (this->getnTicks()) * (this->getnProcs()) > rhs.getnTicks() * rhs.getnProcs();
}

bool Job::operator<(const Job & rhs)
{
	return (this->getnTicks()) * (this->getnProcs()) < rhs.getnTicks() * rhs.getnProcs();
}

bool operator>(const Job &lhs, const Job&rhs)
{
	return (lhs.getnTicks()) * (lhs.getnProcs()) > rhs.getnTicks() * rhs.getnProcs();
}