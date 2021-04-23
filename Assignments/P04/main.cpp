/*****************************************************************************
*                    
*  Author:           Randy Messo
*  Email:            randymesso@gmail.com
*  Label:            P04
*  Title:            Processing in Linear Time
*  Course:           3013 algorithms
*  Semester:         Spring 2021
* 
*  Description:
*        Read in a file of dictionary words and create a trie tree out of them   *        Time how long it takes to do this. Then getch in character and pull up
*        the first 10 search results. Time how long it takes to do this too.
* 
*  Usage:
*        Type in a word to search for. Use backspace if neccessary. Type a 
*        capital z to quit the program.
* 
*  Files:            main.cpp
*                    dictionary.json
*                    getch.hpp
*                    termcolor.hpp
*                    timer.hpp
*****************************************************************************/

#include <iostream>
#include <time.h>
#include <chrono> 
#include "timer.hpp"
#include "getch.hpp"
#include <string>
#include <vector>
#include <fstream>
#include "termcolor.hpp"


using namespace std;

#define CHAR_SIZE 128

/**
 * Struct wordNode
 * 
 * Description:
 *      creates an object that is able to hold a word and a next pointer.
 * 
 * Public Methods:
 *      - wordNode()
 *
 * Private Methods:
 *      - None
 *    
 * 
 * Usage: 
 * 
 *     wordNode x; x is now an object that holds a word.              
 */

struct wordNode
{
  string word;
  wordNode* next;
  wordNode()
  {
    word = "";
    next = NULL;
  }
};

/**
 * Class ListStack
 * 
 * Description:
 *      creates a linked list of wordNodes
 * 
 * Public Methods:
 *      - ListStack()
 *      - [int] getSize
 *      - [void] AddNode
 *      - [void] PrintList
 *      - [vector<string>] FindWords
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *      Liststack x; x.AddNode[wordNode y];
 *      
 */

class ListStack
{
protected:
  wordNode* head;
  wordNode* root;
  wordNode* tail;
  wordNode* left;
  wordNode* right;
  int size;
public:;

  ListStack()                     //constructor
  {
    head = tail = root = NULL;
    left = right = NULL;
    size = 0;
  }

  /**
     * Public : getSize
     * 
     * Description:
     *      gets the size of the linked list;
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      [int] size   : the size of the linked list
     */
int getSize()
{
  return size;
}
  /**
     * Public : AddNode
     * 
     * Description:
     *      Add a wordNode onto the linked list
     * 
     * Params:
     *      [wordNode*]    :  A pointer to an object of the type wordNode
     * 
     * Returns:
     *      None
     */
  void AddNode(wordNode* letter)
  {
    if(head == NULL)
    {
      head = tail = letter;
    }
    else
    {
      tail->next = letter;
      tail = letter;
    }
    size++; 
  }
  /**
     * Public : FindWords
     * 
     * Description:
     *      Matches the word being typed to the linked list of dictionary words
     * 
     * Params:
     *      [string] substring    : the word that was read in
     * 
     * Returns:
     *      [vector<string>] matches   : a vector of the matches found
     */
  vector<string> FindWords(string substring) 
  {
    vector<string> matches; // to hold any matches
    wordNode* curr = head;
    int length;
    while (curr != NULL)
    {
      string temp = " ";
      temp = curr->word;
      length = substring.length();
      if (temp.substr(0,length)==substring)
      {
        matches.push_back(temp);
      }
      curr = curr->next;
    }
    return matches;
  }
  /**
     * Public : PringList
     * 
     * Description:
     *      Prints the linked list of wordNodes
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  void PrintList()
  {
    wordNode* curr = head;
    while (curr != NULL)
    {
      cout << curr->word << endl;
      curr = curr->next;
    }
  }
};

/**
 * struct Trie
 * 
 * Description:
 *      creates a trie tree
 * 
 * Public Methods:
 *      - void insert(string);
 *      - bool deletion(Trie*&, string);
 *      - bool search(string);
 *      - bool haveChildren(Trie const*);
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *      Trie();
 *      
 */


struct Trie
{
public:
    string words;
    bool isLeaf;
    Trie* character[CHAR_SIZE];
 
    // Constructor
    Trie()
    {
        this->isLeaf = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
        words = "";
    }
 
    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
};
 
// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        if (curr->character[key[i]] == nullptr) {
            curr->character[key[i]] = new Trie();
        }
 
        // go to the next node
        curr = curr->character[key[i]];
    }
 
    // mark the current node as a leaf
    curr->isLeaf = true;
}
 
// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    // return false if Trie is empty
    if (this == nullptr) {
        return false;
    }
 
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}
 
// Returns true if a given node has any children
bool Trie::haveChildren(Trie const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }
 
    return false;
}


int main() 
{
    ifstream infile;
    infile.open("dictionary.txt");
    char k;                         // holder for character being typed
    string word = "";               // var to concatenate letters to
    vector<string> LoadDictionary;  // array of word names
    vector<string> matches;         // any matches found in vector of words
    ListStack List;                 // and object of the words read in
    Timer T;                        // time the reading in of words
    Timer SecondTime;               // time the matching of words
    int Results;                    // the number of results found
    Trie *LoadWords = new Trie();
    Trie *FindWords = new Trie();

    T.Start();
    //Create a vector of the dictionary names
    while(!infile.eof())
    {
      string readWords;
      infile >> readWords;
      LoadDictionary.push_back(readWords);
    }
    while(!infile.eof())
    {
      string readWords;
      infile >> readWords;
      LoadWords->insert(readWords);
    }
    //Create the linked list from the vector of dictionary names
    
    for (int i = 0;i < LoadDictionary.size();i++)
    {
      wordNode* temp = new wordNode;
      string HoldWord = LoadDictionary[i];
      temp->word = HoldWord;
      List.AddNode(temp);
    }
    T.End();



    // print out how long it took to load the words file
    cout << T.Seconds() << " seconds to read in and create a trie tree" << endl;
    cout << T.MilliSeconds() << " millisecods to read in and create a trie tree" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') 
    {
        
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        cout << termcolor::yellow << "Current Substring: " << termcolor::reset;
        if ((int)k == 127) 
        {
            if (word.size() > 0) 
            {
                word = word.substr(0, word.size() - 1);
            }
        } 
        else 
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) 
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) 
            {
                k -= 32;
            }
            word += k; // append char to word
        }

        // Find any words in the array that partially match
        // our substr word
        SecondTime.Start();                   // start it
        matches = List.FindWords(word);
        SecondTime.End();                     // end the current timer
        Results = matches.size();             //number of 
        
        

        vector<string>FirstMatches(10);
        if ((int)k != 32) 
        { 
            // if k is not a space print it
            // make the text colorful
            cout << termcolor::on_bright_green << termcolor::red << word << endl << termcolor::reset;
            cout << Results << " words found in " << SecondTime.Seconds() << " seconds\n";
            //If else loop to pring out the order starting with the first position
            if (matches.size() > 10)
            {
              for(int i = 0; i < 10; i++)
              {
                cout << termcolor::cyan;
                FirstMatches[i] = matches[i];
                cout << FirstMatches[i] << " ";
                cout << termcolor::reset;
              }
            }
            else 
            {
              for (int i = 0; i < Results; i++)
              {
                cout << termcolor::cyan;
                FirstMatches[i] = matches[i];
                cout << FirstMatches[i] << " ";
                cout << termcolor::reset;
              }
            }
            cout << endl << endl;
        }

    }
  

    return 0;
}
