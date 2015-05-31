#include "Ga.h"
#include "Individual.h"

Ga::Ga(){

}

void Ga::setPopulation(int x){
	mPopulationSize=x;
}

void Ga::setMutation(int x){
	mMutation=x;
}

void Ga::setGeneration(int x){
	mGeneration=x;
}

void Ga::setChildNum(int x){
	mChildNum=x;
}

void Ga::execute(){
	int g=0;
	initialize();
	/*
	while(g<mGeneration){
		crossOver();
		mutation();
		g++;
	}
	*/
	printPopulation();
}

void Ga::printPopulation(){
	for(int i=0;i<mPopulation.size();i++){
		mPopulation[i]->print();
	}
}

void Ga::initialize(){
	for(int i=0;i<mPopulationSize;i++){
		Individual* i=new Individual();
		i->initGene();
		mPopulation.push_back(i);
	}
}

void Ga::crossOver(){
	random_shuffle(mPopulation.begin(),mPopulation.end());

}

void jox(vector<Individual*> &family){
	for(int i=0;i<mChildNum;i+=2){
		vector<int> saveJob;
		for(int i=0;i<family[0]->getJobNum();i++){
			int r=Util::getRand(0,1);
			if(r==1)
				continue;
			
		}
	}
}

void Ga::mutation(){}

Ga::~Ga(){
	for(int i=0;i<mPopulation.size();i++){
		delete(mPopulation[i]);
	}
}