#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore()
{}

MyDataStore::~MyDataStore()
{
	map<User*, vector<Product*> >::iterator it1 = users.begin();
	set<Product*>::iterator it2 = products.begin();
	map<Product*, vector<Review*> >::iterator it3 = reviews.begin();
	for(;it1!=users.end();++it1)
	{
		delete it1->first;
	}
	for(;it3!=reviews.end();++it3)
	{
		unsigned int tempsize = (it3->second).size();
		for(unsigned int i=0; i<tempsize;++i)
		{
			delete (it3->second)[i];
		}
	}
	for(unsigned int i=0;i<orphanreviews.size();++i)
	{
		delete orphanreviews[i];
	}
	for(;it2!=products.end();++it2)
	{
		delete *it2;
	}
}

	/**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p)
{
	products.insert(p);
	set<string> keys = p->keywords();
	set<string>::iterator it = keys.begin();
	set<Product*> pp;
	pp.insert(p);
	for(; it!=keys.end();++it)
	{
		if(keymap.find(*it)==keymap.end())
		{
			keymap.insert(make_pair(*it, pp));
		}
		else
		{
			keymap[*it] = setUnion(keymap[*it], pp);
		}
	}
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u)
{
	vector<Product*> ucart;
	users.insert(make_pair(u, ucart));
}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	vector<Product*> hits;
	vector<string>::iterator it = terms.begin();
	vector< set<Product*> > alltime; 
	for(;it!=terms.end();++it)
	{
		set<string> termsparse = parseStringToWords(*it);
		set<string>::iterator termit = termsparse.begin();
		for(;termit!=termsparse.end();++termit)
		{
			set<Product*> onetime;
			if(keymap.find(*termit)==keymap.end())
			{
				continue;
			}
			else
			{
				alltime.push_back(keymap[*termit]);
			}
		}
	}
	if(alltime.empty()) return hits;
	set<Product*> final = alltime[0];
	for(unsigned int i=0; i<alltime.size(); i++)
	{
		if(type==0)	final = setIntersection(final, alltime[i]);
		if(type==1) final = setUnion(final, alltime[i]);
	}
	set<Product*>::iterator hit = final.begin();
	for(;hit!=final.end();++hit)
	{
		hits.push_back(*hit);
	}
	return hits;
}

    /**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile)	
{
	map<User*, vector<Product*> >::iterator it1 = users.begin();
	set<Product*>::iterator it2 = products.begin();
	map<Product*, vector<Review*> >::iterator it3 = reviews.begin();
	ofile<<"<products>"<<"\n";
	for(;it2!=products.end();++it2)
	{
		(*it2)->dump(ofile);
	}
	ofile<<"</products>"<<"\n"<<"<users>"<<"\n";
	for(;it1!=users.end();++it1)
	{
		(it1->first)->dump(ofile);
	}
	ofile<<"</users>"<<"\n"<<"<reviews>"<<"\n";
	for(;it3!=reviews.end();++it3)
	{
		vector<Review*>::iterator it4 = (it3->second).begin();
		for(;it4!=(it3->second).end();++it4)
		{
			ofile<< (*it4)->prodName <<"\n";
			ofile<<(*it4)->rating <<" "<<(*it4)->username<<" "<<(*it4)->date
				 <<" "<<(*it4)->reviewText<<"\n";
		}
	}
	vector<Review*>::iterator it5 = orphanreviews.begin();
	for(;it5!=orphanreviews.end();++it5)
	{
		ofile<< (*it5)->prodName <<"\n";
		ofile<<(*it5)->rating <<" "<<(*it5)->username<<" "<<(*it5)->date
			 <<" "<<(*it5)->reviewText<<"\n";
	}
	ofile<<"</reviews>"<<"\n";
}

User* MyDataStore::getUser(string username)
{
	map<User*, vector<Product*> >::iterator it = users.begin();
	for(;it!=users.end();++it)
	{
		if(username==(it->first)->getName())
		{
			return it->first;
		}
	}
	return NULL;
}

unsigned long long MyDataStore::hash(string password)
{
	unsigned long long hashcode = 0;
	int n = password.length();
	int temp;
	unsigned long long exponent = 1;
	for(int i=1;i<=n;i++)
	{
		exponent = 1;
		temp = (int)password[i-1];
		for(int k=0;k<n-i;++k)
		{
			exponent *= 128;
		}
		hashcode += exponent*temp;
	}
	unsigned int digits[4];
	for(int i=3;i>=0;--i)
	{
		digits[i] = hashcode%65521;
		hashcode = hashcode/65521;
	}
	hashcode = (45912 * digits[0] + 35511 * digits[1] + 65169 * digits[2] + 4625 * digits[3]) % 65521;
	return hashcode;
}

void MyDataStore::addCart(User* u, Product* p)
{
	users[u].push_back(p);
}

vector<Product*>& MyDataStore::viewCart(User* u)
{
	return users[u];
}

void MyDataStore::removeItem(User* u, Product* p)
{
	vector<Product*> tempcart = users[u];
	unsigned int i=0;
	for(;i<tempcart.size();++i)
	{
		if(tempcart[i]->getName()==p->getName())
		{
			users[u].erase(users[u].begin()+i);
			return;
		}
	}
}

void MyDataStore::buyCart(User* u)
{
	vector<Product*> ucart = users[u];
    for(unsigned i=0; i<ucart.size(); ++i)
    {
        if(ucart[i]->getQty() && (u->getBalance()>=ucart[i]->getPrice()))
        {
        	u->deductAmount(ucart[i]->getPrice());
        	ucart[i]->subtractQty(1);
        	vector<Product*>::iterator position = find(users[u].begin(), 
        											   users[u].end(), ucart[i]);
			if (position != users[u].end())
    			users[u].erase(position);
        }
    }
}

void MyDataStore::addReview(Review* r)
{
	string pname = r->prodName;
	set<Product*>::iterator it = products.begin();
	for(;it!=products.end();++it)
	{
		if(pname == (*it)->getName() )
		{
			if(reviews.find(*it)==reviews.end())
			{
				vector<Review*> temp;
				temp.push_back(r);
				reviews.insert(make_pair(*it, temp));
			}
			else
			{
				reviews[*it].push_back(r);
			}
			reviews[*it] = datesort(reviews[*it]);
			return;
		}
	}
	orphanreviews.push_back(r);
}

set<User*> MyDataStore::getusernames()
{
	set<User*> myset;
	map<User*, vector<Product*> >::iterator it = users.begin();
	for(;it!=users.end();++it)
	{
		myset.insert(it->first);
	}
	return myset;
}

string MyDataStore::getReview(Product* p)
{
	if(reviews.find(p)==reviews.end()) return "";
	vector<Review*> temp = reviews[p];
	vector<Review*>::iterator it4 = temp.begin();
	string output;
	stringstream ss;
	string temprating;
	for(;it4!=temp.end();++it4)
	{
		ss<<(*it4)->rating<<" ";
		ss>>temprating;
		output+=temprating+" "+(*it4)->username+" "+(*it4)->date
			 +"\n"+(*it4)->reviewText+"\n\n";
	}
	return output;
}

vector<Review*> MyDataStore::datesort(vector<Review*>& old) 
{
	vector<string> dates;
	vector<Review*> copy = old;
	for(unsigned int i=0; i<old.size();++i)
	{
		dates.push_back(old[i]->date);
	}
	AlphaStrCompRev comp;
	mergeSort(dates, comp);
	vector<Review*> output;
	for(unsigned int j=0;j<dates.size();j++)
	{
		for(unsigned int k=0; k<copy.size();++k)
		{
			if(copy[k]->date==dates[j])
			{
				output.push_back(copy[k]);
				copy.erase(copy.begin()+k);
				break;
			}
		}
	}
	return output;
}


vector<Product*> MyDataStore::alphasort(vector<Product*>& old) const
{
	vector<string> pronames;
	for(unsigned int i=0; i<old.size();++i)
	{
		pronames.push_back(old[i]->getName());
	}
	AlphaStrComp comp;
	mergeSort(pronames, comp);
	vector<Product*> output;
	for(unsigned int j=0;j<pronames.size();j++)
	{
		for(unsigned int k=0; k<old.size();++k)
		{
			if(old[k]->getName()==pronames[j])
			{
				output.push_back(old[k]);
				break;
			}
		}
	}
	return output;
}

vector<Product*> MyDataStore::ratingsort(vector<Product*>& old) const
{
	vector<double> ratings;
	map<Product*, double> prorating;
	for(unsigned int i=0; i<old.size();++i)
	{
		if(reviews.find(old[i])==reviews.end())
		{
			prorating.insert(make_pair(old[i], 0.0));
			ratings.push_back(0.0);
			continue;
		}
		vector<Review*> tempreview = reviews.find(old[i])->second;
		int sum=0;
		for(unsigned int l=0;l<tempreview.size();++l)
		{
			sum+=tempreview[l]->rating;
		}
		double avr = (double)sum/tempreview.size();
		prorating.insert(make_pair(old[i], avr));
		ratings.push_back(avr);
	}
	NumbigDouComp comp;
	mergeSort(ratings, comp);
	vector<Product*> output;
	for(unsigned int j=0;j<ratings.size();j++)
	{
		map<Product*, double>::iterator it = prorating.begin();
		for(;it!=prorating.end();++it)
		{
			if(it->second==ratings[j])
			{
				output.push_back(it->first);
				prorating.erase(it);
				break;
			}
		}
	}
	return output;
}

double MyDataStore::calcSimilarity(User* lhs, User* rhs)
{
	if(reviews.empty()) return 1.0;
	double result = 0.0;
	int lexist, rexist;
	double sim;
	double cnt = 0.0;
	map<Product*, vector<Review*> >::iterator it = reviews.begin();
	for(;it!=reviews.end();++it)
	{	
		sim = 1.0;
		lexist = -1;
		rexist = -1;
		vector<Review*> rev = it->second;
		for(unsigned int i=0;i<rev.size();++i)
		{
			Review* temp = rev[i];
			if(temp->username == lhs->getName()) lexist = i;
			else if(temp->username == rhs->getName()) rexist = i;			
		}
		if(lexist!=-1 && rexist!=-1)
		{
			sim = (double)(abs(rev[lexist]->rating-rev[rexist]->rating))/4.0;
			cnt++;
			result += sim;
		}	
	}
	if(cnt==0.0) return 1.0;
	return result/cnt;
}

map<User*, double> MyDataStore::calcAll(User* u)
{
	map<User*, double> result;
	Heap<string> myheap;
	u->dist_ = 0.0;
	u->pred_ = NULL;
	myheap.push(u->dist_, u->getName());
	map<User*, vector<Product*> >::iterator it = users.begin();
	for(;it!=users.end();++it)
	{
		User* temp = it->first;
		if(temp!=u)
		{
			temp->dist_ = calcSimilarity(u, temp);
			temp->pred_ = u;
			myheap.push(temp->dist_, temp->getName());
		}
	}
	while(!myheap.empty())
	{
		string vname = myheap.top();
		myheap.pop();
		User* v = getUser(vname);
		if(u!=v)
		{
			result.insert(make_pair(v, v->dist_));
		}
		it = users.begin();
		for(;it!=users.end();++it)
		{
			User* temp = it->first;
			if(temp!=v)
			{				
				double w = calcSimilarity(v, temp);
				if(v->dist_+w < temp->dist_)
				{
					temp->pred_ = v;
					temp->dist_ = v->dist_+w;
					myheap.decreaseKey(temp->dist_, temp->getName());
				}
			}
		}
	}
	return result;
}

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser)
{
	vector<std::pair<std::string, double> > result;
	User* u = getUser(currentUser);
	map<User*, double> sim = calcAll(u);
	bool exist = false;
	double RP, W;
	double similar;
	map<Product*, vector<Review*> >::iterator it = reviews.begin();
	for(;it!=reviews.end();++it)
	{
		RP = 0;
		W = 0;
		exist = false;
		vector<Review*> tempreview = it->second;
		for(unsigned int i=0;i<tempreview.size();++i)
		{
			if(tempreview[i]->username == currentUser)
			{
				exist = true;
				break;
			}
			else
			{
				similar = sim[getUser(tempreview[i]->username)];
				W += (1-similar);
				RP += (1-similar)*(tempreview[i]->rating);
			}
		}
		if(!exist)
		{
			if(W==0.0)  result.push_back(make_pair(it->first->getName(), 0.0));
			else {
				result.push_back(make_pair(it->first->getName(), RP/W));
			}
		}
	}
	mergeSort(result, PairComp());
	return result;
}