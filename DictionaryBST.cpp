/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of class DictionaryBST's member functions required to
 perform insert and find operations using a C++ set STL.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert( std::string word ) {
  return (dictBST.insert( word ).second);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find( std::string word ) const {
  return (dictBST.find( word ) != dictBST.end());
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
