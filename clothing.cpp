#include <sstream>
#include "clothing.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) :
  Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
  // keywords_ = Clothing::keywords();
}
Clothing::~Clothing() {
}

std::set<std::string> Clothing::keywords() const {
  set<string> keywords = parseStringToWords(name_);
  set<string> brand_keywords = parseStringToWords(brand_);
  keywords.insert(brand_keywords.begin(), brand_keywords.end());
  return keywords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
  return false;
}

std::string Clothing::displayString() const {
  stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << price_ << " " << qty_ << " left." << "\n";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}