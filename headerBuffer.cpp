#include "headerBuffer.h"
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//Converts the original CSV file into a Length-Indicated CSV file
string headerBuffer::convert(string filename)
{
	string temp_filename = filename;	//Name of the original CSV, passed by commandline in main
	
	temp_filename.pop_back();		//This removes the ".csv" from the filename
	temp_filename.pop_back();		//
	temp_filename.pop_back();		//
	temp_filename.pop_back();		//
	
	string converted_filename = temp_filename + "_LENGTH-INDICATED";	//This adds "_LENGTH-INDICATED" to the file name. For example "us_postal_codes.csv"
	int stringLength;													//would become "us_postal_codes_LENGTH-INDICATED" (generic file type)
	string line = "";
	string temp, recordLength;
	ifstream upc;
	ofstream out;
	upc.open(filename);
	out.open(converted_filename);
	for (int i = 0; i < 3; i++)
		getline(upc, temp);

	//cout << "Please wait while converting "<< filename <<" to a length indicated record format..." << endl;
	while (!upc.eof())
	{
		getline(upc, temp);		//grab a line of text from upc
		stringLength = temp.size() + 5;		//get the size of the current line in upc and add 5 (for the 4 character length indicator, plus a comma)
		recordLength = to_string(stringLength);		//recordLength = number of characters in the line plus the "self counting" length indicator

		if (temp != "")
		{
			for (int i = (to_string(stringLength)).size(); i < 4; i++)	//Process for creating the formatted "self counting" length indicator
			{
				recordLength = "0" + recordLength;
			}

			line = line + recordLength + "," + temp + ",";		//line gains the current record beginning with its "self counting" length indicator
		}
	}

	out << line;	//Write the line to a file
	upc.close();	//Close the file
	out.close();	//Close the file
	//cout << "CSV successfully converted to file: " << converted_filename << endl;

	return converted_filename;
}

//Reads a blocked sequence set data file and gathers header information
void headerBuffer::read(string filename)
{
	//Hardcoded Header Attributes
	structure_Type = "blocked sequence set with comma separated fields, and length-indicated records";
	file_Version = 1.0;
	bytes_per_record_Size = 4;
	size_Format = "ASCII";
	index_Schema = "largest zip-code in block,RBN";
	min_block_cap = "50%";
	block_size = 512;
	fields_Count = 6;
	primary_Key = 1;
	avail_link = -1;	//Normally dynamic, but will there will always be 0 avail blocks upon block initialization.
	stale_flag = false;

	//Dynamic Header Attributes
	header_record_Size = 0;
	index_file_Name = "";
	record_Count = 0;
	block_Count = 0;
	active_link = 0;

	string temp;
	string csv_filename;
	fstream file;
	ifstream original;
	file.open(filename);

	index_file_Name = filename;

	for(int i = 0; i < 12 ;i++)		//Dynamically discover name of the index file for the BSS data file.
	{
		index_file_Name.pop_back();
	}
	csv_filename = index_file_Name;
	csv_filename = csv_filename + ".csv";				//Dynamically discover original CSV filename
	index_file_Name = index_file_Name + "_INDEX.txt";	//Name of index file found


	while(!file.eof())			//Dynamically discover block_Count
	{
		getline(file, temp);
		block_Count++;
	}
	block_Count--;				//Subtract 1 for the empty line at end of the file.
	file.close();

	original.open(csv_filename);

	while(!original.eof())
	{
		getline(original, temp);
		record_Count++;
	}
	record_Count -= 4;		//Subtract 4 for the CSV fields, and the extra line in the CSV
	original.close();

	active_link = block_Count;	//The active link will be the last block created.

	header_record = 
		"File Structure Type: " + structure_Type + "\n" +
		"Version: " + to_string(file_Version) + "\n" +
		"Bytes Allocated for Record Length Indicators: " + to_string(bytes_per_record_Size) + "\n" +
		"Size Format Type: " + size_Format + "\n" +
		"Block Size: " + to_string(block_size) + "\n" +
		"Minimum Block Capacity: " + min_block_cap + "\n" +
		"Index File Name: " + index_file_Name + "\n" +
		"Index File Schema: " + index_Schema + "\n" +
		"Total Record Count: " + to_string(record_Count) + "\n" +
		"Total Block Count: " + to_string(block_Count) + "\n" +
		"Fields per Record: " + to_string(fields_Count) + "\n" +
		"Zip Code: int\n" +
		"Place Name: string\n" +
		"State: string\n" +
		"County: string\n" +
		"Latitude: double\n" +
		"Longitude: double\n" +
		"Primary Key Ordinally: " + to_string(primary_Key) + "\n" +
		"RBN Link to Active: " + to_string(active_link) + "\n" +
		"RBN Link to Avail: " + to_string(avail_link) + "\n" +
		"Stale Flag: " + to_string(stale_flag) + "\n";

	temp = "Header Record Size: ";
	header_record_Size = temp.size() + header_record.size();
	header_record_Size = header_record_Size + to_string(header_record_Size).size();

	header_record_Size += 20;
	temp = temp + to_string(header_record_Size) + "\n" + header_record;
	header_record = temp;
}

//Write function writes the header for the Length-Indicated CSV 
void headerBuffer::write(string filename)
{
	string contents;
	ifstream upc;
	ofstream out;

	upc.open(filename);		//Open the Length-Indicated CSV 
	getline(upc, contents);	//Getline retrieves all the contents of the CSV since it is all in one line, and stores it in string contents 
	upc.close();			//Close the file

	contents = header_record + contents;		//Add the header record to beginning of contents

	out.open(filename, ios::out | ios::trunc);	//Open the Length-Indicated CSV for writing (it is cleared by truncating function)
	out << contents;							//Rewrite the contents with the header to the Length-Indicated CSV
	out.close();								//Close the file
}

//Returns the length of the header record of the Length-Indicated CSV
int headerBuffer::getHeaderRecordSize()
{
	return header_record_Size;
}

