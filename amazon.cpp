#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    // a hit is a product that matches a search query?
    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD") {
              string username;
              size_t hit_result_index;
              if (!(ss >> username >> hit_result_index)) {
                cout << "Invalid request" << endl;
                continue;
              }
              username = convToLower(username);
              auto curr = ds.users_.find(username);
              if (hit_result_index > hits.size() || hit_result_index < 1 || curr == ds.users_.end()) {
                cout << "Invalid request" << endl;
              } else {
                ds.carts_[username].push_back(hits[hit_result_index-1]);
              }
            }
            else if (cmd == "VIEWCART") {
              string username;
              if (!(ss>>username)) {
                cout << "Invalid username" << endl;
                continue;
              }
              username = convToLower(username);
              auto curr = ds.users_.find(username);
              if (curr == ds.users_.end()) {
                cout << "Invalid username" << endl;
              } else {
                int item_number = 1;
                for (Product* p : ds.carts_[username]) {
                  cout << "Item " << item_number << endl;
                  cout << p -> displayString() << endl;
                  item_number++;
                }
              }
            } 
            else if (cmd == "BUYCART") {
              string username;
              if (!(ss>>username)) {
                cout << "Invalid username" << endl;
                continue;
              }

              username = convToLower(username);
              auto curr = ds.users_.find(username);
              if (curr == ds.users_.end()) {
                cout << "Invalid username" << endl;
              } else {
                User* user = curr->second;
                vector<Product*>& cart = ds.carts_[username];
                auto it = cart.begin();
                while (it != cart.end()) {
                  Product* p = *it;
                  if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
                    user->deductAmount(p->getPrice());
                    p->subtractQty(1);
                    it = cart.erase(it);
                  } else {
                    ++it;
                  }
                }
              }
            }
            else {
                cout << "Unknown command" << endl;
            }
      }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
