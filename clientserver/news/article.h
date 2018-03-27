using std::string;

class Article{
public:
  Article(unsigned int id, string article_title, string article_author, string article_text);
  unsigned int getIdNbr();
  string getTitle();
  string getAuthor();
  string getArticleText();

private:
  unsigned int id_nbr;
  string title;
  sting author;
  string text;
}
