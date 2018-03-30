#include "protocol.h"
#include "serverhandler.h"
#include "newsgroupdoesnotexistexception.h"
#include "atricledoesnotexistexception.h"
#include "newsgroupalreadyexistexception.h"
#include <string>
#include <tuple>

using std::string;
//unsigned char input = static_cast<unsigned char>(Protocol::ANS_ACK);

Serverhandler::Serverhandler(Database* database, MessageHandler& messagehandler) : db(database), mh(messagehandler){

}
// ANS_LIST_NG num_p [num_p string_p]* ANS_END
void Serverhandler::listNewsGroups() {
  cout << "list" << endl;
  mh.sendCode(Protocol::ANS_LIST_NG);
  mh.recvCode();
  vector<string> newsgroups = db->listNewsGroup();
  mh.sendIntParameter(newsgroups.size());
  for(unsigned int i = 0; i < newsgroups.size(); ++i) {
    mh.sendIntParameter(i);
    mh.sendStringParameter(newsgroups[i]);
  }
  mh.sendCode(Protocol::ANS_END);
}
// ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
void Serverhandler::createNewsGroup(){
  cout << "CNG" << endl;
  string group_name = mh.recvStringParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_CREATE_NG);
  try{
    db->createNewsGroup(group_name);
    mh.sendCode(Protocol::ANS_ACK);
  }catch(NewsGroupAlreadyExistsException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
  }
  cout << "gn" << group_name << endl;
  mh.sendCode(Protocol::ANS_END);
}

// ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::deleteNewsGroup(){
  cout << "DNG" << endl;
  unsigned int group_id = mh.recvIntParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_DELETE_NG);
  try{
    db->deleteNewsGroup(group_id);
    mh.sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e) {
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }

  mh.sendCode(Protocol::ANS_END);

}
// ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::listArticles(){
  cout << "ListA" << endl;
  unsigned int group_id = mh.recvIntParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_LIST_ART);
  try{
    vector<string> titles =  db->listArticles(group_id);
    mh.sendCode(Protocol::ANS_ACK);
    for(string t : titles) {
      mh.sendIntParameter(t.length());
      mh.sendStringParameter(t);
    }
    }catch(const NewsGroupDoesNotExistException& e){
      mh.sendCode(Protocol::ANS_NAK);
      mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }
  mh.sendCode(Protocol::ANS_END);
}
// ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::createArticle(){
  cout << "CA" << endl;
  unsigned int group_id = mh.recvIntParameter();
  string title = mh.recvStringParameter();
  string author = mh.recvStringParameter();
  string text = mh.recvStringParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_CREATE_ART);
  try{
    db->createArticle(group_id, title, author, text);
    mh.sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }
  mh.sendCode(Protocol::ANS_END);


}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::deleteArticle(){
  cout << "DA" << endl;
  unsigned int group_id = mh.recvIntParameter();
  unsigned int article_id = mh.recvIntParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_DELETE_ART);
  try{
    db->deleteArticle(group_id, article_id);
    mh.sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }catch(const ArticleDoesNotExistException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
  }
  mh.sendCode(Protocol::ANS_END);
}

//COM_GET_ART num_p num_p COM_END
//ANS_GET_ART [ANS_ACK string_p string_p string_p | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::getArticle(){
  cout << "GA" << endl;
  unsigned int group_id = mh.recvIntParameter();
  unsigned int article_id = mh.recvIntParameter();
  mh.recvCode();
  mh.sendCode(Protocol::ANS_GET_ART);
  try{
    auto article_info = db->getArticle(group_id, article_id);
    string title = get<0>(article_info);
    string author = get<0>(article_info);
    string text = get<0>(article_info);
    mh.sendCode(Protocol::ANS_ACK);
    mh.sendStringParameter(title);
    mh.sendStringParameter(author);
    mh.sendStringParameter(text);
  }catch(NewsGroupDoesNotExistException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }catch(ArticleDoesNotExistException& e){
    mh.sendCode(Protocol::ANS_NAK);
    mh.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
  }
  mh.sendCode(Protocol::ANS_END);
}
