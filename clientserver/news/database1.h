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
	virtual vector<string> listNewsGroup();
	virtual void createNewsGroup(string news_group_name);
	virtual void deleteNewsGroup(unsigned int news_group_id);
	virtual vector<string> listArticles(unsigned int news_group_id);
	virtual void createArticle(unsigned int news_group_id, string title, string author, string text);
	virtual void deleteArticle(unsigned int news_group_id, unsigned int article_id);
	virtual string getArticle(unsigned int news_group_id, unsigned int article_id);
private:
	vector<string> newsGroups;
	map<int, vector<Article>> articles;

};
#endif
