/*****************************************************************************
*                    
*  Author:           Randy Messo
*  Email:            randymesso@gmail.com
*  Label:            P02
*  Title:            Processing in Linear Time
*  Course:           3013 algorithms
*  Semester:         spring 2021
* 
*  Description:
*        Read in a file of dictionary words and create a linked list of them.   *        Time how long it takes to do this. Then getch in character and pull up
*        the first 10 search results. Time how long it takes to do this too.
* 
*  Usage:
*        Type in a word to search for. Use backspace if neccessary. Type a 
*        capital z to quit the program.
* 
*  Files:            main.cpp
*                    dictionary.txt
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
 *      - [vector<string>] FindAnimals
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
  wordNode* tail;
  int size;
public:;

  ListStack()                     //constructor
  {
    head = NULL;
    tail = NULL;
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
     * Public : FindAnimals
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
  vector<string> FindAnimals(string substring) 
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


int main() 
{
    ifstream infile;
    infile.open("dictionary.txt");
    char k;                         // holder for character being typed
    string word = "";               // var to concatenate letters to
    vector<string> LoadDictionary;  // array of animal names
    vector<string> matches;         // any matches found in vector of animals
    ListStack List;                 // and object of the words read in
    Timer T;                        // time the reading in of words
    Timer SecondTime;               // time the matching of words
    int Results;                    // the number of results found

    T.Start();
    //Create a vector of the dictionary names
    while(!infile.eof())
    {
      string readWords;
      infile >> readWords;
      LoadDictionary.push_back(readWords);
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



    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and create a linked list" << endl;
    cout << T.MilliSeconds() << " millisecods to read in and create a linked list" << endl;

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

        // Find any animals in the array that partially match
        // our substr word
        SecondTime.Start();                   // start it
        matches = List.FindAnimals(word);
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
