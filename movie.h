#ifndef MOVIE_H
#define MOVIE_H
#include "util.h"
#include "product.h"

using namespace std;

class Movie : public Product {
public:
  Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating);
  set<string> keywords() const;
  bool isMatch(vector<string>& searchTerms) const;
  string displayString() const;
  void dump(ostream& os) const;
private:
  string genre_;
  string rating_;
};

#endif