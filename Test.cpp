#include "Test.h"
#include "Ga.h"
#include "Gt.h"
#include "Individual.h"
#include "Util.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

#define N 10

Test::Test(){

}

void Test::test(){
	vector<vector<int> > vec=vector<vector<int> >(N,vector<int>(N,0));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			vec[i][j]=j;
		}
	}
	Gt gt("FT10.txt");
	print(vec);
	vec=gt.fixMatrix(vec);
	check(vec);
}

void Test::print(const vector<vector<int> > &vec){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void Test::check(const vector<vector<int> > &vec){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(vec[i][j]==-1){
				cout<<"error"<<endl;
				print(vec);
				exit(-1);
			}
		}
	}
}

void Test::func(vector<vector<int> > vec,int i,int j,int k){
	if(i>=N || j>=N || k>=N)
		return;
	int t=vec[i][j];
	vec[i][j]=vec[i][k];
	vec[i][k]=t;
	print(vec);
	Gt gt("FT10.txt");
	vec=gt.fixMatrix(vec);
	cout<<"makespan="<<gt.getMakespan()<<endl;
	print(vec);
	check(vec);

	func(vec,i+1,j,k);
	func(vec,i,j+1,k);
	func(vec,i,j,k+1);
}