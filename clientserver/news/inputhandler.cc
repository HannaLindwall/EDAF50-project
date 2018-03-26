#include "inputhandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;

//string_p: PAR_STRING N char1 char2 ... charN // N is the number of characters
//num_p: PAR_NUM N // N is the number


void Inputhandler::enterNG(){
  cout << "Enter name of newsgroup";
  cin >> ng;
  flags.push_back(42);
}
void Inputhandler::enterNGId(){
  cout << "Enter identification number of newsgroup";
  cin >> ngId;
  flags.push_back(41);
}
void Inputhandler::enterListArticles(){
  enterNGId();
}
void Inputhandler::enterCreateArticle() {
  enterNGId();
  cout << "Enter the article title" << endl;
  std::getline(cin, title);
  flags.push_back(42);
  cout << "Enter the author" << endl;
  std::getline(cin, author);
  flags.push_back(42);
  cout << "Enter text, end with #";
  string temp;
  while(cin >> temp && temp != "#")
    text += " " + temp;
  flags.push_back(42);
}
void Inputhandler::enterArticleId() {
  enterNGId();
  cout << "Enter the article identification number";
  cin >> articleId;
  flags.push_back(41);
}
void Inputhandler::enterGetArticle() {
  enterArticleId();
}

// COM_END
string Inputhandler::listNG() {
  cout << "list" << endl;
  string input = to_string(action);
  input += " 8";
  return input;
}
// string_p COM_END
string Inputhandler::createNG() {
  cout << "CNG" << endl;
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ng.length());
  for(char c : ng) {
    input += " ";
    if(c == ' ') {
      input += "_";
    } else {
      input += c;
    }
  }
  input += " 8";
  return input;

}
// num_p COM_END
string Inputhandler::deleteNG() {
  cout << "DNG" << endl;
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  input += " 8";
  return input;

}
// num_p COM_END
string Inputhandler::listArticles() {
  cout << "listA" << endl;
  return deleteNG();

}
// num_p string_p string_p string_p COM_END
string Inputhandler::createArticle() {
  cout << "CA" << endl;
  //action
  string input = to_string(action);
  //NGId
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  //title
  input += " " + to_string(flags[1]);
  input += " " + to_string(title.length());
  for(char c : ng) {
    input += " ";
    if(c == ' ') {
      input += "_";
    } else {
      input += c;
    }
  }
  //author
  input += " " + to_string(flags[2]);
  input += " " + to_string(author.length());
  for(char c : author) {
    input += " ";
    if(c == ' ') {
      input += "_";
    } else {
      input += c;
    }
  }
  //text
  input += " " + to_string(flags[3]);
  input += " " + to_string(text.length());
  for(char c : ng) {
    input += " ";
    if(c == ' ') {
      input += "_";
    } else {
      input += c;
    }
  }
  input += " 8";
  return input;
}
//  num_p num_p COM_END
string Inputhandler::deleteArticle() {
  cout << "DA" << endl;
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  input += " " + to_string(flags[1]);
  input += " " + to_string(articleId);
  input += " 8";
  return input;

}
// num_p num_p COM_END
string Inputhandler::getArticle() {
  cout << "GA" << endl;
  return deleteArticle();

}
