#include "protocol.h"
#include "serverhandler.h"
#include "newsgroupdoesnotexistexception.h"
#include "articledoesnotexistexception.h"
#include "newsgroupalreadyexistexception.h"
#include <algorithm>

//unsigned char input = static_cast<unsigned char>(Protocol::ANS_ACK);

Serverhandler::Serverhandler(Database* database, MessageHandler& messagehandler) : db(database), mh(&messagehandler){

}
// ANS_LIST_NG num_p [num_p string_p]* ANS_END
void Serverhandler::listNewsGroups() {
  mh->sendCode(Protocol::ANS_LIST_NG);
  map<unsigned int, string> newsgroups = db->listNewsGroup();
  mh->sendIntParameter(newsgroups.size());
  for_each(newsgroups.begin(), newsgroups.end(),
        [&](const pair<unsigned int, string>& p) {
            mh->sendIntParameter(p.first);
            mh->sendStringParameter(p.second);});
  mh->sendCode(Protocol::ANS_END);

}
// ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
void Serverhandler::createNewsGroup(){
  string group_name = mh->recvStringParameter();
  mh->sendCode(Protocol::ANS_CREATE_NG);
  try{
    db->createNewsGroup(group_name);
    mh->sendCode(Protocol::ANS_ACK);
  }catch(NewsGroupAlreadyExistsException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
  }
  mh->sendCode(Protocol::ANS_END);
}

// ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::deleteNewsGroup(){
  unsigned int group_id = mh->recvIntParameter();
  mh->sendCode(Protocol::ANS_DELETE_NG);
  try{
    db->deleteNewsGroup(group_id);
    mh->sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e) {
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }

  mh->sendCode(Protocol::ANS_END);

}
// ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::listArticles(){
  unsigned int group_id = mh->recvIntParameter();
  mh->sendCode(Protocol::ANS_LIST_ART);
  try{
    vector<pair<unsigned int, string>> titles =  db->listArticles(group_id);
    mh->sendCode(Protocol::ANS_ACK);
    mh->sendIntParameter(titles.size());
    for(auto p : titles) {
      mh->sendIntParameter(p.first);
      mh->sendStringParameter(p.second);
    }
  } catch(const NewsGroupDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }
  mh->sendCode(Protocol::ANS_END);
}
// ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
void Serverhandler::createArticle(){
  unsigned int group_id = mh->recvIntParameter();
  string title = mh->recvStringParameter();
  string author = mh->recvStringParameter();
  string text = mh->recvStringParameter();
  mh->sendCode(Protocol::ANS_CREATE_ART);
  try{
    db->createArticle(group_id, title, author, text);
    mh->sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }
  mh->sendCode(Protocol::ANS_END);


}
// ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::deleteArticle(){
  unsigned int group_id = mh->recvIntParameter();
  unsigned int article_id = mh->recvIntParameter();
  mh->sendCode(Protocol::ANS_DELETE_ART);
  try{
    db->deleteArticle(group_id, article_id);
    mh->sendCode(Protocol::ANS_ACK);
  }catch(const NewsGroupDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }catch(const ArticleDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
  }
  mh->sendCode(Protocol::ANS_END);
}

//COM_GET_ART num_p num_p COM_END
//ANS_GET_ART [ANS_ACK string_p string_p string_p | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
void Serverhandler::getArticle(){
  unsigned int group_id = mh->recvIntParameter();
  unsigned int article_id = mh->recvIntParameter();
  mh->sendCode(Protocol::ANS_GET_ART);
  try{
    auto article_info = db->getArticle(group_id, article_id);
    string title = get<0>(article_info);
    string author = get<1>(article_info);
    string text = get<2>(article_info);
    mh->sendCode(Protocol::ANS_ACK);
    mh->sendStringParameter(title);
    mh->sendStringParameter(author);
    mh->sendStringParameter(text);
  }catch(NewsGroupDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
  }catch(ArticleDoesNotExistException& e){
    mh->sendCode(Protocol::ANS_NAK);
    mh->sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
  }
  mh->sendCode(Protocol::ANS_END);
}
