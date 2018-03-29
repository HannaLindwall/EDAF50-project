#include "article.h"

using std::string;


Article::Article(string article_title, string article_author, string article_text):
                  title(article_title), author(article_author), text(article_text)  {

}

string Article::getTitle(){
  return title;
}

string Article::getAuthor(){
  return author;
}

string Article::getArticleText(){
  return text;
}
