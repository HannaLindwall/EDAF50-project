#include "database1.h"
#include "article.h"
#include "newsgroupdoesnotexistexception.h"
#include "articledoesnotexistexception.h"
#include "newsgroupalreadyexistexception.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <tuple>
#include <exception>
#include <iostream>
using namespace std;

Database1::Database1(){
  articleId = 1;
  ngId = 1;
}
map<unsigned int, string> Database1::listNewsGroup(){
  return newsGroups;
}

void Database1::createNewsGroup(string news_group_name){
  auto it = find_if(newsGroups.begin(), newsGroups.end(), [&news_group_name] (const pair<unsigned int, string>& p) { return p.second == news_group_name; });
  if(it != newsGroups.end()){
  	throw NewsGroupAlreadyExistsException();
  }
  newsGroups[ngId] = news_group_name;
  ++ngId;
}

void Database1::deleteNewsGroup(unsigned int news_group_id){
  auto it = newsGroups.find(news_group_id);
  if (it == newsGroups.end()) {
    throw NewsGroupDoesNotExistException();
  }
  newsGroups.erase(it);
}

vector<pair<unsigned int, string>> Database1::listArticles(unsigned int news_group_id){
  auto it = newsGroups.find(news_group_id);
  if (it == newsGroups.end()) {
    throw NewsGroupDoesNotExistException();
  }
  vector<Article> arts = articles[news_group_id];
  vector<pair<unsigned int, string>> returnv;
  for(auto a : arts){
  	returnv.emplace_back(a.getId(), a.getTitle());
  }
  return returnv;
}

void Database1::createArticle(unsigned int news_group_id, string title, string author, string text){
auto it = newsGroups.find(news_group_id);
  if (it == newsGroups.end()) {
    throw NewsGroupDoesNotExistException();
  }
  articles[news_group_id].emplace_back(articleId, title, author, text);
  ++articleId;
}

void Database1::deleteArticle(unsigned int news_group_id, unsigned int article_id){
  auto it1 = newsGroups.find(news_group_id);
  if (it1 == newsGroups.end()) {
      throw NewsGroupDoesNotExistException();
  }
  auto it2 = remove_if(articles[news_group_id].begin(), articles[news_group_id].end(), [&article_id] (const Article& a) { return a.getId() == article_id; });
  if (it2 == articles[news_group_id].end()) {
      throw ArticleDoesNotExistException();
  }
  articles[news_group_id].erase(it2);
}

tuple<string, string, string> Database1::getArticle(unsigned int news_group_id, unsigned int article_id){
  auto it1 = newsGroups.find(news_group_id);
  if (it1 == newsGroups.end()) {
      throw NewsGroupDoesNotExistException();
  }
  vector<Article> v = articles[news_group_id];
  auto it2 = find_if(articles[news_group_id].begin(), articles[news_group_id].end(), [&article_id] (const Article& a) { return a.getId() == article_id; });
  if (it2 == articles[news_group_id].end()) {
      throw ArticleDoesNotExistException();
  }
  auto article_info = make_tuple(it2->getTitle(), it2->getAuthor(), it2->getArticleText());
  return article_info;
}
