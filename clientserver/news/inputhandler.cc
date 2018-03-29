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
  cout << "Enter name of newsgroup" << endl;
  cin >> ng;
  flags.push_back(42);
}
void Inputhandler::enterNGId(){
  cout << "Enter identification number of newsgroup"<< endl;
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
  cout << "Enter the article identification number"<< endl;
  cin >> articleId;
  flags.push_back(41);
}
void Inputhandler::enterGetArticle() {
  enterArticleId();
}

string Inputhandler::build(string in) {
  string input;
  for(char c : in) {
    input += " ";
    if(c == ' ') {
      input += "_";
    } else {
      input += c;
    }
  }
  return input;
}

// COM_END
void Inputhandler::listNG() {
  cout << "list" << endl;
  mh.sendCode(Protocol::COM_LIST_NG);
}
void Inputhandler::sendString(string in) {
  string input = build(in);
  mh.sendStringParameter(input);
}

void Inputhandler::sendInt(unsigned int in) {
  mh.sendIntParameter(in);
}
// string_p COM_END
void Inputhandler::createNG() {
  mh.sendCode(Protocol::COM_CREATE_NG);
  cout << "CNG" << endl;
  sendString(ng);
}
// num_p COM_END
void Inputhandler::deleteNG() {
  mh.sendCode(Protocol::COM_DELETE_NG);
  cout << "DNG" << endl;
  sendInt(ngId);
}
// num_p COM_END
void Inputhandler::listArticles() {
  mh.sendCode(Protocol::COM_LIST_ART);
  cout << "listA" << endl;
  sendInt(ngId);
}
// num_p string_p string_p string_p COM_END
void Inputhandler::createArticle() {
  mh.sendCode(Protocol::COM_CREATE_ART);
  cout << "CA" << endl;
  //NGId
  sendInt(ngId);
  //title
  sendString(title);
  //author
  sendString(author);
  //text
  sendString(text);
}
//  num_p num_p COM_END
void Inputhandler::deleteArticle() {
  mh.sendCode(Protocol::COM_DELETE_ART);
  cout << "DA" << endl;
  sendInt(ngId);
  sendInt(articleId);
}
// num_p num_p COM_END
void Inputhandler::getArticle() {
  mh.sendCode(Protocol::COM_GET_ART);
  cout << "GA" << ngId << endl;
  sendInt(ngId);
  sendInt(articleId);
}
