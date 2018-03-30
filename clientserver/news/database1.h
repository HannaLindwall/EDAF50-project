#ifndef DATABASE1_H
#define DATABASE1_H

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "database.h"
#include "article.h"
using namespace std;

class Database1 : public Database{
public:
	Database1();
	virtual map<unsigned int, string> listNewsGroup();
	virtual void createNewsGroup(string news_group_name);
	virtual void deleteNewsGroup(unsigned int news_group_id);
	virtual vector<pair<unsigned int, string>> listArticles(unsigned int news_group_id);
	virtual void createArticle(unsigned int news_group_id, string title, string author, string text);
	virtual void deleteArticle(unsigned int news_group_id, unsigned int article_id);
	virtual tuple<string, string, string> getArticle(unsigned int news_group_id, unsigned int article_id);
private:
	map<unsigned int, string> newsGroups;
	map<unsigned int, vector<Article>> articles;
	unsigned int ngId;
	unsigned int articleId;

};
#endif
