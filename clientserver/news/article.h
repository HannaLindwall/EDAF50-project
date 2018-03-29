#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>
using std::string;

class Article{
public:
  Article(string article_title, string article_author, string article_text);
  string getTitle();
  string getAuthor();
  string getArticleText();

private:
  string title;
  string author;
  string text;
};
#endif