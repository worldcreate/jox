#include <iostream>
#include <limits.h>
#include <stdio.h>
#include "Gt.h"
#include "Util.h"
#include "FileReader.h"

#ifndef NULL
#define NULL 0
#endif

using namespace std;

FileReader* Gt::fr=NULL;

Gt::Gt():mFix(false){
}

Gt::Gt(const char* filename):mFix(false){
	if(fr==NULL)
		fr=new FileReader(filename);
	Table table=fr->getTable();
	setTable(table);
}

/* setTable(Table &)							 */
/* JSPテーブルの設定							 */
/* Pair<int,int>の二次元配列(vector)を引数		 */
/* とする										 */
/* vector[job][order]とし、pair<machine,time>	 */
/* とする										 */
void Gt::setTable(Table &table){
	mTable=table;
	mJobNum=table.size();
	mMachineNum=table[0].size();
}

/* execute()									 */
/* 設定されたテーブルを元にAS(Active 			 */
/* Schedule)を作り出す							 */
void Gt::execute(){
	// step1
	vector<vector<JobPair> > firstIndex(mMachineNum,vector<JobPair>(mJobNum));
	for(int j=0;j<mJobNum;j++){
		JobPair jp=mTable[j][0];
		jp.endTime=jp.time;
		firstIndex[jp.machine][j]=jp;
	}
	mCreateTable=firstIndex;
	//int index=0;
	pair<int,int> T;
	T.first=0;
	T.second=-1;
	while(true){
		// step2
		int machine=0;
		machine=getMinTimeOverT(T);
		#ifdef DEBUG
			cout<<endl;
			cout<<"========================================"<<endl;
			cout<<"machine="<<machine<<endl;
			cout<<"T="<<T.first<<endl;
		#endif
		#ifdef DEBUG
			for(int i=0;i<mCreateTable.size();i++){
				for(int j=0;j<mCreateTable[0].size();j++){
					if(mCreateTable[i][j].isCheck()){
						cout<<"[";
					}
					cout<<mCreateTable[i][j].endTime<<"("<<mCreateTable[i][j].time<<")"<<" ";
					if(mCreateTable[i][j].isCheck()){
						printf("\033[1D");
						cout<<"] ";
					}
				}
				cout<<endl;
			}
			cout<<endl;
		#endif
		if(machine==-1)
			break;
		// step3
		//if(checkConflict(index,machine,T)){
			// step4
			pair<int,int> TT=T;
			fixConflict(machine,TT);
			setNextJobpair(machine,TT);
			
		//}else{
			// step5
		//	setNextJobpair(index,machine,T);
		//}
		//addNextIndexTable(index);
		//index++;

	}
}

/* getMinTimeOverT(const vector<vector<int>>&,int*)	 */
/* ASの生成テーブルを引数とし、Tよりは大きく、最小の */
/* T'を取得する										 */
/* 返り値としては、取得したT'のmachineを返す		 */
int Gt::getMinTimeOverT(pair<int,int> &T){
	/* TODO 修正する必要あり？ */
	pair<int,int> tempT;
	tempT.first=INT_MAX;
	tempT.second=-1;
	int machine=-1;
	for(int m=0;m<mMachineNum;m++){
		for(int j=0;j<mJobNum;j++){
			if(tempT.first<mCreateTable[m][j].endTime)
				continue;
			if(T.first>mCreateTable[m][j].endTime)
				continue;
			if(mCreateTable[m][j].isCheck())
				continue;
			tempT.first=mCreateTable[m][j].endTime;
			tempT.second=j;
			machine=m;
		}
	}
	T=tempT;

	return machine;
}


/* fixConflict(int,int,int)							 */
/* コンフリクトを起こしていた場合、修正する			 */
void Gt::fixConflict(int machine,pair<int,int> &T){
	vector<JobPair> *jobTable=&mCreateTable[machine];
	vector<JobPair*> c;
	vector<JobPair*> sameT;
	vector<JobPair*> differT;
	// 同じTをsameTに代入
	for(int i=0;i<jobTable->size();i++){
		if((*jobTable)[i].isCheck())
			continue;
		JobPair *jp=&(*jobTable)[i];
		if(T.first==jp->endTime){
			sameT.push_back(jp);
		}else if(T.first<jp->endTime){
			differT.push_back(jp);
		}
	}

	// それぞれのsameTに対してコンフリクトを起こしているかを確認
	for(int j=0;j<differT.size();j++){
		if(differT[j]->endTime-
			differT[j]->time <T.first){
			c.push_back(differT[j]);
		}
	}
	c.insert(c.end(),sameT.begin(),sameT.end());


	int r=-1;
	if(!mFix){
		r=Util::getRand(0,c.size()-1);

	}else{
		/* TODO */
		/* matrixの中から未処理で先頭のものを一つとってきて、
		コンフリクトの中にあるか調べる。
		あった場合、それを選択して、なかった場合、コンフリクトの中にあるものを
		ランダムで選択し、matrixの順序を入れ替える。
		*/
		JobPair jp=getFirstNotCheckJobPairFromMatrix(machine);
		bool find=false;
		for(int i=0;i<c.size();i++){
			if(c[i]->jobIndex!=jp.jobIndex)
				continue;
			#ifdef DEBUG
				cout<<"find!"<<endl;
			#endif
			r=i;
			find=true;
			break;
		}
		if(!find){
			#ifdef DEBUG
				cout<<"not find!"<<endl;
			#endif
			r=Util::getRand(0,c.size()-1);
			changeOrderJobPairMatrix(machine,c[r]->jobIndex,jp.jobIndex);
		}
	}
	// スケジュール済みの中から最大のTを探す
	int scheduledT=0;
	for(int j=0;j<mJobNum;j++){
		if(!mCreateTable[machine][j].isCheck())
			continue;
		if(scheduledT<(*jobTable)[j].endTime)
			scheduledT=(*jobTable)[j].endTime;
	}
	int beforeT=0;
	int prevMachine=-1;
	int prevJobIndex=-1;
	#ifdef DEBUG
		cout<<"c[r]->jobIndex="<<c[r]->jobIndex<<endl;
		cout<<"(*jobTable)[c[r]->jobIndex].prev="<<(*jobTable)[c[r]->jobIndex].prev<<endl;
	#endif
	// 選択されたjobの前の完了時間を取得
	if((*jobTable)[c[r]->jobIndex].prev!=-1){
		prevJobIndex=c[r]->jobIndex;
		prevMachine=(*jobTable)[c[r]->jobIndex].prev;
		beforeT=mCreateTable[prevMachine][prevJobIndex].endTime;
	}
	//
	#ifdef DEBUG
		cout<<"beforeMachine="<<prevMachine<<endl;
		cout<<"beforeJobIndex="<<prevJobIndex<<endl;
		cout<<"beforeT="<<beforeT<<endl;
		cout<<"scheduledT="<<scheduledT<<endl;
	#endif
	T.first=max(beforeT,scheduledT)+(*jobTable)[c[r]->jobIndex].time;
	T.second=c[r]->jobIndex;
	#ifdef DEBUG
		cout<<"conflict size ="<<c.size()<<endl;
		cout<<"r="<<r<<endl;
		for(int ci=0;ci<c.size();ci++){
			cout<<c[ci]->jobIndex<<" ";
		}
		cout<<endl;
		cout<<"c[r].second="<<c[r]->jobIndex<<endl;
	#endif
	#ifdef DEBUG
		cout<<"T.first="<<T.first<<endl;
	#endif
	(*jobTable)[c[r]->jobIndex].endTime=T.first;
	for(int j=0;j<c.size();j++){
		if(j==r)
			continue;
		int prevT=0;
		int TT=0;
		int prevJobIndex=c[j]->jobIndex;
		int prevMachine=(*jobTable)[prevJobIndex].prev;

		if(prevMachine!=-1){
			prevT=mCreateTable[prevMachine][prevJobIndex].endTime;
		}
		TT=max(prevT,T.first);
		(*jobTable)[c[j]->jobIndex].endTime=
			mCreateTable[machine][c[j]->jobIndex].time+TT;
	}
}

/* setNextJobpair(int,int,int)							 */
/* 作業iの技術的順序により、次に割り当てられるJobPair	 */
/* をASに記入する										 */
void Gt::setNextJobpair(int machine,pair<int,int> T){
	int jobIndex=T.second;
	mCreateTable[machine][jobIndex].check();
	if(mFix)
		findJobpairByMachineAndJobFromMatrix(machine,jobIndex).check();
	
	int emptyTime=0;
	int nextMachine=mCreateTable[machine][jobIndex].next;
	if(nextMachine==-1)
		return;
	vector<JobPair> *nextJobTable=&mCreateTable[nextMachine];
	
	for(int j=0;j<mJobNum;j++){
		if(!(*nextJobTable)[j].isCheck())
			continue;
		if(emptyTime<(*nextJobTable)[j].endTime){
			emptyTime=(*nextJobTable)[j].endTime;
		}
	}
	int Ti=mCreateTable[machine][T.second].endTime;
	int Tk=emptyTime;
	int TT=max(Ti,Tk);
	#ifdef DEBUG
		cout<<"emptyTime="<<emptyTime<<":TT="<<TT<<endl;
		cout<<"nextMachine="<<nextMachine<<endl;
		cout<<"jobIndex="<<jobIndex<<endl;
	#endif

	JobPair jp=*(findJobpairByMachineAndJob(nextMachine,jobIndex));
	#ifdef DEBUG
		cout<<"jp.time="<<jp.time<<endl;
		cout<<"jp.endTime="<<jp.endTime<<endl;
	#endif
	jp.endTime=TT+jp.time;
	(*nextJobTable)[jobIndex]=jp;
}

/* addNextIndexTable(int)								 */
/* 次の生成テーブルを追加する							 */
void Gt::addNextIndexTable(int index){
	/*
	vector<vector<int> > nextIndex;
	nextIndex=mCreateTable[index];
	mCreateTable.push_back(nextIndex);
	*/
}

/* findJobpairByMachineAndJob(int,int,int)				 */
/* machineとjobにより設定テーブルよりJobPairを見つける	 */
/* orderを指定することにより、次の処理(NEXTJOBPAIR)や	 */
/* 前の処理(PREVJOBPAIR)と使い分ける					 */
Gt::JobPair* Gt::findJobpairByMachineAndJob(int machine,int jobIndex){
	for(int i=0;i<mTable[jobIndex].size();i++){
		if(mTable[jobIndex][i].machine==machine){
			return &mTable[jobIndex][i];
		}
	}
}

/* getASTable()											 */
/* ASが生成完了した際の最終的なテーブルを取得する		 */
vector<vector<int> > Gt::getASTable(){
	vector<vector<int> > completeTable;
	for(int i=0;i<mCreateTable.size();i++){
		vector<int> row;
		for(int j=0;j<mCreateTable[0].size();j++){
			row.push_back(mCreateTable[i][j].endTime);
		}
		completeTable.push_back(row);
	}
	return completeTable;
}

vector<vector<int> > Gt::convertAStoMatrix(const vector<vector<int> > &AS){
	vector<vector<int> > Matrix=vector<vector<int> >(AS.size(),vector<int>(AS[0].size(),0));
	for(int m=0;m<AS.size();m++){
		int T=0;
		for(int j=0;j<AS[0].size();j++){
			int tempT=INT_MAX;
			int tempJ=-1;
			for(int k=0;k<AS[0].size();k++){
				if(tempT>AS[m][k] && T<AS[m][k]){
					tempT=AS[m][k];
					tempJ=k;
				}
			}
			Matrix[m][j]=tempJ;
			T=tempT;
		}
	}
	return Matrix;
}

vector<vector<int> > Gt::getMatrix(){
	vector<vector<int> > matrix;
	matrix=getASTable();
	matrix=convertAStoMatrix(matrix);
	return matrix;
}

vector<vector<int> > Gt::fixMatrix(vector<vector<int> > matrix){
	mFix=true;
	for(int i=0;i<matrix.size();i++){
		vector<JobPair> a;
		for(int j=0;j<matrix[0].size();j++){
			JobPair jp;
			jp.jobIndex=matrix[i][j];
			jp.machine=i;
			a.push_back(jp);
		}
		mMatrix.push_back(a);
	}
	execute();
	vector<vector<int> > table=getASTable();
	table=convertAStoMatrix(table);
	return table;
}

int Gt::getMakespan(){
	vector<vector<int> > ASTable=getASTable();
	int T=0;
	for(int i=0;i<ASTable.size();i++){
		for(int j=0;j<ASTable[0].size();j++){
			if(T<ASTable[i][j])
				T=ASTable[i][j];
		}
	}
	return T;
}

Gt::JobPair& Gt::findJobpairByMachineAndJobFromMatrix(int machine,int jobIndex){
	#ifdef DEBUG
		cout<<"machine="<<machine<<endl;
		cout<<"jobIndex="<<jobIndex<<endl;
		cout<<"========================="<<endl;
		for(int i=0;i<mMatrix.size();i++){
			for(int j=0;j<mMatrix[0].size();j++){
				cout<<"mMatrix["<<i<<"]["<<j<<"]="<<mMatrix[i][j].machine<<","<<mMatrix[i][j].jobIndex<<","<<mMatrix[i][j].isCheck()<<" ";
			}
			cout<<endl;
		}
	#endif
	for(int i=0;i<mMatrix.size();i++){
		for(int j=0;j<mMatrix[0].size();j++){
			if(mMatrix[i][j].machine!=machine)
				continue;
			if(mMatrix[i][j].jobIndex!=jobIndex)
				continue;
			return mMatrix[i][j];
		}
	}
}

Gt::JobPair& Gt::getFirstNotCheckJobPairFromMatrix(int machine){
	for(int j=0;j<mMatrix[0].size();j++){
		if(mMatrix[machine][j].isCheck())
			continue;
		return mMatrix[machine][j];
	}
}

void Gt::changeOrderJobPairMatrix(int machine,int src,int dst){
	int p=-1,q=-1;
	for(int i=0;i<mMatrix[machine].size();i++){
		if(mMatrix[machine][i].jobIndex==src)
			p=i;
		if(mMatrix[machine][i].jobIndex==dst)
			q=i;
	}
	JobPair t=mMatrix[machine][p];
	mMatrix[machine][p]=mMatrix[machine][q];
	mMatrix[machine][q]=t;
}