/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of benchdict program to benchmark and compare the different
 find operation speed in different dictionaries, namely BST, Hashtable and Trie.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include <iostream>
#include <fstream>
#include <string>
#include "util.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"

using namespace std;

int main( int i_argc, char** i_argv ) {
  //! Check for Arguments
  if( i_argc != 5 ) {
    cout << "Invalid number of arguments." << endl
     << "Usage: ./benchdict <min_size> <step_size> <num_iterations> <dictfile>."
     << std::endl;
    return -1;
  }

  //! Variable declarations
  long long findAvg;
  Timer timeObj;
  unsigned int i, j, num_runs = 1000;

  //! Command-line arguments
  unsigned int min_size       = atoi( i_argv[1] );
  unsigned int step_size      = atoi( i_argv[2] );
  unsigned int num_iterations = atoi( i_argv[3] );

  vector< string >            words;
  vector< string >::iterator  wit;

  ifstream dictfile;
  dictfile.open( i_argv[4] );

  //! Check if input file was actually opened
  if( !dictfile.is_open() ) {
    std::cout << "Invalid input file. No file was opened. Please try again."
              << std::endl;
    return -1;
  }

  //! Case 1: DictionaryBST class
  cout << "Benchmarking DictionaryBST class" << endl;

  for( i = 0; i < num_iterations; i++ ) {
    //! Dictionary object
    DictionaryBST *dictBST = new DictionaryBST;

    // Reset istream to start of dictionary file at start of each iteration
    dictfile.clear();
    dictfile.seekg( 0, ios::beg );

    //load min_size+i*step_size words from beginning of dictionary file
    Utils::load_dict( *dictBST, dictfile, min_size + i * step_size );

    //! Load next 100 words from dictionary
    Utils::load_vector( words, dictfile, 100 );

    findAvg = 0;
    for( j = 0; j < num_runs; j++ ) {
      //! Compute time to find those 100 words in the dictionary object
      timeObj.begin_timer();
      for( wit = words.begin(); wit != words.end(); ++wit )
        (*dictBST).find( *wit );
      findAvg += timeObj.end_timer();
    }

    //! Taking average time of all the runs
    findAvg /= num_runs;
    cout << (min_size + i * step_size) << "\t" << findAvg << endl;

    //! Memory deallocation
    delete dictBST;
  }

  //! Case 2: DictionaryHashtable class
  cout << endl << "Benchmarking DictionaryHashtable class" << endl;

  for( i = 0; i < num_iterations; i++ ) {
    //! Dictionary object
    DictionaryHashtable *dictHash = new DictionaryHashtable;

    // Reset istream to start of dictionary file at start of each iteration
    dictfile.clear();
    dictfile.seekg( 0, ios::beg );

    //load min_size+i*step_size words from beginning of dictionary file
    Utils::load_dict( *dictHash, dictfile, min_size + i * step_size );

    //! Load next 100 words from dictionary
    Utils::load_vector( words, dictfile, 100 );

    findAvg = 0;
    for( j = 0; j < num_runs; j++ ) {
      //! Compute time to find those 100 words in the dictionary object
      timeObj.begin_timer();
      for( wit = words.begin(); wit != words.end(); ++wit )
        (*dictHash).find( *wit );
      findAvg += timeObj.end_timer();
    }

    //! Taking average time of all the runs
    findAvg /= num_runs;
    cout << (min_size + i * step_size) << "\t" << findAvg << endl;

    //! Memory deallocation
    delete dictHash;
  }

  //! Case 3: DictionaryTrie class
  cout << endl<< "Benchmarking DictionaryTrie class" << endl;

  for( i = 0; i < num_iterations; i++ ) {
    //! Dictionary object
    DictionaryTrie *dictTrie = new DictionaryTrie;

    // Reset istream to start of dictionary file at start of each iteration
    dictfile.clear();
    dictfile.seekg( 0, ios::beg );

    //load min_size+i*step_size words from beginning of dictionary file
    Utils::load_dict( *dictTrie, dictfile, min_size + i * step_size );

    //! Load next 100 words from dictionary
    Utils::load_vector( words, dictfile, 100 );

    findAvg = 0;
    for( j = 0; j < num_runs; j++ ) {
      //! Compute time to find those 100 words in the dictionary object
      timeObj.begin_timer();
      for( wit = words.begin(); wit != words.end(); ++wit )
        (*dictTrie).find( *wit );
      findAvg += timeObj.end_timer();
    }

    //! Taking average time of all the runs
    findAvg /= num_runs;
    cout << (min_size + i * step_size) << "\t" << findAvg << endl;

    //! Memory deallocation
    delete dictTrie;
  }

  //! Close the dictionary file
  dictfile.close();

  return 0;
}
