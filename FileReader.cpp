#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "FileReader.h"

map<string,FileReader*> FileReader::pool;

FileReader* FileReader::getInstance(const char *file){
	string str(file);
	if (pool.find(str) == pool.end()) {
		FileReader* fileReader=new FileReader(str.c_str());
		pool[str]=fileReader;
	}
	return pool[str];
}

FileReader::FileReader(const char *file){
	printf("FileReader\n");
	ifstream ifs(file);
	string str;
	int j=0;

	while(getline(ifs,str)){
		vector<Gt::JobPair> row;
		vector<string> array=split(str,':');

		for(int i=0;i<array.size();i++){
			vector<string> pair=split(array[i],',');
			const char *machine=pair[0].c_str();
			const char *time=pair[1].c_str();
			Gt::JobPair jp;
			jp.machine=atoi(machine);
			jp.time=atoi(time);
			jp.endTime=-1;
			jp.jobIndex=j;
			if(i!=0){
				jp.prev=row[i-1].machine;
				row[i-1].next=jp.machine;
			}
			row.push_back(jp);
		}
		mTable.push_back(row);
		j++;
	}
	#ifdef DEBUG
		cout<<"jobIndex list"<<endl;
		for(int i=0;i<mTable.size();i++){
			for(int j=0;j<mTable[0].size();j++){
				cout<<mTable[i][j].jobIndex<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	#endif
}

Gt::Table FileReader::getTable(){
	return mTable;
}

vector<string> FileReader::split(const string &str, char delim){
	istringstream iss(str); string tmp; vector<string> res;
	while(getline(iss, tmp, delim)) res.push_back(tmp);
	return res;
}