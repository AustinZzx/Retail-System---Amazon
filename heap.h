#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void heapify(int idx);
    void trickleUp(int loc);
    void swap(int locf, int locr);


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.
    store_.push_back(std::make_pair(priority, item));
    keyToLocation_.insert(std::make_pair(item, store_.size()-1));
    trickleUp(store_.size()-1);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
    int idx = keyToLocation_[item];
    store_[idx].first = priority;
    keyToLocation_[item] = priority;
    trickleUp(idx);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete
    return store_[0].second;
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete
    T item = store_[0].second;
    keyToLocation_.erase(item);
    store_[0] = store_.back(); 
    store_.pop_back();
    heapify(0); // a.k.a. trickleDown()
}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::swap(int locf, int locr)
{
  std::pair<double, T> temp = store_[locf];
  store_[locf] = store_[locr];
  store_[locr] = temp;
  keyToLocation_[temp.second] = locr;
  keyToLocation_[store_[locf].second] = locf;
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int loc)
{
// could be implemented recursively
  int parent = (loc-1)/m_;
  while(parent >= 0)
  {
    if(c_(store_[loc].first,store_[parent].first) )
    {  
      swap(parent, loc);
      loc = parent;
      parent = (loc-1)/m_;
    }
    else break;
  }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify(int idx)   //needs modifying...no more
{
  if(idx*m_+1 >= store_.size()) return;
  int smallerChild = m_*idx+1; // start w/ left
  int rChild = smallerChild;
  for(int i=0;i<m_-1;++i)
  {
    rChild++;
    if(rChild<store_.size())
    {
      if(c_(store_[rChild].first,store_[smallerChild].first))
      {
        smallerChild = rChild;
      } 
    }
  }
  if(c_(store_[smallerChild].first,store_[idx].first))
  {
    swap(idx, smallerChild);
    heapify(smallerChild);
  } 
}
#endif

