#ifndef _GA_H_
#define _GA_H_

#include <vector>

using namespace std;

class Individual;

class Ga{
public:
	Ga();
	void setPopulation(int);
	void setGeneration(int);
	void setMutation(int);
	void setChildNum(int);
	void printPopulation();
	void execute();
	~Ga();
private:
	void initialize();
	void crossOver();
	void jox(vector<Individual*>&);
	void mutation();
	int mPopulationSize;
	int mMutation;
	int mGeneration;
	int mChildNum;
	vector<Individual*> mPopulation;
};

#endif