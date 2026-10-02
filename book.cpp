#include "book.h"

Book::Book(const std::string category, const std::string name, double price, int qty, string ISBN, string author) : Product(category, name, price, qty) {
  author_ = author;
  ISBN_ = ISBN;
  // keywords_ = Book::keywords();
}

set<string> Book::keywords() const {
  set<string> keywords = parseStringToWords(name_);
  set<string> author_keywords = parseStringToWords(author_);
  keywords.insert(author_keywords.begin(), author_keywords.end());
  keywords.insert(ISBN_);
  return keywords;
}

bool Book::isMatch(vector<string>& searchTerms) const {
  // for (const auto& keyword : searchTerms) {
  //   if (keywords_.find(keyword) != keywords_.end()) {
  //     return true;
  //   }
  // }
  return false;
}

string Book::displayString() const {
  stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << ISBN_ << "\n";
  ss << price_ << " " << qty_ << " left." << "\n";
  return ss.str();
}

void Book::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}