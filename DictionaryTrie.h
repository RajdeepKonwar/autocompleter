/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Declaration of class DictionaryTrie's member functions required to
 perform insert and find operations using a user-defined TST back-end.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <algorithm>
#include <string>
#include <queue>
#include <vector>

class TSTNode {
public:
  bool          isWordNode;     //! Indicates node being a "word node"
  bool          markPredicted;  //! Indicates node being marked for prediction
  const char    label;          //! Letter stored in a node
  unsigned int  frequency;      //! Frequency of the word (stored at word nodes)

  TSTNode       *left;          //! Pointer to a node's left child in the TST
  TSTNode       *middle;        //! Pointer to a node's middle child in the TST
  TSTNode       *right;         //! Pointer to a node's right child in the TST
  TSTNode       *parent;        //! Pointer to a node's parent in the TST

  //! Default constructor
  TSTNode( const char &l );
};

class DictionaryTrie {
public:
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /** Insert a word with its frequency into the dictionary.
   *  Return true if the word was inserted, and false if it was not (i.e. it was
   *  already in the dictionary or it was invalid (empty string)
   */
  bool insert( std::string word, unsigned int freq );

  /* Return true if word is in the dictionary, and false otherwise */
  bool find( std::string word ) const;

  /** Return up to num_completions of the most frequent completions
   *  of the prefix, such that the completions are words in the dictionary.
   *  These completions should be listed from most frequent to least.
   *  If there are fewer than num_completions legal completions, this
   *  function returns a vector with as many completions as possible.
   *  If no completions exist, then the function returns a vector of size 0.
   *  The prefix itself might be included in the returned words if the prefix
   *  is a word (and is among the num_completions most frequent completions
   *  of the prefix)
   */
  std::vector< std::string > predictCompletions( std::string prefix,
                                                 unsigned int num_completions );

  /* Destructor */
  ~DictionaryTrie();

private:
  //! Root of the Ternary Search Tree
  TSTNode *root;

  //! Helper function for sorting vector of pairs by second in descending order
  static bool sortBySecDesc( const std::pair< std::string, unsigned int > &a,
                             const std::pair< std::string, unsigned int > &b );

  //! Does a postorder traversal, deleting nodes
  static void deleteAll( TSTNode *n );
};

#endif // DICTIONARY_TRIE_H
