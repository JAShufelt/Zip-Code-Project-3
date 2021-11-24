#include <iostream>
#include <fstream>
#include <string>
#include "deletion.cpp"
#include "Search.cpp"

using namespace std;

int main()
{
    Deletion::addition(test1.txt);
    Deletion::addition(test2.txt);
    Deletion::deletion(test3.txt);
    Deletion::deletion(test4.txt);
    Deletion::deletion(test5.txt);
    return 0;
}