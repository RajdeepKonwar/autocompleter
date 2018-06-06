/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of test program to test insert , find operations in the
 different types of dictionaries, namely BST, Hashtable & Trie and also test
 the auto-completion functionality implemented in the Trie dictionary using TST.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>
#include "util.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"

using namespace std;

int main( int i_argc, char** i_argv ) {
  //! Check for Arguments
  if( i_argc != 2 ) {
    cout << "Invalid number of arguments." << endl
         << "Usage: ./test <input filename>." << endl;
    return -1;
  }

  //! Initialize words
  vector< string >            words;
  vector< string >::iterator  wit;
  vector< string >::iterator  wen;

  //! Initialize data structures
  DictionaryBST       d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie      dt;

  bool t_bst, t_ht, tt;

  words.push_back( "harry" );
  words.push_back( "sriram" );
  words.push_back( "cse" );
  words.push_back( "crucio" );
  words.push_back( "autocomplete" );

  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for( ; wit != wen; ++wit ) {
    cout << "Inserting: \"" << *wit << "\"... ";
    t_bst = d_bst.insert( *wit );
    t_ht  = d_ht.insert( *wit );
    tt    = dt.insert( *wit, 1 );
    //cout << t_bst << " " << t_ht << " "<< tt << "... ";

    if( !t_bst )
      cout << "failed for DictionaryBST... ";

    if( !t_ht )
      cout << "failed for DictionaryHashtable... ";

    if( !tt )
      cout << "failed for DictionaryTrie... " << endl;

    if( t_bst && t_ht && tt )
      cout << "PASSED! :D " << endl;
  }

  cout << endl <<
            "Re-inserting elements that were just inserted into Dictionaries..."
            << endl;

  wit = words.begin();
  wen = words.end();
  for( ; wit != wen; ++wit ) {
    cout << "Inserting: \"" << *wit << "\"... ";
    t_bst = d_bst.insert( *wit );
    t_ht  = d_ht.insert( *wit );
    tt    = dt.insert( *wit, 0 );

    if( !t_bst )
      cout << "failed for DictionaryBST... ";

    if( !t_ht )
      cout << "failed for DictionaryHashtable... ";

    if( !tt )
      cout << "failed for DictionaryTrie... " << endl;

    if( t_bst && t_ht && tt )
      cout << "PASSED! :D " << endl;
  }

  cout << endl;

  wit = words.begin();
  wen = words.end();
  for( ; wit != wen; ++wit ) {
    cout << "Searching for: \"" << *wit << "\"... ";
    t_bst = d_bst.find( *wit );
    t_ht  = d_ht.find( *wit );
    tt    = dt.find( *wit );

    if( !t_bst )
      cout << "failed for DictionaryBST... ";

    if( !t_ht )
      cout << "failed for DictionaryHashtable... ";

    if( !tt )
      cout << "failed for DictionaryTrie... ";

    if( t_bst && t_ht && tt )
      cout << "PASSED! :D " << endl;
  }

  cout << endl;

  //! istream
  ifstream fin;
  fin.open( i_argv[1] );

  //! Check if input file was actually opened
  if( !fin.is_open() ) {
    cout << "Invalid input file. No file was opened. Please try again." << endl;
    return -1;
  }

  Utils::load_dict( dt, fin );
  fin.close();

  std::string prefix  = "in";
  unsigned int numCom = 20;
  std::vector< std::string > pred = dt.predictCompletions( prefix, numCom );

  cout << "Top " << numCom << " predictions for prefix \'" << prefix
       <<"\' (using dictionary \'" << i_argv[1] << "\'):" << endl;
  for( size_t i = 0; i < pred.size(); i++ )
    cout << pred[i] << endl;

  return 0;
}
