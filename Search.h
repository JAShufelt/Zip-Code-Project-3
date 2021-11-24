#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include "record.h"
#include <vector>
#include "headerBuffer.h"
#include "indexRecord.h"
using namespace std;

class Buffer
{
 public:
    void Search();
    void dump(ifstream& blocked);
};

#endif