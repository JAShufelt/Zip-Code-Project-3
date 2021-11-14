#include <iostream>
#include <fstream>
#include <string>
#include "buffer.h"
#include "record.h"
#include "headerBuffer.h"
#include "indexRecord.h"
using namespace std;

string li_to_blocked(string filename, headerBuffer headBuff);
/**<
//This function converts a length-indicated record data file into a
//blocked sequence set data file.
@pre A properly formatted length-indicated record data file exists
@post A new blocked sequence set data file is constructed
@param filename string containing the name of length-indicated record data file
@param headBuff a headerBuffer object
*/

string constructIndex(string blocked_filename);
/**<
//This function constructs an simple index file for a blocked
//sequence set data file
@pre A blocked sequence set data file exists
@post A new simple index file is constructed
@param blocked_filename string containing the name of the blocked sequence set data file
*/

int main(int arc, char* argv[])
{
    string filename = argv[1];  //Sets filename from the command line argument
    string len_ind_file;      //Variable for Length-Indicated CSV filename
    string blocked_filename;    //Variable for Blocked Sequence Set data filename
    string index_filename;
    
    headerBuffer headerBuff;    //Create a header record buffer
    
    cout << "Please wait while converting " + filename + " into a length-indicated format...";
    len_ind_file = headerBuff.convert(filename);  //Convert the file into a Length-Indicated CSV
    cout << "DONE" << endl;

    cout << "\nPlease wait while length-indicated format is converted to a blocked sequence set format...";
    blocked_filename = li_to_blocked(filename, headerBuff);   //Convert L-I CSV into Blocked Sequence Set data file
    cout << "DONE" << endl;

    cout << "\nGathering header record information for the blocked sequence set data file...";
    headerBuff.read(blocked_filename); //headerBuff reads the BSS data file to establish data for the files header
    cout << "DONE" << endl;

    cout << "\nReconstructing blocked sequence set data file with a header record...";
    blocked_filename = li_to_blocked(filename, headerBuff);   //Generate BSS data file, again but with header... This project is the worst
    cout << "DONE" << endl;
    
    cout << "\nContructing an index for " + blocked_filename + "...";
    index_filename = constructIndex(blocked_filename);   //Generates the simple index
    cout << "DONE" << endl;

    //Buffer buff = Buffer(blocked_filename); //Construct a buffer for the Blocked Sequenced Set
   
    

    //while(buff.read() != 0)
    //{
    //    if (buff.buffer_storage != "")
    //    buff.unpack(buff.buffer_storage);
    //}
    
    cout << "\nInitialization is complete." << endl;
}

/**<
// This is a main function that simply creates all of the structures needed to execute the program.
// This does not impliment any of the dynamic elements exect for the file name.
// @pre A zip code CSV file exists.
// @post A new length-indicated version of the file and an inex file exist.
// @param arc the number of characters in the file name.
// @param argv[] The file name stored as an array of characters.
*/

string li_to_blocked(string filename, headerBuffer headBuff)
{
    bool flag = false;
    int AVAIL_BYTES = 497;  //497 bytes of data available for each block (512 - 15, for the 15 bytes used for record count and links)
    int li_beginning = 0;      //First length indicator begins at byte 0
    int li_end = 4;            //First length indicator ends at byte 4
    int record_counter = 0;    //Counts the number of records being placed into a block during intialization
    string recc;               //String representation of record count
    int predecessor = 0;       //Stores the predecessor RBN, initially 0 for first block
    string pred;               //String representation of predecessor
    int successor = 2;         //Stores the successor RBN, initially 2 for first block
    string succ;               //String representation of successor

    ifstream read;                              //Ifstream object read, for reading the Length-Indicated File
    ofstream out;                               //Ofstrean object out, for writing the Blocked Sequence Set File
    
    string blocked_filename = filename;         //Stores Blocked Sequence Set Filename
    string li_filename;                         //Stores Length-Indicated Filename
    string data;                                //Stores all the data from the Length-Indicated File
    string data_copy;                           //A copy of data
    string temp;                                //A temporary string for string manipulations
    string block_data;                          //Stores all the data of a single block, used in construction of the Blocked Sequence Set File
    int temp_byte_count = 0;                    //Holds the total count of characters in a block as each record is added. Ensures block capacity is not exceeded
    
    blocked_filename.pop_back();
    blocked_filename.pop_back();
    blocked_filename.pop_back();
    blocked_filename.pop_back();

    li_filename = blocked_filename + "_LENGTH-INDICATED";   //Length-Indicated Filename set appropriately
    blocked_filename += "_BLOCKED.txt";                     //Blocked Filename set appropriately
    
    out.open(blocked_filename);

    if (headBuff.header_record != "")
    {
        out << headBuff.header_record;
    }
    
    read.open(li_filename);
    getline(read, data);

   while (true)         //This loop runs until it is broken by bool flag
   {
        while (temp_byte_count < AVAIL_BYTES) 
        {
            if (data.size() > AVAIL_BYTES)
            {
                temp = data.substr(li_beginning, li_end);
                temp_byte_count += stoi(temp) + 1;  // +1 for the comma at the end of each record

                li_beginning += stoi(temp) + 1;     // +1 to skip over the comma at the end of each record
                record_counter += 1;
            }
            else
            {
                flag = true;        //Indicates remaining records will fit in a block completely
                data_copy = data;   
                while (data_copy != "")     //Purpose of this loop is simply for counting remaining records that have yet to be placed into the final block
                {
                    temp = data_copy.substr(li_beginning, li_end);
                    data_copy.erase(0,stoi(temp) + 1);
                    record_counter++;
                }
                break;
            }
        }
        
        if (!flag)  //If: There are more blocks yet to be made, do the following.
        {
            temp_byte_count -= (stoi(temp) + 1);
            record_counter -= 1;

            block_data = data.substr(0, temp_byte_count);   //Captures enough records to fill the whole block without exceeding block
            data.erase(0, temp_byte_count);                 //Records captured in block_data and removed from the total data string
        }
        else       //Else: The last block is being made, do the following.
        {
            block_data = data;
        }
        
        recc = to_string(record_counter);   //Formatting record count with padding
        while(recc.size() < 2)
        {
            recc = "0" + recc;
        }

        pred = to_string(predecessor);      //Formatting predecessor with padding
        while(pred.size() < 5)
        {
            pred = "0" + pred;
        }

        succ = to_string(successor);        //Formatting successor with padding
        while(succ.size() < 5)
        {
            succ = "0" + succ;
        }

        block_data = recc + "," + pred + "," + succ + "," + block_data; //Contruct whole block
    
        out << block_data << endl;                                      //Print block into block file

        li_beginning = 0;            //Reseting variables for preparation of constructing a new block
        li_end = 4;                  //
        temp_byte_count = 0;         //
        record_counter = 0;          //
        predecessor++;               //
        successor++;                 //

        if (flag)       //Last block was made, so break loop
            break;
   }
    read.close();   //Close the Length-Indicated File
    out.close();    //Close the new Blocked Sequenced Set File

    return blocked_filename;
}

string constructIndex(string blocked_filename)
{
    Buffer buff;
    buff.recordVector.clear();
    ifstream file;
    ofstream index;
    string temp;
    int greatest_zip;
    int block_number = 1;

    string index_file_name = blocked_filename;      //Establish the name of the index file
    for(int i = 0; i < 12; i++)
    {
        index_file_name.pop_back();
    }
    index_file_name = index_file_name + "_INDEX.txt";

    
    file.open(blocked_filename);
    index.open(index_file_name);

    for(int i = 0; i < 22; i++)     //Skip past the header in BSS data file
    {
        getline(file, temp);
    }

    while(!file.eof())          //Unpack each block to determine greatest zip code in the block
    {
        getline(file, temp);
        
        if (temp != "")
        {
            buff.unpack(temp);

            greatest_zip = buff.recordVector[0].zipCode;

            for (int i = 0; i < buff.recordVector.size(); i++)
            {
                if (buff.recordVector[i].zipCode > greatest_zip)
                {
                    greatest_zip = buff.recordVector[i].zipCode;
                }
            }
            temp = to_string(greatest_zip) + "," + to_string(block_number);
            index << temp << endl;

            buff.recordVector.clear();
            block_number++;
        }
    }
    return index_file_name;
}