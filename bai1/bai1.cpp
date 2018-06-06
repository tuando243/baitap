#include <iostream>
#include <stack>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

string brackets = "(())(())))()";
stack<char> bracketStack;
int status[200] = {0};
int count = 0;

bool checkPushBracketStack(char bracket);
void readFileData();
void writeFile(string data);
string convertIntToString(int val);
void resetStatus();

int main(){
  readFileData();

  for(int i = 0; i < brackets.length(); i++){
    if(checkPushBracketStack(brackets[i])){
      bracketStack.push(brackets[i]);
      if(brackets[i] == '(') status[i] = -1;
      else status[i] = 1;
    }
    else{
      bracketStack.pop();
      resetStatus();
    }
  }

  writeFile(convertIntToString(bracketStack.size()));

  if(bracketStack.size() != 0){
    cout <<"Day ngoac khong dung" <<endl;
    string data;
    for(int i = 0; i < 200; i++){
      if(status[i] == -1){
        data = ")\t" + convertIntToString(i + count);
        writeFile(data);
        count++;
      }
      else if(status[i] == 1){
        data = "(\t" + convertIntToString(i + count - 1);
        writeFile(data);
        count++;
      }
    }
  }
  else{
    cout <<"Day ngoac dung" <<endl;
  }
  return 0;
}

bool checkPushBracketStack(char bracket){
  if(bracketStack.empty() ||
    bracketStack.top() == ')' ||
    bracketStack.top() == '(' && bracket == '(')
    return true;
  return false;
}

void readFileData(){
  ifstream inFile;
  inFile.open("BRACKET_INT");
  if(inFile){
    inFile >> brackets;
  }
  else{
    cout <<"Cannot read file!" <<endl;
  }
  inFile.close();
  return;
}

void writeFile(string data){
  ofstream outFile;
  outFile.open("BRACKET_OUT", ios::app);
  outFile <<data <<endl;
  outFile.close();
  return;
}

string convertIntToString(int val){
  string outString;
  stringstream ss;
  ss << val;
  outString = ss.str();
  return outString;
}

void resetStatus(){
  for(int i = 199; i >= 0; i--)
    if(status[i] != 0){
      status[i] = 0;
      return;
    }
}
