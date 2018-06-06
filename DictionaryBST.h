/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Declaration of class DictionaryBST's member functions required to
 perform insert and find operations using a C++ set STL.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#ifndef DICTIONARY_BST_H
#define DICTIONARY_BST_H

#include <set>
#include <string>

/**
 * The class for a dictionary ADT, implemented as a BST
 * When you implement this class, you MUST use a balanced binary
 * search tree in its implementation.  The C++ set implements 
 * a balanced BST, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryBST {
public:
  /* Create a new Dictionary that uses a BST back end */
  DictionaryBST();

  /* Insert a word into the dictionary. */
  bool insert( std::string word );

  /* Return true if word is in the dictionary, and false otherwise */
  bool find( std::string word ) const;

  /* Destructor */
  ~DictionaryBST();

private:
  //! C++ set STL backend
  std::set< std::string > dictBST;
};

#endif // DICTIONARY_BST_H
