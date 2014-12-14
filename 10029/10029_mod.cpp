// Credits to https://github.com/ajahuang for this solution.
//
#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

unordered_map<string, int> L; 

int main() {
    int maxLength = 0;
    string w2;

    // Generate all possible matches
    while (getline(cin, w2) && !w2.empty()){
        int length = 1;

        // Additions
        for (int i = 0; i <= w2.size(); i++)
            for (char c = 'a'; c <= 'z'; c++){
                string w1(w2);
                w1.insert(i, 1, c);
                if (w1 > w2)
                    break;
                if (L.count(w1))
                    length = max(length, L[w1] + 1);
	    }
        // Deletions
        for (int i = 0; i < w2.size(); i++){
            string w1(w2);
            w1.erase(i, 1);
            if (L.count(w1))
                length = max(length, L[w1] + 1);
        }
        // Mods
        for (int i = 0; i < w2.size(); i++)
            for (char c = 'a'; c < w2[i]; c++){
                string w1(w2);
                w1[i] = c;
                if (L.count(w1))
                    length = max(length, L[w1] + 1);
            }
        L[w2] = length;
        maxLength = max(maxLength, length);
    }
    cout << maxLength << endl;
}
