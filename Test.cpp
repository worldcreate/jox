#include "Test.h"
#include "Ga.h"
#include "Gt.h"
#include "Individual.h"
#include "Util.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>

using namespace std;

#define N 1000000

Test::Test(){

}

void Test::test(){
	int t=INT_MAX;
	double sum=0;
	for(int i=0;i<N;i++){
		Individual individual;
		individual.initGene();
		//individual.print();
		if(t>individual.getFitness()){
			t=individual.getFitness();
		}
		sum+=individual.getFitness();
	}
	cout<<"min="<<t<<endl;
	cout<<"ave="<<sum/N<<endl;
}
