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
	Gt gt("FT6.txt");
	int m[6][6]={
		{0,3,2,5,1,4},
		{1,3,5,0,4,2},
		{2,0,1,4,3,5},
		{2,5,3,0,1,4},
		{1,4,2,3,5,0},
		{2,5,1,0,4,3}
	};
	vector<vector<int> > vec;
	vec.resize(6);
	for(int i=0;i<6;i++){
		vec[i].resize(6);
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			vec[i][j]=m[i][j];
		}
	}
	vec=gt.fixMatrix(vec);

	for(int i=0;i<vec.size();i++){
		for(int j=0;j<vec[0].size();j++){
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}
}