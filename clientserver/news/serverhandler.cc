#include "protocol.h"
#include "database1.h"
#include "serverhandler.h"
//unsigned char input = static_cast<unsigned char>(Protocol::ANS_ACK);

Serverhandler::Serverhandler() {}

string Serverhandler::listNewsGroup(const shared_ptr<Connection>& conn) {
  cout << "list" << endl;
  //just to read the eight

  conn->read();
  return "test";
}
string Serverhandler::createNewsGroup(const shared_ptr<Connection>& conn){
  cout << "CNG" << endl;
  return "test";
}
string Serverhandler::deleteNewsGroup(const shared_ptr<Connection>& conn){
  cout << "DNG" << endl;
  return "test";
}
string Serverhandler::listArticles(const shared_ptr<Connection>& conn){
  cout << "ListA" << endl;
  return "test";
}
string Serverhandler::createArticle(const shared_ptr<Connection>& conn){
  cout << "CA" << endl;
  return "test";
}
string Serverhandler::deleteArticle(const shared_ptr<Connection>& conn){
  cout << "DA" << endl;
  return "test";
}
string Serverhandler::getArticle(const shared_ptr<Connection>& conn){
  cout << "GA" << endl;
  return "test";
}
