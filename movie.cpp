#include "movie.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, 
		int qty, const std::string genre, const std::string rating)
	:Product(category, name, price, qty), genre_(genre), rating_(rating)
	{}

Movie::~Movie()
{}

std::set<std::string> Movie::keywords() const
{
	set<string> myset = parseStringToWords(name_);
	set<string> extra = parseStringToWords(genre_);
	myset=setUnion(myset, extra);
	return myset;
}

std::string Movie::displayString() const
{
	stringstream ss;
	string qtynew;
	string pricenew;
	ss<<qty_<<" "<<price_;
	ss>>qtynew>>pricenew;
	if(qtynew.size()==1)  qtynew = " "+qtynew;
	string temp = name_ + "\n"+"Genre: "+genre_+" Rating: "+rating_
				  +"\n"+ pricenew+" "+qtynew+" left.";
	return temp;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    	<< "\n" << genre_ << "\n" << rating_ << endl;
}