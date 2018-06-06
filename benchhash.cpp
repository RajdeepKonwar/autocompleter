/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of benchhash program which is used to research and compare the
 performance of 2 different hash functions for strings.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "util.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"

using namespace std;

//! Hash functions declaration
unsigned int hashFn1( string str, const unsigned int tableSize );
unsigned int hashFn2( string str, const unsigned int tableSize );

int main( int i_argc, char** i_argv ) {
  //! Check for Arguments
  if( i_argc != 3 ) {
    cout << "Invalid number of arguments." << endl
         << "Usage: ./benchhash <dictfile> <num_words>." << endl;
    return -1;
  }

  //! Variables declaration
  unsigned int i, j, hashVal, numSteps;
  unsigned int num_words  = atoi( i_argv[2] );
  unsigned int table_size = 2 * num_words;

  vector< string >            words;
  vector< string >::iterator  iter;
  map< unsigned int, unsigned int >::iterator         it;
  map< unsigned int, unsigned int >::reverse_iterator rit;

  //! Try and open dictionary
  ifstream dictfile;
  dictfile.open( i_argv[1] );

  //! Check if input file was actually opened
  if( !dictfile.is_open() ) {
    std::cout << "Invalid input file. No file was opened. Please try again."
              << std::endl;
    return -1;
  }

  //! verify correctness of the two hash functions
  vector< string > testStr;
  testStr.push_back( "RK" );
  testStr.push_back( "Ace" );
  testStr.push_back( "Jim" );

  //! Testing hash function 1
  hashVal = hashFn1( testStr[0], 6 );
  cout << "Testing hash function #1" << endl;
  cout << "Hash value of RK = " << hashVal << endl;
  hashVal = hashFn1( testStr[1], 6 );
  cout << "Hash value of Ace = " << hashVal << endl;
  hashVal = hashFn1( testStr[2], 6 );
  cout << "Hash value of Jim = " << hashVal << endl << endl;

  //! Testing hash function 2
  hashVal = hashFn2( testStr[0], 6 );
  cout << "Testing hash function #2" << endl;
  cout << "Hash value of RK = " << hashVal << endl;
  hashVal = hashFn2( testStr[1], 6 );
  cout << "Hash value of Ace = " << hashVal << endl;
  hashVal = hashFn2( testStr[2], 6 );
  cout << "Hash value of Jim = " << hashVal << endl << endl;

  //! Load num_words words from dictionary then close file
  Utils::load_vector( words, dictfile, num_words );
  dictfile.close();

  //! Iterate main loop for the 2 hash functions
  for( j = 1; j <= 2; j++ ) {
    //! Map of #hits and #slots corresponding to those hits
    map< unsigned int, unsigned int > hitsMap;

    //! Map of #hits and steps required to reach the word
    map< unsigned int, unsigned int > steps;

    //! Array storing actual value of hits at each slot
    int hitsArr[table_size];

    //! Initiliaze each slot with -1 (i.e. no hit yet)
    for( i = 0; i < table_size; i++ )
      hitsArr[i] = -1;

    //! Get hash value from hash function and increment corresponding index
    for( iter = words.begin(); iter != words.end(); ++iter ) {
      if( j == 1 )
        hashVal = hashFn1( *iter, table_size );
      else
        hashVal = hashFn2( *iter, table_size );
      hitsArr[hashVal]++;
    }

    //! Construct the map b/w hits and number of slots corresponding to those
    for( i = 0; i < table_size; i++ ) {
      //! If empty slot, skip
      if( hitsArr[i] == -1 )
        continue;

      it = hitsMap.find( hitsArr[i] );
      //! If #hits exists in map, increment its count
      if( it != hitsMap.end() )
        it->second++;
      //! Else insert the pair with #slots=1 into the map
      else
        hitsMap.insert( make_pair( hitsArr[i], 1 ) );
    }

    cout << "Hash function #" << j << ":\n#hits\t#slots receiving the #hits\n";
    for( it = hitsMap.begin(); it != hitsMap.end(); ++it )
      cout << it->first << "\t" << it->second << endl;

    //! Construct map of #steps required for every hit starting in a reverse dir
    numSteps = 0;
    for( rit = hitsMap.rbegin(); rit != hitsMap.rend(); ++rit ) {
      if( !rit->first )
        break;

      numSteps += rit->second;
      steps.insert( make_pair(rit->first, numSteps) );
    }

    //! Calculate the average number of steps required
    float avgSteps = 0.0;
    for( it = steps.begin(); it != steps.end(); ++it )
      avgSteps += it->first * it->second;

    avgSteps /= num_words;
    cout << "\nAverage number of steps in a successful search = "
         << avgSteps << endl;

    rit = hitsMap.rbegin();
    cout << "Maximum number of steps needed to find a word  = "
         << rit->first << endl << endl;
  }

  return 0;
}

/** Input params: String to find hash value for and hash-table size
 *  Return param: Hash value of the string passed.
 *  Description : Hash function 1.
 *
 *  Source: https://stackoverflow.com/a/8317622
 */
unsigned int hashFn1( string str, const unsigned int tableSize ) {
  unsigned int hash = 37;   //! a prime
  unsigned int A    = 59;   //! another prime
  unsigned int B    = 73;   //! yet another prime

  for( char &c : str )
    hash = (hash * A) ^ ((unsigned int) c * B);

  return (hash % tableSize); // or return h % C;
}

/** Input params: String to find hash value for and hash-table size
 *  Return param: Hash value of the string passed.
 *  Description : Hash function 2.
 *
 *  Source: https://stackoverflow.com/a/107657
 */ 
unsigned int hashFn2( string str, const unsigned int tableSize ) {
  unsigned int hash = 0;

  for( char &c : str )
    hash = hash * 101 + (unsigned int) c;

  return (hash % tableSize);
}
