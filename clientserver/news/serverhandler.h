#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H
#include "connection.h"
#include "connectionclosedexception.h"
#include "database.h"
#include "messagehandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
using namespace std;

class Serverhandler {
public:
  Serverhandler(Database* db, MessageHandler& mh);
  string listNewsGroup();
  string createNewsGroup();
  string deleteNewsGroup();
  string listArticles();
  string createArticle();
  string deleteArticle();
  string getArticle();
  void setAction(unsigned int a) { action = a; cout << "action:" << action << endl;}

private:
  Database* db;
  MessageHandler mh;
  unsigned int action;
};
#endif
