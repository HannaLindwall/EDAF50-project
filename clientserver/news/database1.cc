#include "database1.h"
#include "article.h"
#include "notexsistindbexception.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

Database1::Database1(){}
vector<string> Database1::listNewsGroup(){
  return newsGroups;
}

bool Database1::createNewsGroup(string news_group_name){
  bool b;
  if(find(newsGroups.begin(), newsGroups.end(), news_group_name) != newsGroups.end()){
  	b = true;
  } else {
  	b = false;
  }
  if(b){
  	newsGroups.push_back(news_group_name);
  	return true;
  }
  return false;
}

void Database1::deleteNewsGroup(unsigned int news_group_id){
  if(news_group_id >= newsGroups.size()){
    throw NotExsistInDatabaseException();
    return;
  }
    newsGroups.erase(newsGroups.begin()+(news_group_id-1));
}

vector<string> Database1::listArticles(unsigned int news_group_id){
  if(news_group_id >= newsGroups.size()){
    throw NotExsistInDatabaseException();
  }
  vector<Article> v = articles[news_group_id];
  vector<string> returnv;
  for(Article a : v){
  	returnv.push_back(a.getTitle());
  }
  return returnv;
}

void Database1::createArticle(unsigned int news_group_id, string title, string author, string text){
  if(news_group_id >= newsGroups.size()){
    throw NotExsistInDatabaseException();
    return;
  }
  articles[news_group_id].emplace_back(title, author, text);
}

void Database1::deleteArticle(unsigned int news_group_id, unsigned int article_id){
  articles[news_group_id].erase(articles[news_group_id].begin()+(article_id-1));
}

string Database1::getArticle(unsigned int news_group_id, unsigned int article_id){
  vector<Article> v = articles[news_group_id];
  return v[article_id].getArticleText();
}
