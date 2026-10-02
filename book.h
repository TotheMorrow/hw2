#ifndef BOOK_H
#define BOOK_H

#include "util.h"
#include "product.h"
using namespace std;

class Book : public Product {
public:
  Book(const std::string category, const std::string name, double price, int qty, string ISBN, string author);
  set<string> keywords() const;
  bool isMatch(vector<string>& searchTerms) const;
  string displayString() const;
  void dump(ostream& os) const;
private:
  string author_;
  string ISBN_;
};
#endif