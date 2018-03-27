#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H
#include "connection.h"
#include "connectionclosedexception.h"
#include "database.h"
#include <iostream>
#include <string>
#include <vector>
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
  Database db;
};
#endif
