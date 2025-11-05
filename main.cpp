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
    
    // Print results
    encodeMessage("input.txt", codes);
    
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

struct NodePath {
    int node;
    string path;
};

void generateCodes(int root, string codes[]) {
    if (root == -1) return;
    
    stack<NodePath> st;
    NodePath start;
    start.node = root;
    start.path = "";
    st.push(start);
    
    while (!st.empty()) {
        NodePath current = st.top();
        st.pop();
        
        // If leaf node, save the code
        if (leftArr[current.node] == -1 && rightArr[current.node] == -1) {
            int charIdx = charArr[current.node] - 'a';
            codes[charIdx] = current.path;
        }
        
        // Add children to stack
        if (rightArr[current.node] != -1) {
            NodePath right;
            right.node = rightArr[current.node];
            right.path = current.path + "1";
            st.push(right);
        }
        if (leftArr[current.node] != -1) {
            NodePath left;
            left.node = leftArr[current.node];
            left.path = current.path + "0";
            st.push(left);
        }
    }
}

void encodeMessage(const string& filename, string codes[]) {
    // Print code table
    cout << "Character : Code" << endl;
    for (int i = 0; i < 26; i++) {
        if (!codes[i].empty()) {
            cout << (char)('a' + i) << " : " << codes[i] << endl;
        }
    }
    
    cout << endl << "Encoded message:" << endl;
    
    // Read file and encode
    ifstream file(filename);
    string text;
    string encoded = "";
    
    if (file.is_open()) {
        while (getline(file, text)) {
            for (char c : text) {
                if (isalpha(c)) {
                    char lower = tolower(c);
                    encoded += codes[lower - 'a'];
                }
            }
        }
        file.close();
    }
    
    cout << encoded << endl;
}
