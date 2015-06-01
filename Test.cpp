#include "Test.h"
#include "Ga.h"
#include "Individual.h"
#include "Util.h"
#include <iostream>

using namespace std;

Test::Test(){

}

void Test::test(){
	for(int i=0;i<1000;i++){

		Ga ga;
		ga.setChildNum(2);
		Individual *parent1=new Individual();
		Individual *parent2=new Individual();
		parent1->initGene();
		parent2->initGene();

		cout<<"init"<<endl;
		parent1->print();
		parent2->print();

		vector<Individual*> family;
		family.push_back(parent1);
		family.push_back(parent2);

		
		cout<<"===================="<<endl;
		ga.jox(family);
		for(int i=0;i<2;i++){
			family[i]->print();
		}
	}
}