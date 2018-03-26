#include "inputhandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
using std::cout;
using std::cin;
using std::string;
using std::isstringstream;
using std::endl;
using std::pair;

//string_p: PAR_STRING N char1 char2 ... charN // N is the number of characters
//num_p: PAR_NUM N // N is the number

// COM_END
string Inputhandler::listNG() {
  string input = to_string(action);
  input += " 8";
  return input;
}
// string_p COM_END
string Inputhandler::createNG() {
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ng.length());
  for(char c : ng) {
    input += " ";
    if(c == " ") {
      input += "_";
    } else {
      input += c;
    }
  }
  input += " 8";
  return input;

}
// num_p COM_END
string Inputhandler::deleteNG() {
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  input += " 8";
  return input;

}
// num_p COM_END
string Inputhandler::listArticles() {
  return deleteNG();

}
// num_p string_p string_p string_p COM_END
string Inputhandler::createArticle() {
  //action
  string input = to_string(action);
  //NGId
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  //title
  input += " " + to_string(flags[1]);
  input += " " + to_string(title.length());
  for(char c : ng) {
    input += " ";
    if(c == " ") {
      input += "_";
    } else {
      input += c;
    }
  }
  //author
  input += " " + to_string(flags[2]);
  input += " " + to_string(author.length());
  for(char c : author) {
    input += " ";
    if(c == " ") {
      input += "_";
    } else {
      input += c;
    }
  }
  //text
  input += " " + to_string(flags[3]);
  input += " " + to_string(text.length());
  for(char c : ng) {
    input += " ";
    if(c == " ") {
      input += "_";
    } else {
      input += c;
    }
  }
  input += " 8";
  return input;


}
//  num_p num_p COM_END
string Inputhandler::deleteArticle() {
  string input = to_string(action);
  input += " " + to_string(flags[0]);
  input += " " + to_string(ngId);
  input += " " + to_string(flags[1]);
  input += " " + to_string(articleId);
  input += " 8";
  return input;

}
// num_p num_p COM_END
string Inputhandler::getArticle() {
  return deleteArticle();

}
