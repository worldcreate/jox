#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <vector>

using namespace std;

class Individual{
public:
	Individual();
	Individual(int,int);
	void initGene();
	void fixGene();
	void print();
	int getJobNum();
	int getMachineNum();
	vector<int>& operator[](int);
	bool operator<(const Individual& );
	~Individual();
private:
	vector<vector<int> > mGene;
	int mFitness;
};

#endif