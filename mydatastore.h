#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
//#include <climits>
//#include <algorithm>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include "review.h"
#include "msort.h"
#include "heap.h"

using namespace std;


struct AlphaStrComp {
  bool operator()(const string& lhs, const string& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs < rhs; 
  }
};

struct AlphaStrCompRev {
  bool operator()(const string& lhs, const string& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs > rhs; 
  }
};

struct NumbigDouComp {
  bool operator()(const double& lhs, const double& rhs) 
  { 
    return lhs > rhs; 
  }
};

struct PairComp {
  bool operator()(const pair<std::string, double>& lhs, const pair<std::string, double>& rhs) 
  { 
    if(lhs.second == rhs.second) return lhs.first<rhs.first;
    else return lhs.second>rhs.second; 
  }
};



class MyDataStore: public DataStore
{
public:
	MyDataStore();
	~MyDataStore();
	/**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    User* getUser(string username);

    unsigned long long hash(string password);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);	

    void addCart(User* u, Product* p);

    vector<Product*>& viewCart(User* u);

    void removeItem(User* u, Product* p);

    void buyCart(User* u);

    void addReview(Review* r);

    string getReview(Product* p);

    set<User*> getusernames();

    vector<Review*> datesort(vector<Review*>& old);

    vector<Product*> alphasort(vector<Product*>& old) const;

    vector<Product*> ratingsort(vector<Product*>& old) const;

    double calcSimilarity(User* lhs, User* rhs);

    map<User*, double> calcAll(User* u);

    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

private:
	map<User*, vector<Product*> > users;
	set<Product*> products;
    map<string, set<Product*> > keymap;
    map<Product*, vector<Review*> > reviews;
    vector<Review*> orphanreviews;
};
#endif