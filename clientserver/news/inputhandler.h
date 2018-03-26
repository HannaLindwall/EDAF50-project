#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;

class Inputhandler {
public:
  void enterNG(){
    cout << "Enter name of newsgroup";
    cin >> ng;
    flags.push_back(42);
  }
  void enterNGId(){
    cout << "Enter identification number of newsgroup";
    cin >> ngId;
    flags.push_back(41);
  }
  void enterListArticles(){
    enterNGId();
  }
  void enterCreateArticle() {
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
  void enterArticleId() {
    enterNGId();
    cout << "Enter the article identification number";
    cin >> articleId;
    flags.push_back(41);
  }
  void enterGetArticle() {
    enterArticleId();
  }

  string listNG();
  string createNG();
  string deleteNG();
  string listArticles();
  string createArticle();
  string deleteArticle();
  string getArticle();

  Inputhandler() {
    input_functions[2] = enterNG;
    input_functions[3] = enterNGId;
    input_functions[4] = enterListArticles;
    input_functions[5] = enterCreateArticle;
    input_functions[6] = enterArticleId;
    input_functions[7] = enterGetArticle;

    format_functions[1] = listNG;
    format_functions[2] = createNG;
    format_functions[3] = deleteNG;
    format_functions[4] = listArticles;
    format_functions[5] = createArticle;
    format_functions[6] = deleteArticleId;
    format_functions[7] = getArticle;
  }
  
  unsigned int action(unsigned int act) {
    auto perform = input_functions.find(act);
    if(perform != input_functions.end()) {
      action = act;
      input_functions[act]();
    }
    if(act == 1)
    action = act;
    cout << endl;
    return action;
  }
  string getText() { return format_functions[action](); }

private:
  std::vector<unsigned int> flags;
  unsigned int action;
  unsigned int ngId;
  unsigned int articleId;
  string ng;
  string title;
  string author;
  string text;
  std::map<std::pair<int, void()>> input_functions;
  std::map<std::pair<int, void()>> format_functions;
}
