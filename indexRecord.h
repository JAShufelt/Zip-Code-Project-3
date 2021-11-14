#pragma once
#ifndef INDEXRECORD
#define INDEXRECORD
class indexRecord
{public:
	indexRecord(int zip, int reffield)
	{
		zipCode = zip;
		referenceField = reffield;
	}
/**<
// This function merely pairs each zip code with its byte offset.
// @pre A zip code CSV file exists.
// @post Index contains byte offset each zip code.
// @param zip The zip code in question.
// @param reffield The byte offset for the zip code.
*/
		
	int zipCode;
	int referenceField;
};
#endif
