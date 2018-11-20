#pragma once
#include <string>
#include "processor.h"

using std::string;

class Job
{
public:
	Job();
	Job(int jId, int jProcs, int jTicks, const string & jDesc);
	Job(const Job & rOtherJob);
	~Job();

	bool decrTics(int & rNumProcs); // Returns true if the job is expired, else false. Returns by reference nProcs

	int getId() const;
	int getnProcs() const;
	int getnTicks() const;
	string& getDesc();
	bool operator>(const Job & rhs);
	bool operator<(const Job & rhs);

	friend bool operator>(const Job &lhs, const Job&rhs);

private:
	int id, nProcs, nTicks;
	string jobDescription;
};

