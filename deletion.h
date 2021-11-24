#ifndef DELETION_H
#define DELETION_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
class Deletion
{
public:
	void addition(ifstream& alterFile);
    void deletion(ifstream& alterFile);
    void write_blocked_file(string head, vector<string> wbf, int bc);
    void write_index_file(vector<string> wif);
};

#endif