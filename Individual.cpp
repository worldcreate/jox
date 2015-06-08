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
	vector<vector<int> >buffer;
	buffer=gt.fixMatrix(mGene);
	// Check Matrix
	for(int i=0;i<buffer.size();i++){
		for(int j=0;j<buffer.size();j++){
			if(mGene[i][j]==-1){
				cout<<"error!!!"<<endl;
				print(buffer);
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

void Individual::print(vector<vector<int> > &vec){
	for(int i=0;i<vec.size();i++){
		for(int j=0;j<vec[0].size();j++){
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}
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

bool Individual::operator==(Individual& dst){
	bool ret=true;
	for(int i=0;i<mGene.size();i++){
		for(int j=0;j<mGene.size();j++){
			if(mGene[i][j]!=dst[i][j])
				ret=false;
		}
	}
	return ret;
}

bool Individual::operator!=(Individual& dst){
	return !(this->operator==(dst));
}

Individual::~Individual(){
	
}