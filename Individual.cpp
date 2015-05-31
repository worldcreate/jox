#include <iostream>
#include "Individual.h"
#include "Gt.h"

Individual::Individual():mFitness(0){

}

void Individual::initGene(){
	Gt gt("sample.txt");
	gt.execute();
	mGene=gt.convertAStoMatrix(gt.getASTable());
	mFitness=gt.getMakespan();
}

void Individual::print(){
	for(int i=0;i<mGene.size();i++){
		for(int j=0;j<mGene[0].size();j++){
			cout<<mGene[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"fitness="<<mFitness<<endl;
	cout<<endl;
}

void Individual::getJobNum(){
	return mGene[0].size();
}

vector<int>& operator[](int n){
	return mGene[n];
}

Individual::~Individual(){
	
}