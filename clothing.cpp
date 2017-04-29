#include "clothing.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, 
		int qty, const std::string size, const std::string brand)
	:Product(category, name, price, qty), size_(size), brand_(brand)
	{}

Clothing::~Clothing()
{}

std::set<std::string> Clothing::keywords() const
{
	set<string> myset = parseStringToWords(name_);
	set<string> extra = parseStringToWords(brand_);
	myset=setUnion(myset, extra);
	return myset;
}

std::string Clothing::displayString() const
{
	stringstream ss;
	string qtynew;
	string pricenew;
	ss<<qty_<<" "<<price_;
	ss>>qtynew>>pricenew;
	if(qtynew.size()==1)  qtynew = " "+qtynew;
	string temp = name_ + "\n"+"Size: "+size_+" Brand: "+brand_
				  +"\n"+ pricenew+" "+qtynew+" left.";
	return temp;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    	<< "\n" << size_ << "\n" << brand_ << endl;
}