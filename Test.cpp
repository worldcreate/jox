#include "Test.h"
#include "Ga.h"
#include "Gt.h"
#include "Individual.h"
#include "Util.h"
#include <iostream>

using namespace std;

Test::Test(){

}

void Test::test(){
	Individual *parent1=new Individual();
	Individual *parent2=new Individual();
	parent1->initGene();
	parent2->initGene();

	parent1->print();
	parent2->print();

	cout<<"============================"<<endl;

	vector<Individual*> family;
	family.push_back(parent1);
	family.push_back(parent2);
	Ga ga;
	ga.setChildNum(2);
	ga.jox(family);

	for(int i=0;i<family.size();i++){
		family[i]->print();
	}
}