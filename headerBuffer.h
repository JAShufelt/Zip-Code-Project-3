#pragma once
#ifndef HEADERBUFFER_H
#define HEADERBUFFER_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
class headerBuffer
{
public:
	string convert(string filename);
/**<
// This function converts the original file into a length-indicated CSV
// file. First, it creates a new name for the length-indicated file. Then,
// it gets the data from the original file and adds a self-counting length
// indicator and a comma. Finally, it writes everything to the file and
// closes it.
// @pre There is a CSV file.
// @post A length-indicated version of the file exists.
// @param filename A string containing the original file's name.
// @return The file name of the converted file.
*/
	
	void read(string filename);
/**<
// This function allows the headerBuffer to read a blocked sequence set
// data file, and gather header information for the header record.
// @pre A blocked sequence set data file exists
// @post Attributes for the header record are stored within the headerBuffer object,
// @param filename A string containing the blocked sequence set data file name.
*/

	void write(string filename);
/**<
// This function writes the header at the top of the length-indicated file.
// @pre The length-indicated file exists and a vector contains the field order.
// @post A header is written at the top of the length-indicated file.
// @param filename A string containing the name of the length-indicated file.
*/
	int getHeaderRecordSize();
/**<
// This function returns the size of the header record.
// @pre Header Record exists.
// @post Size of header record is returned.
// @return Size of the header record as integer.
*/
public:
	string structure_Type;	//Blocked Sequence Set with Comma Separated Fields, and Length-Indicated Records
	double file_Version;	//1.0
	int header_record_Size;	//Discovered Dynamically while reading
	int bytes_per_record_Size;	//4
	int block_size;		//512
	string min_block_cap;	//50%
	string size_Format;	//ASCII
	string index_file_Name;	//Discovered Dynamically while reading
	string index_Schema;	//Description of index
	int block_Count;	//Discovered Dynamically while reading
	int record_Count;	//Discovered Dynamically while reading
	int fields_Count;	//6
	int primary_Key;	//1
	int active_link;	//Discovered Dynamically
	int avail_link;		//-1, always -1 when a list was just created.
	bool stale_flag;	//false by default

	string header_record = "";	//Discovered Dynamically while reading
	vector<string> fieldOrder;	//Constructed while reading for maintaining field order.
};
#endif
