#ifndef _GT_H_
#define _GT_H_

#include <vector>
#include <map>

using namespace std;

class FileReader;

class Gt{
public:
	class JobPair{
	public:
		JobPair(){
			machine=-1;
			time=-1;	// 加工時刻
			endTime=-1;	// 加工終了時刻
			jobIndex=-1;
			checked=false;
			prev=-1;
			next=-1;
		}
		int machine;
		int prev;
		int next;
		int time;
		int endTime;
		int jobIndex;
		bool isCheck(){return checked;}
		void check(){checked=true;}
	private:
		bool checked;
	};
	typedef vector<vector<JobPair> > Table;
	
	Gt();
	Gt(const char*);
	void setTable(Table&);
	void execute();
	vector<vector<int> > getASTable();
	vector<vector<int> > convertAStoMatrix(const vector<vector<int> >&);
	vector<vector<int> > getMatrix();
	vector<vector<int> > fixMatrix(vector<vector<int> > );
	int getMakespan();
private:
	
	Table mTable;
	vector<vector<JobPair> > mCreateTable;
	vector<vector<JobPair> > mMatrix;
	int mJobNum;
	int mMachineNum;
	bool mFix;

	int getMinTimeOverT(pair<int,int>&);
	void fixConflict(int,pair<int,int>&);
	void setNextJobpair(int,pair<int,int>);
	void addNextIndexTable(int);
	Gt::JobPair* findJobpairByMachineAndJob(int,int);
	Gt::JobPair& findJobpairByMachineAndJobFromMatrix(int,int);
	Gt::JobPair& getFirstNotCheckJobPairFromMatrix(int);
	void changeOrderJobPairMatrix(int,int,int);
	enum {PREVJOBPAIR=-1,NOWJOBPAIR,NEXTJOBPAIR};

	static FileReader* fr;
};

#endif