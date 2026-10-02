#ifndef CLOTHING_H
#define CLOTHING_H

#include "util.h"
#include "product.h"
using namespace std;

class Clothing : public Product {
public:
  Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand);
  ~Clothing();
  std::set<std::string> keywords() const;
  bool isMatch(std::vector<std::string>& searchTerms) const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

private:
  string size_;
  string brand_;
  set<string> keywords_;
};

#endif