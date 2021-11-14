#ifndef BUFFER_H
#define BUFFER_H

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
     ifstream reader;
     ofstream writer;

     vector<vector <Record> > outer;
     vector<Record> recordVector;

     string buffer_storage;
 
 Buffer()
 {
 }
 /**<
 // This is a default constructor.
 // @pre There is no buffer object.
 // @post A buffer object is created with all data members initialized to null.
 */
 
 Buffer(string blocked_filename)
 {
     reader.open(blocked_filename);
 }
 /**<
 // An alternative Buffer constructor
 // @param blocked_filename string containing name of the blocked sequence set data file 
 // @post A buffer object is created, with its reader having opened the provided data file
 */

 int read();
 /**<
 // This function gets a line from the file opened within the buffer object's reader
 // and stores it inside the buffer object's buffer_storage
 // @pre reader must have opened a file
 // @post A line from the file is stored in buffer_storage
 // @return Int, returns a 1 if it successfully read a line, returns 0 if the end of the file has been met
 */
 
 void unpack(string data);
 /**<
 // This function takes in a whole block of data as a string
 // and unpacks every record, storing it inside of the
 // buffer object's recordVector
 // @pre data is formatted properly as block
 // @post The buffer object's recordVector will contain all the records within the block
 // @param data string containing a whole block of data.
 */
 
private:
 ifstream upc;
};

#endif
