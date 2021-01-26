/****************************************************************
*                    
*  Author:           Randy Messo
*  Email:            Randymesso@gmail.com
*  Label:            A03
*  Title:            Commenting C++ Code
*  Course:           CMPS 3013 
*  Semester:         Spring 2021
* 
*  Description:
*        This program is used to learn how to properly comment code in c++
* 
*  Usage:
*        Used to exemplify a knowledge of how to comment a block of code
* 
*  Files:       
*        main.cpp    : driver program 
*****************************************************************/
#include <iostream>

using namespace std;

int A[100];
/**
 *  Node
 * 
 * Description:
 *      This struct sets up the use of nodes during the program
 * 
 * Public Methods:
 *      Node()            
 *      Node(int n)        
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 * 
 *      Node()             Default constructor
 *      Node(int n)        Accepts an integer perameter
 *      
 */
struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      Programed to create a linked list. This could be done through pushing vales on, popping them off, while keeping up with the head and tail. 
 * 
 * Public Methods:
 *                 List()
 *     void        Push(int val)
 *     void        Insert(int val)
 *     void        PrintTail()
 *     int         Pop()
 *     string      Print()
 * Private Methods:
 *     N/A
 * 
 * Usage: 
 * 
 *      Push(int val)        Insert the value that you want to add
 *      Insert(int val)      Inser the value that is being inserted
 *      PrintTail()          Print out value pointed to by the tail
 *      Pop()                Remove a value from the list
 *      Print()              Call to print out the whole list
 *
 */

class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }
/**
  * Public void: Push
  * 
  * Description:
  *      Add a certain values on to the list
  * 
  * Params:
  *      Integer named val
  * 
  * Returns:
  *      NULL
  */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
/**
  * Public void: Inseert
  * 
  * Description:
  *      Insert a value in a specific spot
  * 
  * Params:
  *     Integer named val
  * 
  * Returns:
  *      NULL
  */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }
/**
  * Public void: PrintTail
  * 
  * Description:
  *      Print out the value pointed to by the tail
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void PrintTail() {
        cout << Tail->x << endl;
    }
/**
  * Public string Pint
  * 
  * Description:
  *      Prints out the contents of the list
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      The fully printed out list
  */
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

/**
  * Public int Pop
  * 
  * Description:
  *      Remove an item form the stack 
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      integer 0
  */
    int Pop() {
        Size--;
        return 0; //
    }
/**
  * Public List Operator+
  * 
  * Description:
  *      To minimize the amount of things in the list
  * 
  * Params:
  *      Constant reference to the right hand side
  * 
  * Returns:
  *      An object of the structure type list
  */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
/**
  * Public int operator[]
  * 
  * Description:
  *      Checking the bounds of the index to make sure it stays in line
  * 
  * Params:
  *      Integer named index
  * 
  * Returns:
  *      Integer node pointing to x 
  */
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
