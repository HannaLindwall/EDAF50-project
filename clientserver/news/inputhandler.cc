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
  cin.ignore();
  std::getline(cin, title);
  cout << "Enter the author" << endl;
  std::getline(cin, author);
  cout << "Enter text, end with space #" << endl;
  string temp;
  while(cin >> temp && temp != "#")  {
    text += temp + " ";
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
      cout << "space" << endl;
      input += "_";
    } else {
      cout << c << endl;
      input += c;
    }
  }
  cout << input << endl;
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
// ANS_LIST_NG num_p [num_p string_p]* ANS_END
string Inputhandler::readListNG(MessageHandler& mh) {
  mh.recvCode();
  unsigned int nbrNG = mh.recvIntParameter();
  if(nbrNG==0) {
    return "No newsgroups created yet.";
  }
  string output = "List of all newsgroups:";
  for(unsigned int i = 0; i < nbrNG; ++i) {
    output += "\n";
    unsigned int id = mh.recvIntParameter();
    output += to_string(id) + " ";
    string ngName = mh.recvStringParameter();
    output += ngName;
  }
  return output;
}
// ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
string Inputhandler::readCreateNG(MessageHandler& mh) {
  mh.recvCode();
  string output = "Newsgroup: " + ng;
  if(mh.recvCode()==Protocol::ANS_ACK) {
    output += " was successfully created.";
  } else {
    output += " could not be created.";
    if(mh.recvCode()==Protocol::ERR_NG_ALREADY_EXISTS) {
      output += " The newsgroup might already exist, try another name.";
    }
  }
  return output;

}
// ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
string Inputhandler::readDeleteNG(MessageHandler& mh) {
  mh.recvCode();
  string output = "Newsgroup: " + to_string(ngId);
  if(mh.recvCode()==Protocol::ANS_ACK) {
    output += " was successfully deleted.";
  } else {
    output += " could not be deleted.";
    if(mh.recvCode()==Protocol::ERR_NG_DOES_NOT_EXIST) {
      output += " The newsgroup might not exist, try listing all newsgroups.";
    }
  }
  return output;
}
// ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
string Inputhandler::readListArticles(MessageHandler& mh) {
  mh.recvCode();
  string output = "Newsgroup: " + to_string(ngId);
  if(mh.recvCode()==Protocol::ANS_ACK) {
    unsigned int nbrArt = mh.recvIntParameter();
    if(nbrArt==0) {
      output += " has no articles added to it yet.";
    } else {
      for(unsigned int i = 0; i < nbrArt; ++i) {
        output += "\n";
        unsigned int id = mh.recvIntParameter();
        output += to_string(id) + " ";
        string art = mh.recvStringParameter();
        output += art;
      }
    }
  } else {
    if(mh.recvCode()==Protocol::ERR_NG_DOES_NOT_EXIST) {
      output += " might not exist, try listing all newsgroups.";
    }
  }
  return output;
}
// ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
string Inputhandler::readCreateArticle(MessageHandler& mh) {
  mh.recvCode();
  string output = "Article: " + title;
  if(mh.recvCode()==Protocol::ANS_ACK) {
    output += " was successfully added to newsgroup: " + to_string(ngId);
  } else {
    output += " could not be created.";
    if(mh.recvCode()==Protocol::ERR_NG_DOES_NOT_EXIST) {
      output += " The newsgroup might not exist, try listing all newsgroups.";
    }
  }
  return output;
}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
string Inputhandler::readDeleteArticle(MessageHandler& mh) {
  mh.recvCode();
  string output = "Article: " + to_string(articleId);
  if(mh.recvCode()==Protocol::ANS_ACK) {
    output += " was successfully deleted from newsgroup: " + to_string(ngId);
  } else {
    output += " could not be deleted.";
    if(mh.recvCode()==Protocol::ERR_NG_DOES_NOT_EXIST) {
      output += " The newsgroup might not exist, try listing all newsgroups.";
    }
    if(mh.recvCode()==Protocol::ERR_ART_DOES_NOT_EXIST) {
      output += " The article might not exist, try listing all articles in newsgoup: " + to_string(ngId);
    }
  }
  return output;
}
//ANS_GET_ART [ANS_ACK string_p string_p string_p | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
string Inputhandler::readGetArticle(MessageHandler& mh) {
  mh.recvCode();
  string output = "Article: " + to_string(articleId);
  if(mh.recvCode()==Protocol::ANS_ACK) {
    for( unsigned int i = 0; i < 3; ++i) {
      output += "\n";
      string op = mh.recvStringParameter();
      op = readText(op);
      output += op;
    }
  } else {
    output += " could not be found.";
    if(mh.recvCode()==Protocol::ERR_NG_DOES_NOT_EXIST) {
      output += " The newsgroup might not exist, try listing all newsgroups.";
    }
    if(mh.recvCode()==Protocol::ERR_ART_DOES_NOT_EXIST) {
      output += " The article might not exist, try listing all articles in newsgoup: " + to_string(ngId);
    }
  }
  return output;
}

///translate

string Inputhandler::readText(string op) {
  string input;
  istringstream iss(op);
  unsigned char r;
  iss >> r;
  if(r == '_') {
    input += " ";
  } else {
    input += r;
  }
  return input;
}
