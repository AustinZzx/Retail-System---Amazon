#include "book.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

Book::Book(const std::string category, const std::string name, double price, 
		int qty, const std::string ISBN, const std::string author)
	:Product(category, name, price, qty), ISBN_(ISBN), author_(author)
	{}

Book::~Book()
{}

std::set<std::string> Book::keywords() const
{
	set<string> myset = parseStringToWords(name_);
	set<string> extra = parseStringToWords(author_);
	set<string> extramore = parseStringToWords(ISBN_);
	extra = setUnion(extra, extramore);
	myset=setUnion(myset, extra);
	return myset;
}

std::string Book::displayString() const
{
	stringstream ss;
	string qtynew;
	string pricenew;
	ss<<qty_<<" "<<price_;
	ss>>qtynew>>pricenew;
	if(qtynew.size()==1)  qtynew = " "+qtynew;
	string temp = name_ + "\n"+"Author: "+author_+" ISBN: "+ISBN_
				  +"\n"+ pricenew+" "+qtynew+" left.";
	return temp;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    	<< "\n" << ISBN_ << "\n" << author_ << endl;
}