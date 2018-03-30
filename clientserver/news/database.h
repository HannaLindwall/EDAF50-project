#ifndef DATABASE_H
#define DATABASE_H

#include <set>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Database{
public:
  virtual ~Database() = default;
  virtual map<unsigned int, string> listNewsGroup() = 0;
	virtual void createNewsGroup(string news_group_name) = 0;
	virtual void deleteNewsGroup(unsigned int news_group_id) = 0;
	virtual vector<pair<unsigned int, string>> listArticles(unsigned int news_group_id) = 0;
	virtual void createArticle(unsigned int news_group_id, string title, string author, string text) = 0;
	virtual void deleteArticle(unsigned int news_group_id, unsigned int article_id) = 0;
	virtual tuple<string, string, string> getArticle(unsigned int news_group_id, unsigned int article_id) = 0;
};
#endif
