#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>

class MyDataStore : public DataStore 
{
public:
    ~MyDataStore() {
      for (Product* p : products_) {
        delete p;
      }
      for (auto u : users_) {
        delete u.second;
      }
    }
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    map<string, User*> users_;
    map<string, vector<Product*>> carts_;
private:
  vector<Product*> products_;
  map<string, set<Product*>> keyword_map;
};

#endif