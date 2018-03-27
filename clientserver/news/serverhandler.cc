#include "protocol.h"
#include "serverhandler.h"
//unsigned char input = static_cast<unsigned char>(Protocol::ANS_ACK);

Serverhandler::Serverhandler(Database* database, MessageHandler& messagehandler) : db(database), mh(messagehandler){

}

string Serverhandler::listNewsGroup() {
  cout << "list" << endl;
  string return_string = "20 ";
  vector<string> newsgroups = db->listNewsGroup();
  // string data = "";
  // for(string s : newsgroups){
  //   data += s;
  //   data += " ";
  // }
  //return_string += messageHandler.parseshit(data);
  return return_string;
}
string Serverhandler::createNewsGroup(){
  cout << "CNG" << endl;
  return "test";
}
string Serverhandler::deleteNewsGroup(){
  cout << "DNG" << endl;
  return "test";
}
string Serverhandler::listArticles(){
  cout << "ListA" << endl;
  return "test";
}
string Serverhandler::createArticle(){
  cout << "CA" << endl;
  return "test";
}
string Serverhandler::deleteArticle(){
  cout << "DA" << endl;
  return "test";
}
string Serverhandler::getArticle(){
  cout << "GA" << endl;
  string return_string = db->getArticle(1 , 1);
  return return_string;

}
