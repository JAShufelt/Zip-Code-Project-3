#include "record.h"
#include <cassert>
using namespace std;


 string Record::get_state()
 {
     return state;
 }
 
 double Record::get_lat()
 {
     return lat;
 }
 
 double Record::get_long()
 {
     return lon;
 };

 int Record::get_zip() 
 {
     return zipCode;
 }