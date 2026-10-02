#include "movie.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) :
  Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

set<string> Movie::keywords() const
{
  set<string> keywords = parseStringToWords(name_);
  keywords.insert(convToLower(genre_));
  for (string s : keywords) {
    cout << s << endl;
  }
  return keywords;
}

bool Movie::isMatch(vector<string>& searchTerms) const
{
  return false;
}

string Movie::displayString() const
{
  stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << price_ << " " << qty_ << " left." << "\n";
  return ss.str();
}

void Movie::dump(ostream& os) const 
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}