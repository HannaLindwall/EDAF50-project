using std::string;

class Article{
public:
  Article(unsigned int id, string title, string author, string text);
  string getTitle();
  unsigned int getIdNbr();
  string getArticleText();
  string getAuthor();

private:
  unsigned int id_nbr;
  string title;
  sting author;
  string text;
}
