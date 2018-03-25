#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
using std::cout;
using std::endl;

class Cliendhandler {
public:
  void createNG(){
    cout << "Enter name of newsgroup";
  }
  void deleteNG(){
    cout << "Enter identification number of newsgroup";
  }
  void listArticles(){
    cout << "Enter identification number of newsgroup";
  }
  void createArticle() {
    cout << "Enter the identification number of newsgroup, followed by
the article title, author and text.";
  }
  void deleteArticle() {
    cout << "The group and article identification numbers";
  }
  void getArticle() {
    cout << "The group and article identification numbers";
  }
  void action(unsigned int act) {
    auto perform = _functions.find(act);
    if(perform != _functions.end()) {
      _functions[act]();
    } else {
      cout << "Action could not be found";
    }
    cout << endl;
  }
  Clienthandler() {
    _functions[2] = createNG;
    _functions[3] = deleteNG;
    _functions[4] = listArticles;
    _functions[5] = createArticle;
    _functions[6] = deleteArticle;
    _functions[7] = getArticle;
  }
private:
  std::map<std::pair<int,void()>> _functions;
}
