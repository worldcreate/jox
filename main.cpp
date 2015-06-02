#include <iostream>
#include <cstdlib>
#include "Ga.h"
#include "Gt.h"
#include "Test.h"


#define POPULATION 50
#define MUTATION 1
#define GENERATION 100
#define CHILDNUM 2
#define TRIAL 50

using namespace std;

int main(int argc,char *argv[]){
	int i=1;
	int population=POPULATION;
	int mutation=MUTATION;
	int generation=GENERATION;
	int childnum=CHILDNUM;
	int trial=TRIAL;
	while(argc>i){
		if(argv[i][0]=='-'){
			const char *arg=&argv[i][2];
			switch(argv[i][1]){
				case 'g':
					generation=atoi(arg);
				break;
				case 'p':
					population=atoi(arg);
				break;
				case 'm':
					mutation=atoi(arg);
				break;
				case 'c':
					childnum=atoi(arg);
				break;
				case 't':
					trial=atoi(arg);
				break;
			}
		}
		i++;
	}
	for(int i=0;i<TRIAL;i++){
		Ga ga;
		ga.setPopulation(population);
		ga.setGeneration(generation);
		ga.setMutation(mutation);
		ga.setChildNum(childnum);
		ga.execute();
	}
}