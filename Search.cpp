// Search.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include "record.h"
#include "indexRecord.h";
#include "buffer.h";

using namespace std;

int main(int argc, char* argv[])
{
	ifstream index;
	ifstream blocked;
	bool flagSearched = false;
	bool flagFound = false;
	vector<string> not_foundRecords;
	vector<Record> foundRecords;

	string blocked_filename = argv[1];
	string temp;
	string index_line;
	string largest_zip = "";
	string block_number = "";

	char COMMA = ',';
	
	string index_filename = blocked_filename;
	for(int i = 0; i < 12; i++)
	{
		index_filename.pop_back();
	}
	index_filename = index_filename + "_INDEX.txt";

	for(int i = 2; i < argc ; i++)	//Loop once for all flags other than the filename in the CLAs
	{
		temp = argv[i];				

		if(temp.substr(0,2) == "-Z")	//Enter condition if the CLA was a -Z search command
		{
			temp.erase(0, 2);
			index.open(index_filename);

			while(!index.eof())			//Iterate through whole index looking for which index line might contain the zip code
			{
				getline(index, index_line);			
				for(int i = 0; i < index_line.size(); i++)		//This loop breaks the current line up into the largest_zip and the block number
				{
					if (index_line[i] != COMMA)
					{
						largest_zip = largest_zip + index_line[i];
					}
					else
					{
						block_number = index_line.substr(largest_zip.size() + 1, index_line.size());
						break;
					}
				}
				
				if(largest_zip != "" && stoi(temp) <= stoi(largest_zip))		//If the zipcode being searched for could potentially be in the block addressed by the current index line
				{
					flagSearched = true;
					string data;
					Buffer buff;
					blocked.open(blocked_filename);

					for(int i = 0; i < stoi(block_number) + 22; i++)	//Navigate to the corresponding block 
					{
						getline(blocked, data);
					}

					buff.unpack(data);		//Unpack all the records in the corresponding block
					
					for (int i = 0; i < buff.recordVector.size(); i++)		//Search all records in the block for the zip code
					{
						if(temp == to_string(buff.recordVector[i].zipCode))	//If the zip code is found in the block add it to the Found Records vector
						{
							foundRecords.push_back(buff.recordVector[i]);
							flagFound = true;	//A record was found matching the zip code
							break;
						}
					}

				}
				largest_zip = "";
				block_number = "";
				if (flagSearched) break;	//Break the loop if the appropriate blocked was already searched
			}
		
			if(!flagFound)					//If the zipcode searched for doesn't have a matching record
			{
				not_foundRecords.push_back(temp);
			}
		}
		index.close();
		blocked.close();
		flagSearched = false;
		flagFound = false;
	}

	if (foundRecords.size() >= 1)	//If there was matching records from the search, display a table for them
	{
		cout << "Records Found" << endl;
		cout << "-------------" << endl;

		for (int i = 0; i < foundRecords.size(); i++)
		{
			cout <<
				to_string(foundRecords[i].zipCode) + " " +
				foundRecords[i].placeName + " " +
				foundRecords[i].state + " " +
				foundRecords[i].county + " " +
				to_string(foundRecords[i].lat) + " " +
				to_string(foundRecords[i].lon) + " " << endl;
		}
	}

	if (not_foundRecords.size() >= 1)	//If there was any zip codes that weren't found in the search, display a table for them
	{
		cout << "\nZip Codes Not Found" << endl;
		cout << "-------------------" << endl;

		for(int i = 0; i < not_foundRecords.size(); i++)
		{
			cout << not_foundRecords[i] << endl;
		}
	}
}
/**<
// This is the main function which performs searching on the blocked sequence set data file
// @pre Initalization was performed, and there exists a blocked sequence set data file, and corresponding index.
// @post A table of the search results is displayed to the user.
// @param arc Int containing the number of commandline arguments passed.
// @param argv[] string[] containing the blocked sequence set data file as the first element, followed by search terms.
*/