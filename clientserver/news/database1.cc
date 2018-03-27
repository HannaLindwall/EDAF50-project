#include "database1.h"
#include <string>
#include <vector>
using namespace std;

Database1::Database1(){}
vector<string> Database1::listNewsGroup(){

}
void Database1::createNewsGroup(string news_group_name){}
void Database1::deleteNewsGroup(unsigned int news_group_id){}
vector<string> Database1::listArticles(unsigned int news_group_id){}
void Database1::createArticle(unsigned int news_group_id, string title, string author, string text){}
void Database1::deleteArticle(unsigned int news_group_id, unsigned int article_id){}
string Database1::getArticle(unsigned int news_group_id, unsigned int article_id){
	return "hej";
}
