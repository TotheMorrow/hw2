#include "mydatastore.h"

void MyDataStore::addProduct(Product* p)
{
  products_.push_back(p);
  set<string> keywords = p->keywords();
  for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
    keyword_map[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u)
{  
  users_[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  vector<Product*> hits;
  if (terms.empty()) return hits;
  set<Product*> matched;

  if (type == 0) {
    auto first = keyword_map.find(terms[0]);
    if (first == keyword_map.end()) return hits;
    matched = first->second;
    for (size_t i = 1; i < terms.size(); i++) {
      auto curr = keyword_map.find(terms[i]);
      if (curr == keyword_map.end()) return hits;
      matched = setIntersection(curr->second, matched);
      if (matched.empty()) return hits;
    }
  } else {
    for (string term : terms) {
      auto curr = keyword_map.find(term);
      if (curr != keyword_map.end()) {
        matched = setUnion(curr->second, matched);
      }
    }
  }
  hits.insert(hits.end(), matched.begin(), matched.end());
  return hits;
}

void MyDataStore::dump(std::ostream& ofile) 
{
  ofile << "<products>\n";
  for (const auto& p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>\n";
  ofile << "<users>\n";
  for (const auto& u : users_) {
    u.second->dump(ofile);
  }
  ofile << "</users>\n";
}