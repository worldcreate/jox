#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <map>
#include <string>
#include "Gt.h"

using namespace std;

class FileReader{
public:
	static FileReader* getInstance(const char *);
	Gt::Table getTable();
private:
	FileReader(const char *);
	Gt::Table mTable;
	vector<string> split(const string &str, char delim);
	static map<string,FileReader*> pool;
};

#endif