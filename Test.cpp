#include "Test.h"
#include "Ga.h"
#include "Gt.h"
#include "Individual.h"
#include "Util.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#define N 10

Test::Test(){

}

void Test::test(){
	int mat[N][N]={
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9},
		{0,1,2,3,4,5,6,7,8,9}
	};
	Individual individual(N,N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			individual[i][j]=mat[i][j];
		}
	}
	individual.fixGene();
	individual.print();
}
