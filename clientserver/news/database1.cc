#include "database1.h"
#include "article.h"
#include <string>
#include <vector>
using namespace std;

Database1::Database1(){}
vector<string> Database1::listNewsGroup(){
  return newsGroups;
}

void Database1::createNewsGroup(string news_group_name){ //Borde troligen returnera om vi lyckas eller ej
  newsGroups.push_back(news_group_name);				 //Alltså, om den fanns i vectorn eller ej
}

void Database1::deleteNewsGroup(unsigned int news_group_id){
  newsGroups.erase(newsGroups.begin()+(news_group_id-1));
}

vector<string> Database1::listArticles(unsigned int news_group_id){
  vector<Article> v = articles[news_group_id];
  vector<string> returnv;
  for(Article a : v){
  	returnv.push_back(a.getTitle());
  }
  return returnv;
}

void Database1::createArticle(unsigned int news_group_id, string title, string author, string text){
  articles[news_group_id].emplace_back(title, author, text);
}

void Database1::deleteArticle(unsigned int news_group_id, unsigned int article_id){
  articles[news_group_id].erase(articles[news_group_id].begin()+(article_id-1));
}

string Database1::getArticle(unsigned int news_group_id, unsigned int article_id){
  vector<Article> v = articles[news_group_id];
  return v[article_id].getArticleText();
}
