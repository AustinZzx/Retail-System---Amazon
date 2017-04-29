#include <vector>
#include <iostream>
using namespace std;

  template <class T, class Comparator>
  void mymerge(vector<T>& mylist, vector<T>& output, Comparator comp,
			int s1, int e1, int s2, int e2)
  {
  	int s = s1;
  	int low = s1;
  	while(s1<=e1 && s2<=e2)
  	{
  		if(comp(mylist[s1],mylist[s2]))
  		{
  			output[s] = mylist[s1];
  			s++;
  			s1++;
  		}
  		else
  		{
  			output[s] = mylist[s2];
  			s++;
  			s2++;
  		}
  	}
  	while(s1<=e1)
  	{
  		output[s] = mylist[s1];
  		s++;
  		s1++;
  	}
  	while(s2<=e2)
  	{
  		output[s] = mylist[s2];
  		s++;
  		s2++;
  	}
  	for(;low<s;low++)
  	{
  		mylist[low] = output[low];
  	}
  }

  template <class T, class Comparator>
  void msort(vector<T>& mylist, vector<T>& output, Comparator comp, int start, int end)
  {
    // base case
  if(start >= end) return;
  // recursive calls
  int mid = (start+end)/2;
  msort(mylist, output, comp, start, mid);
  msort(mylist, output, comp, mid+1, end);
  // merge
  mymerge(mylist, output, comp, start, mid, mid+1, end);
  }
  
  template <class T, class Comparator>
  void mergeSort (vector<T>& myArray, Comparator comp)
  {
    if(myArray.size()<=1)
    {
      return;
    }
    else
    {
      vector<T> other(myArray);
      msort(other, myArray, comp, 0, myArray.size()-1);
    }
  }
