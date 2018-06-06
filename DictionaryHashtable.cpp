/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of class DictionaryHashTable's member functions required to
 perform insert and find operations using a C++ unordered_set STL.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert( std::string word ) {
  return (dictHash.insert( word ).second);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find( std::string word ) const {
  return (dictHash.find( word ) != dictHash.end());
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
