#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> myset;
	typename std::set<T>::iterator it = s2.begin();
	for(;it!=s2.end();it++)
	{
		if(s1.find(*it) != s1.end())
		{
			myset.insert(*it);
		}
	}
	return myset;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> myset = s1;
	typename std::set<T>::iterator it = s2.begin();
	for(;it!=s2.end();it++)
	{
		if(myset.find(*it) == myset.end())
		{
			myset.insert(*it);
		}
	}	
	return myset;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
