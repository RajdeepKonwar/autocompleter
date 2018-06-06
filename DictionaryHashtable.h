/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Declaration of class DictionaryHashTable's member functions required to
 perform insert and find operations using a C++ unordered_set STL.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#ifndef DICTIONARY_HASHTABLE_H
#define DICTIONARY_HASHTABLE_H

#include <unordered_set>
#include <string>

/**
 *  The class for a dictionary ADT, implemented as a Hashtable
 * When you implement this class, you MUST use a Hashtable
 * in its implementation.  The C++ unordered_set implements 
 * a Hashtable, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryHashtable {
public:
  /* Create a new Dictionary that uses a Hashset back end */
  DictionaryHashtable();

  /* Insert a word into the dictionary. */
  bool insert( std::string word );

  /* Return true if word is in the dictionary, and false otherwise */
  bool find( std::string word ) const;

  /* Destructor */
  ~DictionaryHashtable();

private:
  //! C++ unordered_set STL backend
  std::unordered_set< std::string > dictHash;
};

#endif // DICTIONARY_HASHTABLE_H
