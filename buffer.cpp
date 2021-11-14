#include "buffer.h"
#include <cassert>
#include <fstream>
#include <stdlib.h>
#include "indexRecord.h"
using namespace std;

int Buffer::read()
{
    if(!reader.eof())
    {
        getline(reader, buffer_storage);
        return 1;
    }
    else
    {
        return 0;
    }
};

void Buffer::unpack(string data)
{
    char COMMA = ',';
    string recordData;
    
    int recordLength;
    string state;
    double lat;
    double lon;
    int zip;
    string place;
    string county;
    int fieldOrderPointer = 0;

    int record_count = stoi(data.substr(0, 2)); //First two bytes is the record count in the block
    int temp;
    int field = 0;
    string record_string;
    string partial_field = "";
    data.erase(0, 15);                          //Skip to the first block

    for(int i = 0; i < record_count; i++)
    {
        temp = stoi(data.substr(0, 4));
        record_string = data.substr(0, temp + 1);

        for(int i = 0; i < record_string.size(); i++)
        {
            if(record_string[i] != COMMA)
            {
                partial_field = partial_field + record_string[i];
            }
            
            else
            {
                if (field == 0)
                {
                    recordLength = stoi(partial_field);
                    field++;
                }
                else if (field == 1)
                {
                    zip = stoi(partial_field);
                    field++;
                }
                else if (field == 2)
                {
                    place = partial_field;
                    field++;
                }
                else if (field == 3)
                {
                    state = partial_field;
                    field++;
                }
                else if (field == 4)
                {
                    county = partial_field;
                    field++;
                }
                else if (field == 5)
                {
                    lat = stod(partial_field);
                    field++;
                }
                else if (field == 6)
                {
                    lon = stod(partial_field);
                    field++;
                }
                partial_field = "";
            }
        }
        Record newRecord = Record(recordLength,state,lat,lon,zip,place,county);
        recordVector.push_back(newRecord);
        data.erase(0, (temp + 1));
        field = 0;
    }
}
