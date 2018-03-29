#include "protocol.h"
#include "serverhandler.h"
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
}
// ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::deleteNewsGroup(){
  cout << "DNG" << endl;
}
// ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::listArticles(){
  cout << "ListA" << endl;
}
// ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::createArticle(){
  cout << "CA" << endl;
}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::deleteArticle(){
  cout << "DA" << endl;
}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::getArticle(){
  cout << "GA" << endl;
  string return_string = db->getArticle(1 , 1);
}
