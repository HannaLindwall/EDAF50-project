#include <tuple>
#include <map>
#include <vector>
using namespace std;

class database1{
public:
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
}