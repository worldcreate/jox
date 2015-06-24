#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include "Gt.h"

class FileReader{
public:
	FileReader(const char *);
	Gt::Table getTable();
private:
	Gt::Table mTable;
	vector<string> split(const string &str, char delim);
};

#endif