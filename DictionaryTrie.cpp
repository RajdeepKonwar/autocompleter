/**
 @author Rajdeep Konwar (A53225609)
 
 @date Oct 30 2017
 
 @section OVERVIEW
 Implementation of class DictionaryTries's member functions required to
 perform insert and find operations using a user-defined TST back-end.
 
 @section ASSIGNMENT NUMBER
 PA2
 */

#include "util.h"
#include "DictionaryTrie.h"

/** Input params: Constant character (a letter in our key)
 *  Return param: None
 *  Description : Default constructor for class TSTNode.
 *
 *  Creates a new node in the Ternary Search Tree
 */
TSTNode::TSTNode( const char &l ) : isWordNode(false), markPredicted(false),
                                    label(l), frequency(0), left(nullptr),
                                    middle(nullptr), right(nullptr),
                                    parent(nullptr) {}

/** Input params: None
 *  Return param: None
 *  Description : Default constructor for class DictionaryTrie.
 *
 *  Creates a new Dictionary that uses a Ternary Search Tree back end
 */
DictionaryTrie::DictionaryTrie() : root(nullptr) {}

/** Input params: Key to find (string)
 *  Return param: Boolean
 *  Description : Inserts a word in the dictionary.
 *
 *  Insert a word with its frequency into the dictionary. Returns true if the
 *  word was inserted, and false if it was not (i.e. it was already in the
 *  dictionary or it was invalid (empty string)
 */
bool DictionaryTrie::insert( std::string word, unsigned int freq ) {
  size_t pos        = 0;              //! Letter counter for word
  size_t len        = word.length();  //! Length of given word
  char letter       = word.at( pos ); //! Get first letter of word
  TSTNode *current  = root;           //! Start at the root
  TSTNode *newNode;                   //! Pointer holding new nodes

  //! Return false if key is invalid (empty string)
  if( word.empty() )
    return false;

  //! If tree is empty, add word as a vertical chain and return true
  if( root == nullptr ) {
    newNode = new TSTNode( letter );
    root    = newNode;
    current = newNode;
    for( pos = 1; pos < len; pos++ ) {
      letter  = word.at( pos );
      newNode = new TSTNode( letter );
      current->middle = newNode;
      newNode->parent = current;
      current = newNode;
    }

    current->isWordNode = true;
    current->frequency  = freq;
    return true;
  }

  while( current != nullptr ) {
    if( letter == current->label ) {
      //! If we are at the last letter of our word
      if( (letter == word.back()) && (pos == len - 1) ) {
        /** We legally traversed through the tree for every letter of key,
         *  simple label the end at which you end up as "word node", set
         *  its frequency to the one provided in the arguments and return true
         */
        if( !current->isWordNode ) {
          current->isWordNode = true;
          current->frequency  = freq;
          return true;
        }

        //! The word already exists in our tree
        else {
          /** If a duplicate word inserted has a different frequency, update
           *  the frequency to the larger frequency but return false
           */
          if( current->frequency < freq ) {
            current->frequency = freq;
            return false;
          }

          /** If frequency of duplicate word is less than current node's
           *  frequency, don't update frequency; simply return false
           */
          else {
            return false;
          }
        }
      } else {
        /** Traverse down the middle if middle child exists and focus on
         *  the next letter of the key
         */
        if( current->middle != nullptr ) {
          current = current->middle;
          letter  = word.at( ++pos );
        }

        /** If you run into a case where you want to traverse down to a middle
         *  child, but no such child exists, simply create middle children
         *  labeled by each of the remaining letters of key, update frequency
         *  and return true
         */
        else {
          for( pos = pos + 1; pos < len; pos++ ) {
            letter  = word.at( pos );
            newNode = new TSTNode( letter );
            current->middle = newNode;
            newNode->parent = current;
            current = newNode;
          }

          current->isWordNode = true;
          current->frequency  = freq;
          return true;
        }
      }
    }

    else if( letter < current->label ) {
      /** If you are performing the tree traversal and run into a case where you
       *  want to traverse left, but no such child exists, create a new left
       *  child labeled by the current letter of key, and then create middle
       *  children labeled by each of the remaining letters of key
       */
      if( current->left == nullptr ) {
        newNode = new TSTNode( letter );
        current->left   = newNode;
        newNode->parent = current;
        current = newNode;
        for( pos = pos + 1; pos < len; pos++ ) {
          letter  = word.at( pos );
          newNode = new TSTNode( letter );
          current->middle = newNode;
          newNode->parent = current;
          current = newNode;
        }

        current->isWordNode = true;
        current->frequency  = freq;
        return true;
      }

      //! Traverse left
      else {
        current = current->left;
      }
    }

    else if( current->label < letter ) {
      /** If you are performing the tree traversal and run into a case where you
       *  want to traverse right, but no such child exists, create a new right
       *  child labeled by the current letter of key, and then create middle
       *  children labeled by each of the remaining letters of key
       */
      if( current->right == nullptr ) {
        newNode = new TSTNode( letter );
        current->right  = newNode;
        newNode->parent = current;
        current = newNode;
        for( pos = pos + 1; pos < len; pos++ ) {
          letter  = word.at( pos );
          newNode = new TSTNode( letter );
          current->middle = newNode;
          newNode->parent = current;
          current = newNode;
        }

        current->isWordNode = true;
        current->frequency  = freq;
        return true;
      }

      //! Traverse right
      else {
        current = current->right;
      }
    }
  }

  return false;
}

/** Input params: Key to find (string)
 *  Return param: Boolean
 *  Description : Finds a word from the dictionary.
 *
 *  Returns true if word is in the dictionary, and false otherwise
 */
bool DictionaryTrie::find( std::string word ) const {
  unsigned int pos  = 0;              //! Letter counter in word
  char letter       = word.at( pos ); //! Get first letter of word
  TSTNode *current  = root;           //! Start at the root

  //! Return false if key is invalid (empty string)
  if( word.empty() )
    return false;

  while( current != nullptr ) {
    /** If letter is less than node's label: If node has a left child,
     *  traverse down to node's left child. Otherwise, we have failed
     */
    if( letter < current->label ) {
      current = current->left;
    }

    /** If letter is greater than node's label: If node has a right child,
     *  traverse down to node's right child. Otherwise, we have failed
     */
    else if( current->label < letter ) {
      current = current->right;
    }

    /** If letter is equal to node's label: If letter is the last letter of key
     *  and if node is labeled as a "word node," we have successfully found key
     *  in our Ternary Search Tree; if not, we have failed. Otherwise, if node
     *  has a middle child, traverse down to node's middle child and set letter
     *  to the next character of key; if not, we have failed
     */
    else if( letter == current->label ) {
      if( (letter == word.back()) && (pos == word.length() - 1) ) {
        if( current->isWordNode )
          return true;
        else
          return false;
      } else {
        if( current->middle != nullptr ) {
          current = current->middle;
          letter  = word.at( ++pos );
        } else {
          return false;
        }
      }
    }
  }

  return false;
}

/** Input params: Two vectors to compare
 *  Return param: Boolean
 *  Description : Helper function to sort by second in descending order.
 *
 *  Returns true if first vector's second is larger than the other's second
 */
bool DictionaryTrie::sortBySecDesc(
                            const std::pair< std::string, unsigned int > &a,
                            const std::pair< std::string, unsigned int > &b ) {
  return (a.second > b.second);
}

/** Input params: A prefix string and number of completions desired
 *  Return param: Vector of predicted words
 *  Description : AutoCompletes words from a given prefix.
 *
 *  Returns up to num_completions of the most frequent completions of the
 *  prefix, such that the completions are words in the dictionary.
 *  These completions should be listed from most frequent to least.
 *  If there are fewer than num_completions legal completions, this function
 *  returns a vector with as many completions as possible. If no completions
 *  exist, then the function returns a vector of size 0. The prefix itself might
 *  be included in the returned words if the prefix is a word (and is among the
 *  num_completions most frequent completions of the prefix)
 */
std::vector< std::string > DictionaryTrie::predictCompletions(
                                                std::string prefix,
                                                unsigned int num_completions ) {
  unsigned int i, count = 0, pos  = 0;  //! Various counters
  std::string path                = ""; //! String holding found words

  std::queue< TSTNode * > predictQ;     //! Queue to store nodes for BFS
  std::vector< std::string > words;     //! Vector of predictions
  std::vector< std::pair< std::string, unsigned int > >
                          legalWords;   /** Vector of pairs holding all legal
                                         *  words along with their frequency
                                         */

  TSTNode *current  = root;             //! Start at the root
  TSTNode *start, *curr, *tmp;          //! Sundry pointers for autocompletion

  //! Return empty vector along with a message if prefix is empty string
  if( prefix.empty() ) {
    std::cout << "Invalid​ Input.​​ Please retry​ with​ correct input." << std::endl;
    return words;
  }

  //! Get first letter of prefix
  char letter = prefix.at( pos );

  while( current != nullptr ) {
    /** If letter is less than node's label: If node has a left child, traverse
     *  down to node's left child.
     */
    if( letter < current->label ) {
      current = current->left;
    }

    /** If letter is greater than node's label: If node has a right child,
     *  traverse down to node's right child.
     */
    else if( current->label < letter ) {
      current = current->right;
    }

    /** If letter is equal to node's label: If letter is the last letter of
     *  prefix, start from the next node and do a Breadth First Search (BFS)
     *  to find all prediction words and return them in a vector depending
     *  on edge cases and checklist.
     */
    else if( letter == current->label ) {
      if( (letter == prefix.back()) && (pos == prefix.length() - 1) ) {
        //! Only if we are at at word node and the word hasn't been marked
        if( current->isWordNode && !current->markPredicted ) {
          current->markPredicted = true;
          count++;
          legalWords.push_back( std::make_pair( prefix, current->frequency ) );
        }

        if( current->middle != nullptr ) {
          //! Push starting node into the queue
          start = current->middle;
          predictQ.push( start );

          while( !predictQ.empty() ) {
            //! Get the first element in the queue
            curr = predictQ.front();

            //! Only for words which haven't been marked as found earlier
            if( curr->isWordNode && !curr->markPredicted ) {
              curr->markPredicted = true;
              tmp = curr;
              std::string app( 1, tmp->label );
              path += app;

              /** Once we find a word-node, start at the word-node and do a
               *  reverse traversal up the tree untill we reach the start node.
               *  If the current node is the middle child of its parent, we add
               *  the letter to our string path otherwise just traverse upward
               */
              while( tmp != start ) {
                if( tmp == tmp->parent->middle ) {
                  tmp = tmp->parent;
                  std::string app( 1, tmp->label );
                  path += app;
                } else {
                  tmp = tmp->parent;
                }
              }

              /** Once string path is formed, reverse it and add with prefix
               *  to form a legal word and push it into our vector of pairs
               */
              std::reverse( path.begin(), path.end() );
              path = prefix + path;
              count++;
              legalWords.push_back( std::make_pair( path, curr->frequency ) );

              //! Reset string path to be null for next word search
              path = "";
            }

            //! pop node curr from front of queue
            predictQ.pop();

            //! visit curr; for each of curr's children, push onto queue
            if( curr->left != nullptr )
              predictQ.push( curr->left );
            if( curr->middle != nullptr )
              predictQ.push( curr->middle );
            if( curr->right != nullptr )
              predictQ.push( curr->right );
          }

          /** Once all legal words are found and pushed onto vector, break loop
           *  by setting current pointer to be nullptr
           */
          current = nullptr;
        }

        //! If there is no legal word in the tree, return empty vector
        else {
          return words;
        }
      } else {
        if( current->middle != nullptr ) {
          current = current->middle;
          letter  = prefix.at( ++pos );
        } else {
          return words;
        }
      }
    }

    //! Prefix contains non-dictionary characters; return empty vector
    else {
      std::cout << "Invalid​ Input.​​ Please retry​ with​ correct input."
                << std::endl;
      return words;
    }
  }

  /** Sort the vector of pairs by second (i.e. frequency) in descending order
   *  using our sort helper function
   */
  std::stable_sort( legalWords.begin(), legalWords.end(), sortBySecDesc );

  //! Populate the return vector with min(count, num_completions)
  for( i = 0; i < std::min(count, num_completions); i++ )
    words.push_back( (legalWords[i]).first );

  return words;
}

/** Input params: None
 *  Return param: None
 *  Description : Default destructor.
 *
 *  Deletes every node in the TST
 */
DictionaryTrie::~DictionaryTrie() {
  //! delete all nodes of the tree
  deleteAll( root );
}

/** Input params: A node in the tree
 *  Return param: None
 *  Description : Does a postorder traversal, deleting all nodes in the BST.
 */
void DictionaryTrie::deleteAll( TSTNode *n ) {
  //! start at node n (call with root initially)
  TSTNode *current = n;

  if( current == nullptr )
    return;

  //! recursively call deleteAll for all left children
  if( current->left != nullptr )
    deleteAll( current->left );

  //! recursively call deleteAll for all middle children
  if( current->middle != nullptr )
    deleteAll( current->middle );

  //! recursively call deleteAll for all right children
  if( current->right != nullptr )
    deleteAll( current->right );

  //! memory deallocation
  delete current;
  current = nullptr;

  return;
}
