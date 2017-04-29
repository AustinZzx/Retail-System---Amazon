#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> myset;
    stringstream ss(rawWords);
    string temp;
    while(ss>>temp)
    {
        temp = convToLower(temp);
        if(temp.size()<2) continue;
        else
        {
            unsigned int breakpt = 0;
            for(unsigned int i=0; i<temp.size();i++)
            {
                if(ispunct(temp[i])&&(!(temp.size()==15&&temp[3]=='-'&&temp[13]=='-')))
                {
                    string part = temp.substr(breakpt, i-1);
                    breakpt = i;
                    if(part.size()>1)  myset.insert(part);
                }
            }
            if(!breakpt)
            {
                string rest = temp.substr(breakpt, temp.size()-1);
                if(rest.size()>1)  myset.insert(rest);
            }
            else if(breakpt!=temp.size()-1)
            {
                string rest = temp.substr(breakpt+1, temp.size()-1);
                if(rest.size()>1)  myset.insert(rest);
            }
        }
    }
    return myset;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
