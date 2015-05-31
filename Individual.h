#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <vector>

using namespace std;

class Individual{
public:
	Individual();
	void initGene();
	void print();
	int getJobNum();
	vector<int>& operator[](int);
	~Individual();
private:
	vector<vector<int> > mGene;
	int mFitness;
};

#endif