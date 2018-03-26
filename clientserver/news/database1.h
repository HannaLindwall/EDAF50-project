#ifndef DATABASE1_H
#define DATABASE1_H 

#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Database1{
public:
	Database1 db();
	vector<string> listNewsGroup();
	void createNewsGroup(string newsGroupName);
	void deleteNewsGroup(string newsGroupName);
	vector<string> listArticles(string newsGroupName);
	void createArticle(string newsGroupName);
	void deleteArticle(string newsGroupName);
	string getArticle(string newsGroupName, string articleName);
private:
	vector<pair<int, string>> newsGroups;
	vector<tuple<int, int, string, string, string>> articles;
	int groupIndex;
};
#endif
