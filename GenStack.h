#include <iostream>
#include <exception>

using namespace std;

/*
This is my exception class used for the pop and a peek operations on an empty stack
*/
class Empty_Stack : public exception{
public:
  const char* what() const throw(){
    return "Stack is empty";
  }
};


/*
This is the templated class that defines my stack implementation. The
stack is resized with 5 extra potential elements if the stack is full
when push() is called. Additionally, an error is thrown when the stack
is empty and pop() or peek() are called.
*/
template <typename E> class GenStack
{
public:

  int top;
  int max;
  E init;

  E *myArray;
  E *newArray;

  //Default constructor
  GenStack(){
    max = 1;
    top = -1;
    myArray = new E[max];
  }

  //Constructor
  GenStack(int maxsize){
    max = maxsize;
    top = -1;
    myArray = new E[maxsize];
  }

  //Destructor
  ~GenStack(){
    cout << "Object destroyed" << endl;
    delete [] myArray;
  }

  /*
  CopyArray returns no values but it takes in 4 paremeters. It takes in newSize,
  an integer that defines the new size of the stack. It also takes in max, an
  integer that represents the previous size of the stack. Finally, it takes in
  init - the value of the new space that we want to initialize to, and data - the
  element that was attempted to be pushed when the stack was full. The function creates
  a new array, copies the content over from the old array, initializes the new values for
  the extra spaces, deallocates the previous array, and then reassigns that array to the new one.
  Lastly, it calls push again with the element that was previously attempted to be pushed, since
  the stack is no longer full.
  */
  void copyArray(int newSize, int max, E init, E data){
    newArray = new E[newSize];
    for (int i = 0; (i < max) && (i<newSize); ++i){
      newArray[i] = myArray[i];
    }
    for (int j = max; j < newSize; ++j){
      newArray[j] = init;
    }
    delete [] myArray;
    myArray = newArray;
    push(data);
  }

  /*
  Push returns no values and takes in data, of type E, as a parameter. It checks
  to see if the stack is full, and if it is copyArray() is called so that the array
  can be resized. Otherwise, data is pushed on to the stack.
  */
  void push(E data){
    if (isFull()){
      int newSize = max + 5;
      //cout << "Stack is full" << endl;
      copyArray(newSize, max, init, data);
    }
    else{
      myArray[++top] = data;
    }
  }

  /*
  Pop returns a value of type E (specified in it's instantiation). It checks
  to see if the stack is empty. If it is empty, an exception is thrown. Otherwise,
  the top element is returned, and removed from the stack.
  */
  E pop(){
    try{
      if (isEmpty()){
        Empty_Stack e;
        throw e;
      }
      else{
        return myArray[top--];
      }
    }
    catch (exception& e){
      cout << e.what();
    }
    return myArray[top--];
  }

  /*
  Peek returns a value of type E (specified in it's instantiation), and takes in
  no parameters. if the stack is empty, an exception is thrown. Otherwise, the top
  element is returned from the stack.
  */
  E peek(){
    try{
      if (isEmpty()){
        Empty_Stack e;
        throw e;
      }
      else{
        return myArray[top];
      }
    }
    catch (exception& e){
      cout << e.what();
    }
    return myArray[top];
  }

  /*
  IsFull returns an integer, and takes in no parameters. If the stack is full,
  it adds 5 to the value of max (since the array will be 5 elements larger), and returns
  1 (or true). Otherwise, the function returns 0 (or false).
  */
  int isFull(){
    if (top == max-1){
      max +=5;
      return 1;
    }
    else{
      return 0;
    }
  }

  /*
  IsEmpty returns an integer and takes no parameters. It merely returns a boolean
  expression to check if stack is empty. If it is, 1 (or true) is returned. Otherwise,
  0 (or false) is returned.
  */
  int isEmpty(){
    return (top == -1);
  }
};
