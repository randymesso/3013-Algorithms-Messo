///////////////////////////////////////////////////////////////////////////////
//
// Author:           Randy Messo
// Email:            randymesso@gmail.com
// Label:            P01
// Title:            Array Based Stack Code
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       Taking a stack and resizing it in order to keep at least 10 spaces available
//       as well as shrinking the stack when the amount inside gets too small
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>


using namespace std;
/** 
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack
{
private:
  int *A;                 // pointer to array of int's
  int top;                // top of stack 


public:
  double size;            // current max stack size
  int count = 0;          // count of times stack resizes
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
ArrayStack()
{
  size = 10;
  A = new int[size];
  top = -1;
}
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
ArrayStack(int s)
{
    size = s;
    A = new int[s];
    top = -1;
  }
/**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
bool Empty()
{
  return (top <= -1);
}
/**
  * Public bool: Full
  * 
  * Description:
  *      Check if the stack is full
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
bool Full()
{
  return (top >= size-1);
}


/**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
int Peek()
{
  if(!Empty())
  {
    return A[top];
  }
  return -99; // some sentinel value
// not a good solution
}
/**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value from the stack if the stack isn't empty. Afterwards  
  *      it checks if a stack resize is neccessary.
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
void Pop()
{
  if(!Empty())
  {
    top--;
  }
  CheckResize();
}

/**
  * Public bool: TooSmall
  * 
  * Description:
  *      Checks to see if the stack is too small
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      bool   : If the stack is too small then it will return true
  */
bool TooSmall()
{
  return (size > 10 && top <= size * 0.15);
}


/**
  * Public void: Print
  * 
  * Description:
  *      Prints out the stack starting from the 0th position
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void Print()
{
  for(int i=0;i<=top;i++)
  {
    cout<<A[i]<<" ";
  }
  cout<<endl;
} 

/**
  * Public void: CheckResize
  * 
  * Description:
  *      Checks to see if the stack is too full(by our standards) or if the 
  *      stack is too empty. If the stack is too full, then you double the size,
  *      if the stack is too empty then you cut the size in half. 
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void CheckResize()
{
  if(Full())
  {
    ContainerGrow();
    count++;
  }
  else if (TooSmall())
  {
    ContainerShrink();
    count++;
  }
}

/**
  * Public void Push
  * 
  * Description:
  *      Adds an integer which was infiled onto the stack
  * 
  * Params:
  *      int  : Value you want to add onto stack 
  * 
  * Returns:
  *      NULL
  */
void Push(int x)
{
  CheckResize();              // whenever you add a value, you must check if a 
  A[++top] = x;               // resize is neccessary
}
/**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Called when the stack has reached its limit. Grows the stack by multipling it by two
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void ContainerGrow()
{
  int newSize = size*2;       // double size of original
  int *B = new int[newSize];  // allocate new memory
  for(int i=0;i<size;i++)
  {                           // copy values to new array
    B[i] = A[i];
  }
  delete [] A;                // delete old array
  size = newSize;             // save new size
  A = B;                      // reset array pointer
  }

/**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Called when the stack needs to shrink once it reaches a certain point.
  *      This method shrinks the size of the stack by cutting it in half
  *
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void ContainerShrink()
{ 
  int newSize = size / 2;             // half size of original
  int *B = new int[newSize];          // allocate new memory
  for(int i=0;i< newSize;i++)
  {                                   // copy values to new array
    B[i] = A[i];
  }
  delete [] A;                        // delete old array
  size = newSize;                     // save new size
  A = B;                              // reset array pointer
  }

};
// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc,char* argv[]) 
{
  ofstream outfile;
  ifstream infile;
  outfile.open("output.txt");
  infile.open("input.txt");


  ArrayStack stack;


  int Num;                          // number being read from file
  int Max_Size = 0;                 // keeps track of the max stack size
  int Ending_Size;                  // keeps track of the ending stack size

 
  while(infile)                     // loop while the infile is open
  {
    infile >> Num;                  // read in the number 

    if (Num % 2 == 0)               // if the number is even, push onto stack
    {
      stack.Push(Num);
      if (Max_Size < stack.size)    // controls the max size so it incraments
      {
        Max_Size = stack.size;
      }
    }
    else                            // if the number is odd, pop the last even
    {
      stack.Pop();
    }
    Ending_Size = stack.size; 
  }
  
 //Output requirements

outfile << "########################################################\n";
outfile << "Assignment 4 - Resizing Stack\n";
outfile << "3013 CMPS\n";
outfile << "Randy Messo\n\n";
outfile << "Max Stack Size " << Max_Size <<endl;
outfile << "End Stack Size " << Ending_Size << endl;
outfile << "Stack Resized " << stack.count <<" Times\n";
outfile << "########################################################\n";
outfile.close();
return 0;
}
