#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <map>
#include "messagehandler.h"
#include "protocol.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;
class Inputhandler;
typedef void (Inputhandler::*void_funct)();
typedef string (Inputhandler::*mh_funct)(MessageHandler&);
typedef string (Inputhandler::*string_funct)(string);

class Inputhandler {
public:
  void enterNG();
  void enterNGId();
  void enterListArticles();
  void enterCreateArticle();
  void enterArticleId();
  void enterGetArticle();

  void listNG();
  void createNG();
  void deleteNG();
  void listArticles();
  void createArticle();
  void deleteArticle();
  void getArticle();

  string readListNG(MessageHandler& mh);
  string readCreateNG(MessageHandler& mh);
  string readDeleteNG(MessageHandler& mh);
  string readListArticles(MessageHandler& mh);
  string readCreateArticle(MessageHandler& mh);
  string readDeleteArticle(MessageHandler& mh);
  string readGetArticle(MessageHandler& mh);


  Inputhandler(MessageHandler messagehandler) : mh(messagehandler) {
    input_functions[2] = &Inputhandler::enterNG;
    input_functions[3] = &Inputhandler::enterNGId;
    input_functions[4] = &Inputhandler::enterListArticles;
    input_functions[5] = &Inputhandler::enterCreateArticle;
    input_functions[6] = &Inputhandler::enterArticleId;
    input_functions[7] = &Inputhandler::enterGetArticle;

    format_functions[1] = &Inputhandler::listNG;
    format_functions[2] = &Inputhandler::createNG;
    format_functions[3] = &Inputhandler::deleteNG;
    format_functions[4] = &Inputhandler::listArticles;
    format_functions[5] = &Inputhandler::createArticle;
    format_functions[6] = &Inputhandler::deleteArticle;
    format_functions[7] = &Inputhandler::getArticle;

    read_functions[1] = &Inputhandler::readListNG;
    read_functions[2] = &Inputhandler::readCreateNG;
    read_functions[3] = &Inputhandler::readDeleteNG;
    read_functions[4] = &Inputhandler::readListArticles;
    read_functions[5] = &Inputhandler::readCreateArticle;
    read_functions[6] = &Inputhandler::readDeleteArticle;
    read_functions[7] = &Inputhandler::readGetArticle;

  }

  unsigned int perform_action(unsigned int act) {
    auto perform = input_functions.find(act);
    if(perform != input_functions.end()) {
      cout << "found " << act << endl;
      action = act;
      (this->*input_functions[act])();
    }
    if(act == 1) {
      action = act;
    }
    return action;
  }
  void sendParameters() { (this->*format_functions[action])(); mh.sendCode(Protocol::COM_END);}
  string readParameters() { return (this->*read_functions[action])(mh); }


private:
  std::vector<unsigned int> flags;
  unsigned int action;
  unsigned int ngId;
  unsigned int articleId;
  string ng;
  string title;
  string author;
  string text;
  std::map<int, void_funct> input_functions;
  std::map<int, void_funct> format_functions;
  std::map<int, mh_funct> read_functions;
  std::map<int, string_funct> translate_functions;
  MessageHandler mh;
  string build(string s);
  void sendInt(unsigned int i);
  void sendString(string s);
  string readText(string s
  );
};
#endif
