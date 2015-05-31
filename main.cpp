#include <iostream>
#include <cstdlib>
#include "Ga.h"
#include "Gt.h"

#define POPULATION 50
#define MUTATION 1
#define GENERATION 100
#define CHILDNUM 2

using namespace std;

int main(int argc,char *argv[]){
	int i=1;
	int population=POPULATION;
	int mutation=MUTATION;
	int generation=GENERATION;
	int childnum=CHILDNUM;
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
			}
		}
		i++;
	}
	/*
	Ga ga;
	ga.setPopulation(population);
	ga.setGeneration(generation);
	ga.setMutation(mutation);
	ga.setChildNum(childnum);
	ga.execute();
	*/
	for(int i=0;i<10;i++){
		vector<vector<int> > matrix;
		Gt gt("FT6.txt");
		int m[6][6]={
			{0,3,2,5,1,4},
			{1,3,5,0,4,2},
			{5,0,3,1,2,4},
			{2,5,3,0,1,4},
			{1,4,2,3,5,0},
			{2,5,1,0,4,3}
		};
		for(int i=0;i<6;i++){
			vector<int> a;
			for(int j=0;j<6;j++){
				a.push_back(m[i][j]);
			}
			matrix.push_back(a);
		}
		matrix=gt.fixMatrix(matrix);
		cout<<"=========================="<<endl;
		for(int i=0;i<matrix.size();i++){
			for(int j=0;j<matrix[0].size();j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
}