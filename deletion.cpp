#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Deletion.h"
#include "indexRecord.h"
#include "record.h"
#include "buffer.h"
#include "Search.cpp"

using namespace std;

void Deletion::addition(ifstream& alterFile)
{
    ifstream blockedFile ("us_postal_codes_BLOCKED.txt");
    ifstream indexFile ("us_postal_code_INDEX.txt");
    vector<string> blocked_vector;
    vector<string> index_vector;
    string bypass_header, block_line, header = "", temp, indZip = "", az;
    char COMMA = ',';
    char SPECIAL = '%';
    int blockCount = 0, indexZip, add_zip, add_rec, new_rec;

	for (int i = 0; i < 22; i++)
    {
	    getline(blockedFile, bypass_header);
        header = header + bypass_header + SPECIAL;
    }
    
    while (!blockedFile.eof())
    {
        getline(blockedFile, block_line\);
        blocked_vector.push_back(block_line);
    }

    while (!indexFile.eof())
    {
        getline(indexFile, index_line_full);
        index_vector.push_back(index_line_end);
    }

    blockedFile.close();
    indexFile.close();

    while (!alterFile.eof())
    {
        for (int i = 0; i < 22; i++)
        {
	        getline(alterFile, trash);
        }
        
        getline(alterFile, add_rec);

        if (add_rec.size() < 10)
        {
            new_rec = "000"
        }
        else if (add_rec.size() < 100)
        {
            new_rec = "00" + add_rec.size() + COMMA + add_rec;
        }
        else if (add_rec.size() < 1000)
        {
            new_rec = "0" + add_rec.size() + COMMA + add_rec;
        }
        else if (add_rec.size() >= 1000)
        {
            new_rec = add_rec.size() + COMMA + add_rec;
        }

        while (add_rec[j] != COMMA)
        {
            az = az + add_rec[j];
            j++;
        }

        add_zip = stoi(az);

        for (int i=0; i<index_vector.size(); i++)
        {
            temp = index_vector[i];
            int j = 0;

            while (temp[j] != COMMA)
            {
                indZip = indZip + temp[j];
                j++;
            }

            indexZip = stoi(indZip);
            string maybe = index_vector[i-1];
            string may = "";
            int j =0;

            while (maybe[j] != COMMA)
            {
                trash = maybe[j];
                j++;
            }

            j++

            while (j < maybe.size())
            {
                may = may + maybe[j];
            }

            int blonu = stoi(may) + 1;

            if ((indexZip > add_zip))
            {
                index_vector[i-1] = index_vector[i-1] + SPECIAL + add_zip + COMMA + blonu;
            }
            else if (i == index_vector.size())
            {
                index_vector.push_back(add_zip + COMMA + blonu);
            }

            rp = stoi(recordPlace);
            index_vector[i] = "";
            cout << endl << "\"" << delete_zip << COMMA << rp << "\" from index has been deleted." << endl;
            int blockNumber = rp/10;
            int offset = ((rp-blockNumber) * 7) + 3;
            string tempA = blocked_vector[blockNumber], tempB = "", tempC = "";
            int m = 0;

            for (int k=0; k<offset; k++)
            {
                while (tempA[m] != COMMA)
                {
                    tempB = tempB + tempA[m];
                    m++;
                }

                m++;
                tempB=tempB+COMMA;
            }

            for (int n=m; n<tempA.size(); n++)
            {
                tempC = tempC + tempA[n];
            }

            blocked_vector[blockNumber] = tempB + new_rec + tempC;
            indZip = "";
        }
    }

    write_blocked_file(header, blocked_vector, blockCount);
    write_index_file(index_vector);
    Search::dump(alterFile);
};

 /**<
 // This function reads records from a passed file, turns the index file into
 // a string vector, and turns the blocked file into a string vector. Then,
 // It finds the place this record would go in the index and writes it there.
 // The function does the same for the blocked file. Finally, it rewrites
 // both files and calls the dump function.
 // @pre There is a file containing records the user wishes to add.
 // @post These records are added into the index and blocked files in
 //       memory and two dump files exist.
 // @param alterFile A reference to a file with the records(s) being added.
 */

void Deletion::deletion(ifstream& alterFile);
{
    Search::dump(alterFile);
    ifstream blockedFile ("us_postal_codes_BLOCKED.txt");
    ifstream indexFile ("us_postal_code_INDEX.txt");
    vector<string> blocked_vector;
    vector<string> index_vector;
    string bypass_header, block_line, delte_zip, header = "";
    char COMMA = ',';
    char SPECIAL = '%';
    int blockCount = 0;

	for (int i = 0; i < 22; i++)
    {
	    getline(blockedFile, bypass_header);
        header = header + bypass_header + SPECIAL;
    }
    
    while (!blockedFile.eof())
    {
        getline(blockedFile, block_line\);
        blocked_vector.push_back(block_line);
    }

    while (!indexFile.eof())
    {
        getline(indexFile, index_line_full);
        index_vector.push_back(index_line_end);
    }

    blockedFile.close();
    indexFile.close();

    while (!alterFile.eof())
    {
        for (int i = 0; i < 22; i++)
        {
	        getline(alterFile, trash);
        }
        
        getline(alterFile, delete_zip);
        string recordPlace = "", trash;
        int rp;

        for (int i=0; i<index_vector.size(); i++)
        {
            string indexZip = "";
            string tempA = index_vector[i];
            string tempB;
            string lengInd = "";
            int j = 0;

            while (tempA[j] != COMMA)
            {
                indexZip = indexZip + tempA[j];
                j++;
            }

            if (delete_zip == stoi(indexZip))
            {
                for (int k=j+1; k<tempA.size(); k++)
                {
                    recordPlace = recordPlace + tempA[k];
                }

                rp = stoi(recordPlace);
                index_vector[i] = "";
                cout << endl << "\"" << delete_zip << COMMA << rp << "\" from index has been deleted." << endl;
                int blockNumber = rp/10;
                int offset = ((rp-blockNumber) * 7) + 3;
                tempA = blocked_vector[blockNumber];
                int m = 0;

                for (int k=0; k<offset; k++)
                {
                    while (tempA[m] != COMMA)
                    {
                        tempB = tempA[m];
                        m++;
                    }

                    m++;
                }

                while (tempA[m] != COMMA)
                {
                    lengInd = lengInd + tempA[m];
                    blocked_vector[blockNumber][m] = '';
                    m++;
                }

                int li = stoi(lengInd);
                cout << "\"" << lengInd;

                for (int k=m; k <= (li-4); k++)
                {
                    cout << blocked_vector[blockNumber][k];
                    blocked_vector[blockNumber][k] = '';
                }

                recordPlace="";
                cout << "\" has been deleted from blocked record file." << endl;
            }

            indexZip = "";
        }
    }

    write_blocked_file(header, blocked_vector, blockCount);
    write_index_file(index_vector);
};

 /**<
 // This function reads a file of zip codes the user wshes to delete. Then, it turns
 // the index and blocked files into string vectors based on each line of each file.
 // The function searches the index for the zip codes, deletes them from the index
 // file, and notifies the user. Then it locates them in the blocked file vector,
 // deletes them from there, and the notifies the user. It also does a dump for each
 // zip code. Finally, it calls two functions to rewrite the new index and blocked
 // files.
 // @pre There is a file containing zip codes of records the user wishes to delete.
 // @post The records of these zip codes have been deleted from the blocked file and
 //       index file, two dump files exist, and alterations to all these files have
 //       been announced to user.
 // @param alterFile ifstream& the file containing all zipcodes of records that will be
 //        deleted and then dumped.
 */

void Deletion::write_blocked_file(string head, vector<string> wbf, int bc)
{
    ofstream blocked_file ("us_postal_codes_BLOCKED.txt");
    char SPECIAL = '%';
    vector<string> blofi;
    string temp = "";
    int blockNumber=0;
    static int charCount=0;
    static int commCount=0;

    for (int i = 0; i < header.size(); i++)
    {
        if (header[i] != COMMA)
        {
            blocked_file << header[i];
        }
        else
        {
            blocked_file << endl;
        }
    }

    for (int i; i < bc; i++)
    {
        blocked_file << wbf[i];
    } 
};

 /**<
 // This function uses the header string and blocked string vector from the previous
 // function and writes them into the new blocked file.
 // @pre An edited blocked file exists in memory as a string vector.
 // @post There is a new, edited blocked file.
 // @param head A string containing the original header.
 // @param wbf A vector of strings the hold the edited blocked file.
 // @param bc An integer that contains a count of the number of blocks.
 */

void Deletion::write_index_file(vector<string> wif)
{
    ofstream index_file ("us_postal_codes_INDEX.txt");

    for (int i = 0; i < wif.size(); i++)
    {
        index_file << wif[i] << endl;
    }

    index_file.close();
};

 /**<
 // This function simply writes the edited index file string vector into a new
 // index file.
 // @pre Edited index exists in memory as a string vector.
 // @post A new, edited index file exists.
 // @param wif A string vector containing the edited index file.
 */