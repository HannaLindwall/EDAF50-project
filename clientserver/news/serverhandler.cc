#include "protocol.h"
#include "serverhandler.h"
#include <string>

using std::string;
//unsigned char input = static_cast<unsigned char>(Protocol::ANS_ACK);

Serverhandler::Serverhandler(Database* database, MessageHandler& messagehandler) : db(database), mh(messagehandler){

}
// ANS_LIST_NG num_p [num_p string_p]* ANS_END
void Serverhandler::listNewsGroups() {
  cout << "list" << endl;
  mh.recvCode();
  mh.sendCode(Protocol::ANS_LIST_NG);
  vector<string> newsgroups = db->listNewsGroup();
  mh.sendIntParameter(newsgroups.size());
  for(string ng : newsgroups) {
    mh.sendIntParameter(ng.length());
    mh.sendStringParameter(ng);
  }
  mh.sendCode(Protocol::ANS_END);
}
// ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
void Serverhandler::createNewsGroup(){
  cout << "CNG" << endl;
  mh.recvCode();
  string group_name = mh.recvStringParameter();
  db->createNewsGroup(group_name); // Denna måste returnera en bool för
  //Skicka tillbaka ACK eller NACK
  // mh.sendCode(Protocol::ANS_CREATE_NG);
  // //if success sendCode ANS_ACK
  //   mh.sendCode(Protocol::ANS_ACK);
  // //else sendCode ANS_NAK ERR_NG_ALREADY_EXISTS
  //   mh.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
  // mh.sendCode(Protocol::ANS_END);
}
// ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::deleteNewsGroup(){
  cout << "DNG" << endl;
  mh.recvCode();
  unsigned int group_id = mh.recvIntParameter();
  db->deleteNewsGroup(group_id);

}
// ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::listArticles(){
  cout << "ListA" << endl;
  mh.recvCode();
}
// ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::createArticle(){
  cout << "CA" << endl;
  mh.recvCode();
  mh.
}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::deleteArticle(){
  cout << "DA" << endl;
  mh.recvCode();
  unsigned int group_id = mh.recvIntParameter();
  unsigned int article_id = mh.recvIntParameter();
  db->deleteNewsGroup(group_id, article_id);
}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::getArticle(){
  cout << "GA" << endl;
  mh.recvCode();
  string return_string = db->getArticle(1 , 1);
}
