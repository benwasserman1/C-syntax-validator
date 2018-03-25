/*
Benjamin Wasserman
wasse114@mail.chapman.edu
Delimiter Syntax Checker

Purpose of this source file:

The purpose of this source file is to define some functions, and to run the program
in main. It also has a couple global objects declared. First off, it declares the
stack (starting by allocating 5 elements) There is also the global integer, lineTrack.
This variable tracks the line that the program is analyzing so it can tell the user about
the location of the error. See the comments above the functions for more specifics.
*/

#include <iostream>
#include <fstream>
#include "GenStack.h"

using namespace std;

int lineTrack = 0;
//int position = 0;
GenStack <char> q(5);

/*
The function expectedValue takes in a character, current, as a parameter and returns
an integer. It's called if the closed delimiter doesn't match the open one at the top
of the stack. Then it checks the stop of the stack to give the user specifics about the
error. The function exits the program if the error is found so that the user can fix
the problem. The program checks for errors with delimiters in a file. It checks only
for errors with (), {}, and []. The errors it checks for are unexpected closing delimiters,
closing brackets that don't match the opening bracket, and missing closing brackets.
*/
int expectedValue(char current){
  if (q.peek() == '{'){
    cout << "ERROR: line " << lineTrack <<  ". Expected '}' and found " << "'" << current << "'" << endl;
    exit(0);
  }
  else if (q.peek() == '['){
    cout << "ERROR: line " << lineTrack <<  ". Expected ']' and found " << "'" << current << "'" << endl;
    exit(0);
  }
  else if (q.peek() == '('){
    cout << "ERROR: line " <<  lineTrack <<  ". Expected ')' and found " << "'" << current << "'" << endl;
    exit(0);
  }
  return 0;
}

/*
The function findCharacters doesn't return any values, but it takes in 7 paremeters.
It takes in a string, line, which is the line of the file. It also takes in 6 paremeters
of type char. These are all the possible delimiters. The function starts by searching each line
for a delimiter. If the deilimter is open, it's pushed to the stack. If it's closed, then
the function checks if the stack is empty (making it an unexpected delimiter), checks if the
top element of the stack is the appropriate opening character, and if neither of those are true
it calls the function expectedValue.
*/
void findCharacters(string line, char parentheses, char set, char bracket, char closedParentheses, char closedSet, char closedBracket){

  int position = 0;
  while (position < line.size()){
    for (int i = 0; i < line.size(); ++i){
      if (line[i] == set){
        q.push(set);
        }
      else if (line[i] == parentheses){
        q.push(parentheses);
      }
      else if (line[i] == bracket){
        q.push(bracket);
      }
      else if (line[i] == closedSet){
        if (q.isEmpty()){
          cout << "ERROR: line " <<  lineTrack <<  ". Unexpected '" << closedSet << "'" << endl;
          exit(0);
        }
        else if (q.peek() == '{'){
          q.pop();
        }
        else{
          expectedValue(closedSet);
        }
      }
      else if (line[i] == closedParentheses){
        if (q.isEmpty()){
          cout << "ERROR: line " <<  lineTrack <<  ". Unexpected '" << closedParentheses << "'" << endl;
          exit(0);
        }
        else if (q.peek() == '('){
          q.pop();
        }
        else{
          expectedValue(closedParentheses);
        }
      }
      else if (line[i] == closedBracket){
        if (q.isEmpty()){
          cout << "ERROR: line " <<  lineTrack <<  ". Unexpected '" << closedBracket << "'" << endl;
          exit(0);
        }
        else if (q.peek() == '['){
          q.pop();
        }
        else{
          expectedValue(closedBracket);
        }
      }
      position++;
      }
    }
  }

/*
The function missingEnd takes in no parameters and returns no values. It is used
to check for extra closing delimiters at the end of the file. If there are characters
in q then there are extra closing delimters, so the function calls q.peek() to check this
and then prints out an error, pops that character, and exits the program to let the user
fix the problem.
*/
void missingEnd(){
  if (q.peek() == '['){
    cout << "ERROR: Reached end of file and expected ']'"  << endl;
    q.pop();
    exit(0);
  }
  else if (q.peek() == '{'){
    cout << "ERROR: Reached end of file and expected '}'"  << endl;
    q.pop();
    exit(0);
  }
  else if (q.peek() == '('){
    cout << "ERROR: Reached end of file and expected ')'"  << endl;
    q.pop();
    exit(0);
  }
}


/*
The function initFile doesn't return any values but takes in a string, the file
that the user wants to analyze as a parameter. initFile reads in the file line by
line, tracks the number of lines, and calls the function findCharacters. Once it hits
the end of the file, if the stack isn't empty it calls the function missingEnd(), since
there must be missing closing delimiters.
*/
void initFile(string file){
  string line;
  ifstream inFile;
  inFile.open(file);
  if (inFile.fail()){
    cerr << "Error opening the file" << endl;
    return;
  }
  while (true){
    if (inFile.eof()){
      if (!q.isEmpty()){
        missingEnd();
      }
      cout << "Reached the end of the file without any delimiter syntax errors" << endl;
      lineTrack = 0;
      break;
    }
    if (getline(inFile, line)){
      lineTrack++;
      //cout << line << endl;
      findCharacters(line, '(', '{', '[', ')', '}', ']');
    }
  }
  inFile.close();
}

/*
The function newFile doesn't return any values nor take in any paramters. It merely
asks the user if they would like to process another file. If they say yes, the function
calls initFile(). Otherwise, the program is exited.
*/
void newFile(){
  bool anotherFile = true;
  string file;
  string processFile;
  while (anotherFile){
    cout << "Would you like to process another file? Enter 'y' if so or anything other key to exit" << endl;
    cin >> processFile;
    if (processFile == "y"){
      string line;
      cout << "Enter the location of the file " << endl;
      cin >> file;
      initFile(file);
      }
    else{
      anotherFile = false;
      exit(0);
    }
  }
}

/*
This is the main function. It takes in two parameters. The first is the integer,
argc. This is for the number of arguments that are input by the user. The second, is the pointer
array for the actual argument that the user inputs. If they don't input a parameter, a
message is displayed letting them know this and then the program exits. If they do enter a paramter,
the 1st element is considered the file name and initFile() is called.
*/
int main(int argc, char** argv){
  bool anotherFile = true;
  string file;
  string processFile;
  if (argc > 1){
    string test = argv[1];
    initFile(test);
    newFile();
  }
  else{
    cout << "Enter the location of the file as a parameter" << endl;
  }
}
