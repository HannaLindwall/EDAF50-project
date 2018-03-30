#include "database1.h"
#include "article.h"
#include "newsgroupdoesnotexistexception.h"
#include "atricledoesnotexistexception.h"
#include "newsgroupalreadyexistexception.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <exception>
#include <iostream>
using namespace std;

Database1::Database1(){}
vector<string> Database1::listNewsGroup(){
  return newsGroups;
}

void Database1::createNewsGroup(string news_group_name){

  if(find(newsGroups.begin(), newsGroups.end(), news_group_name) != newsGroups.end()){
  	throw NewsGroupAlreadyExistsException();
  }
  newsGroups.push_back(news_group_name);
}

void Database1::deleteNewsGroup(unsigned int news_group_id){
  if (news_group_id > newsGroups.size()) {
    throw NewsGroupDoesNotExistException();
  }
    newsGroups.erase(newsGroups.begin()+(news_group_id-1));
}

vector<string> Database1::listArticles(unsigned int news_group_id){
  if (news_group_id > newsGroups.size()) {
    throw NewsGroupDoesNotExistException();
  }
  vector<Article> v = articles[news_group_id];
  vector<string> returnv;
  for(Article a : v){
  	returnv.push_back(a.getTitle());
  }
  return returnv;
}

void Database1::createArticle(unsigned int news_group_id, string title, string author, string text){
if (news_group_id > newsGroups.size()) {
    throw NewsGroupDoesNotExistException();
  }
  articles[news_group_id].emplace_back(title, author, text);
}

void Database1::deleteArticle(unsigned int news_group_id, unsigned int article_id){
  if (news_group_id > newsGroups.size()) {
      throw NewsGroupDoesNotExistException();
  }
  try{
    articles[news_group_id].erase(articles[news_group_id].begin()+(article_id-1));
  }catch(exception& e){
    throw ArticleDoesNotExistException();
  }
}

tuple<string, string, string> Database1::getArticle(unsigned int news_group_id, unsigned int article_id){
  if (news_group_id > newsGroups.size()) {
    throw NewsGroupDoesNotExistException();
  }
  vector<Article> v = articles[news_group_id];
  try{
    auto article_info = make_tuple(v[article_id].getTitle(), v[article_id].getAuthor(), v[article_id].getArticleText());
    return article_info;
  }catch(exception& e){
    throw ArticleDoesNotExistException();
  }

}
