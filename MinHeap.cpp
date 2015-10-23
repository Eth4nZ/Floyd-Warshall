#include "MinHeap.h"
#include <iostream>

using namespace std;

MinHeap::MinHeap(int size){
    heapSize = 0;
    capacity = size;
    storage = new Dist*[capacity];
    for(int i = 0; i < capacity; i++)
        storage[i] = NULL;
}

MinHeap::~MinHeap(){
    if(storage != NULL){
        for(int i = 0; i< capacity; i++){
            delete storage[i];
            heapSize--;
        }
        delete[] storage;
    }
}

void MinHeap::insert(Dist *rhs){
    if(heapSize == capacity){
        cerr << "No more room in this heap!" << endl;
        return;
    }
    heapSize++;
    storage[heapSize-1] = rhs;
    percUp(heapSize-1);
}

void MinHeap::percUp(int curIndex){
    int parentIndex;
    Dist* temp;
    if(curIndex != 0){ //not at the top
        parentIndex = (curIndex-1)/2;
        if(storage[parentIndex]->length >
                 storage[curIndex]->length){
            temp = storage[parentIndex];
            storage[parentIndex] = storage[curIndex];
            storage[curIndex] = temp;
            percUp(parentIndex);
        }
    }
}

int MinHeap::numChildren(int index){
    int children = 0;
    int left = 2*index+1, right = left+1;
    if(left >= heapSize)
        return 0;
    if(storage[left] != NULL)
        children++;
    if(storage[right] != NULL)
        children++;
    return children;
}

void MinHeap::percDown(int curIndex){
    int children = numChildren(curIndex);
    if(children != 0){
        Dist* temp;
        int left = 2*curIndex+1, right = left+1;
        switch(children){
            case 1:
                if(storage[curIndex]->length
                        > storage[left]->length){
                    temp = storage[left];
                    storage[left] = storage[curIndex];
                    storage[curIndex] = temp;
                    percDown(left);
                }
                break;
            case 2:
                if((storage[curIndex]->length
                            > storage[left]->length)
                        ||(storage[curIndex]->length
                            > storage[right]->length)){
                    int rhsIndex = left;
                    if(storage[left]->length
                            > storage[right]->length)
                        rhsIndex = right;
                    temp = storage[rhsIndex];
                    storage[rhsIndex] = storage[curIndex];
                    storage[curIndex] = temp;
                    percDown(rhsIndex);
                }
                break;
            default:
                //no way, this shouldn't happen;
                break;
        }
    }
    return;
}

Dist MinHeap::removeMin(){
    Dist* value = new Dist();
    *value = *storage[0];
    //replace 1st & last slot;
    Dist* temp = storage[0];
    storage[0] = storage[heapSize-1];
    storage[heapSize-1] = temp;
    storage[heapSize-1] = NULL; //avoid dangling pointers
    heapSize--;
    percDown(0);
    return *value;
}


bool MinHeap::isEmpty(){
    return (heapSize == 0);
}

void MinHeap::inOrderTraversal(){
    if(isEmpty()){
        cout << "MinHeap is empty!" << endl;
        return;
    }
    inOrder(0);
    cout << endl;
}

void MinHeap::inOrder(int curIndex){
    //left cur right
    int left = 2*curIndex+1, right = left+1;
    if((left < capacity) && (storage[left] != NULL))
        inOrder(left);
    cout << storage[curIndex] << " ";
    if((right < capacity) && (storage[right] != NULL))
        inOrder(right);
}

void MinHeap::linearDisplay(){
 /*   cout << "linearDisplay" << endl;
    for(int i = 0; i < heapSize; i++)
        cout << *storage[i] << " ";
    cout << endl;
    cout << "linearDisplay" << endl; */
}

void MinHeap::emptyHeap(){
  /*  while(!isEmpty()){
        int temp = removeMin();
        cout << temp << endl;
    } */
}

