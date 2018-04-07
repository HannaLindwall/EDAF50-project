#include "database2.h"
#include "newsgroupdoesnotexistexception.h"
#include "articledoesnotexistexception.h"
#include "newsgroupalreadyexistexception.h"
#include <algorithm>
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
      ng += temp + " ";
    }
    if(ng.substr(0, ng.length() - 1) == comp) {
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

//remove ng from textfile
void Database2::removeNG(unsigned int ngId) {
  unsigned int id;
  ifstream ng_in ("newsgroups.txt");
  ofstream temp ("temp.txt");
  string line;
  while (getline(ng_in,line)) {
    istringstream iss(line);
    iss >> id;
    if(id != ngId) {
      temp << line << endl;
    }
  }
  temp.close();
  ng_in.close();
  remove("newsgroups.txt");
  rename("temp.txt","newsgroups.txt");
}

map<unsigned int, string> Database2::listNewsGroup(){
  map<unsigned int, string> newsGroups;
  unsigned int id;
  ifstream ng_in ("newsgroups.txt");
  string line;
  while(getline(ng_in, line)) {
    istringstream iss(line);
    iss >> id;
    string newsgroup;
    string temp;
    while (iss >> temp) {
      newsgroup += temp + " ";
    }
    newsGroups[id] = newsgroup.substr(0, newsgroup.length() - 1);
  }
  return newsGroups;
}

void Database2::createNewsGroup(string news_group_name){
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
  string ng_id = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(ng_id.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  struct dirent* dp;
  while ((dp = readdir(dirp)) != NULL) {
    remove((to_string(news_group_id) + "/" + string(dp->d_name)).c_str());
  }
  remove(ng_id.c_str());
  removeNG(news_group_id);
}

vector<pair<unsigned int, string>> Database2::listArticles(unsigned int news_group_id){
  string ng_id = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(ng_id.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  vector<pair<unsigned int, string>> articles;
  struct dirent* dp;
  while ((dp = readdir(dirp)) != NULL) {
    //id
    string article_id;
    string articleName = string(dp->d_name);
    if(articleName[0] != '.') {
      istringstream iss1(articleName);
      unsigned char c;
      while( iss1 >> c && c != '.') {
        article_id += c;
      }
      unsigned int art_id;
      istringstream iss2(article_id);;
      iss2 >> art_id;
      //title
      ifstream article_in (ng_id + "/" + articleName);
      string title;
      getline(article_in, title);
      articles.push_back(make_pair(art_id, title));
    }
  }
  sort(articles.begin(), articles.end());
  return articles;
}

void Database2::createArticle(unsigned int news_group_id, string title, string author, string text){
  string ng_id = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(ng_id.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  //if article already exists this just overwrites it
  ofstream article_out (ng_id + "/" + to_string(articleId) + ".txt");
  article_out << title << endl << author << endl << text << endl;
  increaseArticleId();
}

void Database2::deleteArticle(unsigned int news_group_id, unsigned int article_id){
  string ng_id = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(ng_id.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  //test whether file aka article exists
  string art_id = to_string(article_id);

  ifstream article_in (ng_id + "/" + art_id + ".txt");
  if (!article_in.is_open()){
    throw ArticleDoesNotExistException();
  } else {
    //file exists
    remove((ng_id + "/" + art_id + ".txt").c_str());
    article_in.close();
  }
}

tuple<string, string, string> Database2::getArticle(unsigned int news_group_id, unsigned int article_id){
  string ng_id = to_string(news_group_id);
  //test whether folder aka ng exists
  DIR* dirp = opendir(ng_id.c_str());
  if(!dirp) {
    throw NewsGroupDoesNotExistException();
  }
  //test whether file aka article exists
  string art_id = to_string(article_id);
  ifstream article_in (ng_id + "/" + art_id + ".txt");
  string title;
  string author;
  string text;
  if (!article_in.is_open()){
    throw ArticleDoesNotExistException();
  } else {
    //file exists
    getline(article_in, title);
    getline(article_in, author);
    string temp;
    while (getline(article_in, temp)) {
      text += temp + "\n";
    }
    article_in.close();
  }
  return make_tuple(title, author, text.substr(0, text.length() - 1));
}
