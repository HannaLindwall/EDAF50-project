#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H
#include "connection.h"
#include "connectionclosedexception.h"
#include "database1.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>
#include <cstdlib>
using namespace std;

class Serverhandler {
public:
  Serverhandler();
  string listNewsGroup(const shared_ptr<Connection>& conn);
  string createNewsGroup(const shared_ptr<Connection>& conn);
  string deleteNewsGroup(const shared_ptr<Connection>& conn);
  string listArticles(const shared_ptr<Connection>& conn);
  string createArticle(const shared_ptr<Connection>& conn);
  string deleteArticle(const shared_ptr<Connection>& conn);
  string getArticle(const shared_ptr<Connection>& conn);
  void setAction(unsigned int a) { action = a; cout << "action:" << action << endl;}

private:
  unsigned int action;
  unsigned int ngId;
  unsigned int articleId;
  string ng;
  string title;
  string author;
  string text;
  Database1 db1;
};
#endif
