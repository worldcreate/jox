#ifndef _TEST_H_
#define _TEST_H_

#include <vector>

using namespace std;

class Test{
public:
	Test();
	void test();
private:
	void print(const vector<vector<int> >&);
	void check(const vector<vector<int> >&);
	void func(vector<vector<int> >vec,int,int,int);
};

#endif