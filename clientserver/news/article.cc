#include "article.h"

using std::string;


Article::Article(unsigned int i, string article_title, string article_author, string article_text): id(i),
                  title(article_title), author(article_author), text(article_text)  {

}
unsigned int Article::getId() const{
  return id;
}

string Article::getTitle() const{
  return title;
}

string Article::getAuthor() const{
  return author;
}

string Article::getArticleText() const{
  return text;
}
