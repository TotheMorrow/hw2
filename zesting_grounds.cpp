#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "util.h"

using namespace std;

int main () {
  string rawWords1 = "Data Abstraction & Problem Solving with C++";
  set<string> keywords1 = parseStringToWords(rawWords1);
  string rawWords2 = "Data Abstraction & Problem Solving with";
  set<string> keywords2 = parseStringToWords(rawWords2);

  set<string> set_union = setUnion(keywords1, keywords2);
  cout << "union:" << endl;
  for (set<string>::iterator it=set_union.begin(); it != set_union.end(); ++it) {
    cout << *it << endl;
  }
  set<string> set_intersection = setIntersection(keywords1, keywords2);
  cout << "intersection:" << endl;
  for (set<string>::iterator it=set_intersection.begin(); it != set_intersection.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}