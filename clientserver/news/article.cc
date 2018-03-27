#include "article.h"

using std::string;


Article::Article(unsigned int id, string article_title, string article_author, string article_text):
                  id_nbr(id), title(article_title), author(article_author), text(article_text)  {

}
unsigned int Article::getIdNbr() {
  return id_nbr;
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
