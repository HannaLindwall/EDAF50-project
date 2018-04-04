#include "database2.h"
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
#include <fstream>
#include <ios>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;

Database2::Database2(){
  //file with ngId
  ifstream ngID_in ("NGId.txt");
  if (ngID_in.is_open()){
    ngID_in >> ngId;
    ngID_in.close();
  } else {
    //create NGId.txt
    ofstream ngID_out ("NGId.txt");
    ngID_out << 1 << endl;
    ngId = 1;
  }
  //file with articleId
  ifstream article_in ("articleId.txt");
  if (article_in.is_open()){
    article_in >> articleId;
    article_in.close();
  } else {
    //create articleId.txt
    ofstream article_out ("articleId.txt");
    article_out << 1 << endl;
    articleId = 1;
  }
  //file with newsgroups
  ifstream ng_in ("newsgroups.txt");
  if (!ng_in.is_open()){
    ofstream ng_out ("newsgroups.txt");
  } else {
    //file exists
    ng_in.close();
  }
}
//check if newsgroup already exist with name
bool Database2::newsgroup_exist(istream& ng, string comp) {
  string line;
  while(getline(ng, line)) {
    istringstream iss(line);
    string temp;
    //id
    iss >> temp;
    //ng
    string ng;
    while (iss >> temp) {
      ng += temp;
    }
    if(ng == comp) {
       return true;
    }
  }
  return false;
}
//increase ngid after creating new ng
void Database2::increaseNGId() {
  ofstream ng ("NGId.txt");
  ++ngId;
  ng << ngId << endl;
}
//increase articleId after creating new article
void Database2::increaseArticleId() {
  ofstream article ("articleId.txt");
  ++articleId;
  article << articleId << endl;
}

map<unsigned int, string> Database2::listNewsGroup(){
  map<unsigned int, string> mp;
  return {{0,"hej"}, {1,"hejsan"}};
}

void Database2::createNewsGroup(string news_group_name){
  cout << "db2 cng" << endl;
  ifstream ng_in("newsgroups.txt");
  //check if newsgroup already exist
  bool flag = newsgroup_exist(ng_in, news_group_name);

  ng_in.close();
  //the newsgroup already exists
  if(flag) {
    throw NewsGroupAlreadyExistsException();
  }
  //add newsgroup to newsgroup.txt, ios::app to not overwrite
  ofstream ng_out ("newsgroups.txt", ios::app);
  ng_out << ngId << " " << news_group_name << endl;
  mkdir(to_string(ngId).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  increaseNGId();
}

void Database2::deleteNewsGroup(unsigned int news_group_id){
  cout << "db2 dng" << endl;
  string n = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(n.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  struct dirent* dp;
  while ((dp = readdir(dirp)) != NULL) {
    cout << dp->d_name << endl;
    remove((to_string(news_group_id) + "/" + string(dp->d_name)).c_str());
  }
  remove(to_string(news_group_id).c_str());
}

vector<pair<unsigned int, string>> Database2::listArticles(unsigned int news_group_id){
  return {make_pair(1, "hejsan")};
}

void Database2::createArticle(unsigned int news_group_id, string title, string author, string text){
  cout << "db2 ca" << endl;
  string n = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(n.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  //if article already exists this just overwrites it
  ofstream article_out (n + "/" + to_string(articleId) + ".txt");
  article_out << title << endl << author << endl << text << endl;
}

void Database2::deleteArticle(unsigned int news_group_id, unsigned int article_id){

}

tuple<string, string, string> Database2::getArticle(unsigned int news_group_id, unsigned int article_id){
  return make_tuple("hej", "hh", "blabla");
}
