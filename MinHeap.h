#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_
#include "Edge.h"
#include "Dist.h"

class MinHeap{
private:
    int heapSize;
    int capacity;
    Dist **storage;

    void percUp(int);
    void percDown(int);
    int numChildren(int);

    void inOrder(int);
public:
    MinHeap(int);
    ~MinHeap();
    void insert(Dist*);
    Dist removeMin();

    bool isEmpty();
    int getHeapSize(){
        return heapSize;
    }

    void inOrderTraversal();
    void linearDisplay();
    void emptyHeap();
};
#endif
