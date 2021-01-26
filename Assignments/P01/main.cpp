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
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>

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
  int *A;           // pointer to array of int's
  int size;         // current max stack size
  int top;          // top of stack

public:
int capacity;
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
    capacity = size;
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
  *      Stack full?
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
  *      Returns top value and removes it from stack
  *
  * Params:
  *      NULL
  *
  * Returns:
  *      [int] top value if any
  */
  int Pop()
  {
    if(!Empty())
    {
      return A[top--];
    }

    return -99; // some sentinel value
                // not a good solution
  }

 /**
  * Public void: Print
  *
  * Description:
  *      Prints stack to standard out
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
  * Public bool: Push
  *
  * Description:
  *      Adds an item to top of stack
  *
  * Params:
  *      [int] : item to be added
  *
  * Returns:
  *      [bool] ; success = true
  */
  bool Push(int x)
  {
    if(Full())
    {
      ContainerGrow();
    }
    if(!Full())
    {
      A[++top] = x;
      return true;
    }

    return false;

  }

 /**
  * Public void: ContainerGrow
  *
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
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
    capacity = size;

    A = B;                      // reset array pointer

  }
  void ContainerShrink()
  {
    int newSize = size / 2;         // half size of original
    int *B = new int[newSize];      // allocate new memory

    for(int i=0;i<size;i++)
    {                               // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                    // delete old array

    size = newSize;                 // save new size
    capacity = size;

    A = B;                          // reset array pointer
  }
  // void CheckResize()
  // {
  //   ArrayStack A;
  //   if (A.Full())
  //   {
  //     A.ContainerGrow();
  //   }
  //   else if ()
  //   {

  //   }
  // }


};



// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char* argv[])
{
  ifstream infile;                  
  ofstream outfile;
  infile.open("input.txt");           // open up the infile to read data
  outfile.open("output.txt");         // open up outfile to store data

  ArrayStack stack; 


  int x = 0;                          // Hold value pushed in
  int count = 0;                      // Number of values in stack
  double size = 10.0;                 // size of stack
  int Stack_Resize;
  int Max_Size = 0;

  for (int i = 0; i<41; i++)
  {
    infile >> x;
    if (stack.capacity == count)
    {
      stack.ContainerGrow();
      if (stack.capacity > Max_Size)
      {
        Max_Size = stack.capacity;
      }
      Stack_Resize++;
      if((x % 2) == 0)
      {
        stack.Push(x);
        //outfile << x << " ";
        count = (count + 1);
      }
      else
      {
          stack.Pop();
          count=(count-1);
      }
    }
    else if(count / stack.capacity == .15)
    {
      stack.ContainerShrink();
      Stack_Resize++;
      if((x % 2) == 0)
      {
        stack.Push(x);
        //outfile << x << " ";
        count++;
      }
      else
      {
        stack.Pop();
        count--;
      }
    }
    else
    { 
      if(x % 2 == 0)
      {
        stack.Push(x);
        //outfile << x << " ";
        count=(count+1);
      }
      else
      { 
        stack.Pop();
        count=(count-1);
      }
    }
    
  }

  
  outfile << "*****************************************************\n";
  outfile << "Assignment 4 - Resizing Stack\n";
  outfile << "3013 CMPS\n";
  outfile << "Randy Messo\n\n";
  outfile << "Max Stack Size " << Max_Size << endl;
  outfile << "End Stack Size " << stack.capacity << endl;
  outfile << "Stack Resized " << Stack_Resize << " Times\n";
  outfile << "*****************************************************\n";
  printf("You have %d argument(s)\n", argc);


  return 0;
}
