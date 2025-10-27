#include <iostream>
using namespace std;

// Weight array for heap comparisons
extern int weightArr[];

struct MinHeap {
    int data[100];
    int size;
    
    MinHeap() : size(0) {}
    
    void push(int index) {
        data[size] = index;
        size++;
        upheap(size - 1);
    }
    
    int pop() {
        if (size == 0) return -1;
        
        int min = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0);
        return min;
    }
    
    void upheap(int index) {
        if (index == 0) return;
        
        int parent = (index - 1) / 2;
        if (weightArr[data[index]] < weightArr[data[parent]]) {
            swap(data[index], data[parent]);
            upheap(parent);
        }
    }
    
    void downheap(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        
        if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
            smallest = left;
        }
        
        if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(data[index], data[smallest]);
            downheap(smallest);
        }
    }
};
