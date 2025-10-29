#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

// Arrays for tree
char charArr[100];
int weightArr[100];
int leftArr[100];
int rightArr[100];
int nextFree = 0;

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
    
    return 0;
}
