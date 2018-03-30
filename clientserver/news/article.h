#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>
using std::string;

class Article{
public:
  Article(unsigned int id, string article_title, string article_author, string article_text);
  unsigned int getId() const;
  string getTitle() const;
  string getAuthor() const;
  string getArticleText() const;

private:
  unsigned int id;
  string title;
  string author;
  string text;
};
#endif
