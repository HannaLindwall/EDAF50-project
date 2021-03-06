#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H
#include "database.h"
#include "messagehandler.h"
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
using namespace std;

class Serverhandler {
public:
  Serverhandler(Database* db, MessageHandler& mh);
  void listNewsGroups();
  void createNewsGroup();
  void deleteNewsGroup();
  void listArticles();
  void createArticle();
  void deleteArticle();
  void getArticle();
  void setAction(unsigned int a) { action = a;}

private:
  Database* db;
  MessageHandler* mh;
  unsigned int action;
};
#endif
