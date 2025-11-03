#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Arrays for tree
char charArr[100];
int weightArr[100];
int leftArr[100];
int rightArr[100];
int nextFree = 0;

// Next steps
int buildEncodingTree(int startIdx);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

void createLeafNodes(int freq[]) {
    nextFree = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
}

int main() {
    cout << "Starting encoder..." << endl;
    
    // Read file and count letters
    ifstream file("input.txt");
    string text;
    int freq[26] = {0};
    
    if (file.is_open()) {
        while (getline(file, text)) {
            for (char c : text) {
                if (isalpha(c)) {
                    freq[tolower(c) - 'a']++;
                }
            }
        }
        file.close();
    }
    
    // Make leaf nodes
    createLeafNodes(freq);
    
    // Build tree
    int root = buildEncodingTree(nextFree);
    
    // Get codes
    string codes[26];
    generateCodes(root, codes);
    
    return 0;
}

int buildEncodingTree(int startIdx) {
    if (nextFree <= 1) return 0;
    
    MinHeap heap;
    
    // Add all leaf nodes to heap
    for (int i = 0; i < nextFree; i++) {
        heap.push(i);
    }
    
    // Combine nodes until one remains
    while (heap.size > 1) {
        int left = heap.pop();
        int right = heap.pop();
        
        // Create parent node
        int parent = nextFree;
        weightArr[parent] = weightArr[left] + weightArr[right];
        leftArr[parent] = left;
        rightArr[parent] = right;
        nextFree++;
        
        heap.push(parent);
    }
    
    return heap.pop();
}

void generateCodes(int root, string codes[]) {
    if (root == -1) return;
    
    stack<pair<int, string>> st;
    st.push({root, ""});
    
    while (!st.empty()) {
        int node = st.top().first;
        string path = st.top().second;
        st.pop();
        
        // If leaf node, save the code
        if (leftArr[node] == -1 && rightArr[node] == -1) {
            int charIdx = charArr[node] - 'a';
            codes[charIdx] = path;
        }
        
        // Add children to stack
        if (rightArr[node] != -1) {
            st.push({rightArr[node], path + "1"});
        }
        if (leftArr[node] != -1) {
            st.push({leftArr[node], path + "0"});
        }
    }
}

void encodeMessage(const string& filename, string codes[]) {
}
