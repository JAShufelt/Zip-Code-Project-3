#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Record
{
 public:

 
 Record()
 {
     lengthIndicator = NULL;
     state = "";
     lat = NULL;
     lon = NULL;
     zipCode = NULL;
     placeName = "";
     county = "";
 }
/**<
 // This is a default constructor.
 // @pre There is no record object.
 // @post A record object is created with all data members initialized to null.
 */
 
 Record(int lenind, string st, double la, double lo, int zip, string place, string count)
 {
     lengthIndicator = lenind;
     state = st;
     lat = la;
     lon = lo;
     zipCode = zip;
     placeName = place;
     county = count;
 }
/**<
 // This is a constructor with parameters. When the object is created with
 // parameters, this will assign the parameters to the corresponding data
 // members.
 // @pre 
 // @post 
 // @param st The zip code's state.
 // @param la The zip code's lattitude.
 // @param lo The zip code's longitude.
 // @param zip The zip code.
 // @param place The zip code's place name.
 // @param count The zip code's county.
 */
 
 string get_state();
 /**<
 // This is a getter function that returns the state abbreviation.
 // @pre A record exists.
 // @post The state abbreviation is returned.
 // @return The state abbreviation.
 */
 
 double get_lat();
 /**<
 // This is a getter function that returns the lattitude.
 // @pre A record exists.
 // @post The lattitude is returned.
 // @return The lattitude.
 */
 
 double get_long();
 /**<
 // This is a getter function that returns the longitude.
 // @pre A record exists.
 // @post The longitude is returned.
 // @return The longitude.
 */
 
 int get_zip();
 /**<
 // This is a getter function that returns the zip code.
 // @pre A record exists.
 // @post The zip code is returned.
 // @return The zip code.
 */

 public:
 string state;
 double lat;
 double lon;
 int zipCode;
 string placeName;
 string county;
 int lengthIndicator;
};

#endif
