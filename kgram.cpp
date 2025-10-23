#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// NOTES / TODO:
// "bba" actually appeared twice, but we only captured it once...
// because the second occurrence was at the end.


map<string, map<char, int>> map_kgrams(string input, int k) {
    map<string, map<char, int>> kgrams;
    
    // Loop through the input text
    // Stop at input.length() - k because we need k characters for a k-gram
    for (int i = 0; i <= input.length() - k; i++) {
        // Extract the k-gram at position i
        string kgram = input.substr(i, k);
        
        // Check if there's a next character
        if (i + k < input.length()) {
            char next_char = input[i + k];
            
            // Increment the count for this k-gram -> character transition
            kgrams[kgram][next_char]++;
            
            cout << "Position " << i << ": k-gram '" << kgram 
                 << "' -> next char '" << next_char << "'" << endl;
        } else {
            cout << "Position " << i << ": k-gram '" << kgram 
                 << "' -> no next char (end of text)" << endl;
        }
    }
    
    return kgrams;
}

int main(int argc, char* argv[]) {

    int k = stoi(argv[2]);
    
    ifstream file;
    file.open(argv[1]);

    string line;
    string input;

    while (getline(file, line)) {
        input += line;
    }

    file.close();

    auto kgrams = map_kgrams(input, k);
    
    // Print out the results
    cout << "\n=== RESULTS ===" << endl;
    for (auto& kgram_pair : kgrams) {
        // kgram_pair is: pair<string, map<char, int>>
        cout << "K-gram '" << kgram_pair.first << "':" << endl;

        for (auto& char_pair : kgram_pair.second) {
            // char_pair is: pair<char, int>
            cout << "  -> '" << char_pair.first << "': " << char_pair.second << endl;
        }

        if (kgram_pair.second.empty()) {
            cout << "  (no transitions - end of text)" << endl;
        }
    }

}