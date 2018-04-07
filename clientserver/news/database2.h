#ifndef DATABASE2_H
#define DATABASE2_H

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "database.h"
using namespace std;

class Database2 : public Database{
public:
	Database2();
	virtual map<unsigned int, string> listNewsGroup();
	virtual void createNewsGroup(string news_group_name);
	virtual void deleteNewsGroup(unsigned int news_group_id);
	virtual vector<pair<unsigned int, string>> listArticles(unsigned int news_group_id);
	virtual void createArticle(unsigned int news_group_id, string title, string author, string text);
	virtual void deleteArticle(unsigned int news_group_id, unsigned int article_id);
	virtual tuple<string, string, string> getArticle(unsigned int news_group_id, unsigned int article_id);
private:
	unsigned int ngId;
	unsigned int articleId;
  bool newsgroup_exist(istream& ng, string comp);
  void increaseNGId();
  void increaseArticleId();
	void removeNG(unsigned int ngId);
};
#endif
