#include <iostream>
#include "Individual.h"
#include "Gt.h"
#include <stdlib.h>

#define INPUT_FILE "FT10.txt"

Individual::Individual():mFitness(0){

}

Individual::Individual(int machineNum,int jobNum):mFitness(0){
	mGene=vector<vector<int> >(machineNum,vector<int>(jobNum,-1));
}

void Individual::initGene(){
	Gt gt(INPUT_FILE);
	gt.execute();
	mGene=gt.convertAStoMatrix(gt.getASTable());
	mFitness=gt.getMakespan();
}

void Individual::fixGene(){
	Gt gt(INPUT_FILE);
	mGene=gt.fixMatrix(mGene);
	// Check Matrix
	for(int i=0;i<mGene.size();i++){
		for(int j=0;j<mGene.size();j++){
			if(mGene[i][j]==-1){
				cout<<"error!!!"<<endl;
				print();
				exit(-1);
			}
		}
	}
	//
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

int Individual::getJobNum(){
	return mGene[0].size();
}

int Individual::getMachineNum(){
	return mGene.size();
}

int Individual::getFitness(){
	return mFitness;
}

vector<int>& Individual::operator[](int n){
	return mGene[n];
}

bool Individual::operator<(Individual& obj){
	return this->mFitness<obj.getFitness();
}

bool Individual::operator>(Individual& obj){
	return this->mFitness>obj.getFitness();
}

bool Individual::less(Individual *l, Individual *r){
	return l->getFitness()<r->getFitness();
}

Individual::~Individual(){
	
}