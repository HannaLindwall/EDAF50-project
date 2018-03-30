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
}
void Inputhandler::enterNGId(){
  cout << "Enter identification number of newsgroup"<< endl;
  cin >> ngId;
}
void Inputhandler::enterListArticles(){
  enterNGId();
}
void Inputhandler::enterCreateArticle() {
  enterNGId();
  cout << "Enter the article title" << endl;
  std::getline(cin, title);
  cout << "Enter the author" << endl;
  std::getline(cin, author);
  cout << "Enter text, end with #";
  string temp;
  while(cin >> temp && temp != "#")  {
    text += " " + temp;
  }
}
void Inputhandler::enterArticleId() {
  enterNGId();
  cout << "Enter the article identification number"<< endl;
  cin >> articleId;
}
void Inputhandler::enterGetArticle() {
  enterArticleId();
}

string Inputhandler::build(string in) {
  string input;
  for(char c : in) {
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
  cout << "CNG" << endl;
  mh.sendCode(Protocol::COM_CREATE_NG);
  sendString(ng);
}
// num_p COM_END
void Inputhandler::deleteNG() {
  cout << "DNG" << endl;
  mh.sendCode(Protocol::COM_DELETE_NG);
  sendInt(ngId);
}
// num_p COM_END
void Inputhandler::listArticles() {
  cout << "listA" << endl;
  mh.sendCode(Protocol::COM_LIST_ART);
  sendInt(ngId);
}
// num_p string_p string_p string_p COM_END
void Inputhandler::createArticle() {
  cout << "CA" << endl;
  mh.sendCode(Protocol::COM_CREATE_ART);
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
  cout << "DA" << endl;
  mh.sendCode(Protocol::COM_DELETE_ART);
  sendInt(ngId);
  sendInt(articleId);
}
// num_p num_p COM_END
void Inputhandler::getArticle() {
  cout << "GA" << ngId << endl;
  mh.sendCode(Protocol::COM_GET_ART);
  sendInt(ngId);
  sendInt(articleId);
}

void Inputhandler::readEmpty(istream& iss) {
  unsigned char c;
  iss >> c;
  iss >> c;
  iss >> c;
}

string Inputhandler::translateListNG(string reply) {
  cout << "list" << endl;
  unsigned char r;
  string ngs;
  istringstream iss(reply);
  //20
  readEmpty(iss);
  iss >> r;
  //41
  readEmpty(iss);
  iss >> r;
  //nbrNG
  readEmpty(iss);
  iss >> r;
  unsigned int nbrNG = r;
  cout << "nbr " << nbrNG << endl;
  //no newsgroups
  if(nbrNG == 0) {
    return "No newsgroups added";
  }
  for(unsigned int i = 0 ; i < nbrNG ; ++i) {
    //string reading
    readEmpty(iss);
    iss >> r;
    //id
    readEmpty(iss);
    iss >> r;
    unsigned int id = r;
    ngs += to_string(id) + " ";
    readEmpty(iss);
    iss >> r;
    readEmpty(iss);
    iss >> r;
    unsigned int length = r;
    cout << "1 " << length << endl;
    //word starting
    for(unsigned int k = 0; k < length; ++k) {
      iss >> r;
      if(r == '_') {
        ngs += " ";
      } else {
        ngs += r;
      }
    }
    if(i < nbrNG - 1) {
      ngs += "\n";
    }
  }
  //27
  readEmpty(iss);
  iss >> r;
  return ngs;
}
string Inputhandler::translateCreateNG(string reply) {
  cout << "CNG" << endl;
  unsigned char r;
  string resp = ng + " was";
  istringstream iss(reply);
  //readEmpty(iss);
  //21
  readEmpty(iss);
  iss >> r;
  cout << "4" << r << endl;
  readEmpty(iss);
  iss >> r;
  unsigned int code = r;
  cout << "5" << code << endl;
  if (r == static_cast<unsigned int>(Protocol::ANS_ACK)) {
    resp += " successfully added";
  } else {
    resp += " not added, it might already exist, try to list all newsgroups";
  }
  //27
  readEmpty(iss);
  iss >> r;
  return resp;
}
string Inputhandler::translateDeleteNG(string reply) {
  cout << "DNG" << endl;
  unsigned char r;
  string resp = to_string(ngId) + " was";
  istringstream iss(reply);
  //22
  readEmpty(iss);
  iss >> r;
  cout << "4" << r << endl;
  readEmpty(iss);
  iss >> r;
  unsigned int code = r;
  cout << "5" << code << endl;
  if (r == static_cast<unsigned int>(Protocol::ANS_ACK)) {
    resp += " successfully deleted";
  } else {
    resp += " not added, it might not exist, try to list all newsgroups";
  }
  //27
  readEmpty(iss);
  iss >> r;
  return resp;
}
string Inputhandler::translateListArticles(string reply) {
  cout << "LA" << endl;
  string r;
  return r;
}
string Inputhandler::translateCreateArticle(string reply) {
  cout << "CA" << endl;
  string r;
  return r;
}
string Inputhandler::translateDeleteArticle(string reply) {
  cout << "DA" << endl;
  string r;
  return r;
}
string Inputhandler::translateGetArticle(string reply) {
  cout << "GA" << endl;
  string r;
  return r;
}
