#include "heap.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    srand(time(0));
    Heap<int, greater<int> > heap(10);
    unsigned int size = 100;
    for(unsigned int i = 0; i < size; i++){
        heap.push(rand() % 1000, 2);
    }
    int prev = heap.top();
    heap.pop();
    int errorCount = 0;
    for(unsigned int i = 0; i < size - 1; i++){
        if(prev < heap.top()){
            errorCount++;
        }
        prev = heap.top();
        heap.pop();
    }

    cout << "Errors: " << errorCount << endl;
}