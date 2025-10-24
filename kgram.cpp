#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// REFLECT LATER... do we actually need a separate map for k-gram frequencies? 
// The only reason is to count the k-grams at the end of the text... 
// but those should not be relevant for text generation, so why bother? 

// Training phase: Extract k-gram statistics from input text
// Returns a pair containing:
//   1. K-gram frequencies: map<string, int> - counts how many times each k-gram appears
//   2. Character transitions: map<string, map<char, int>> - for each k-gram, counts which characters follow it
pair<map<string, int>, map<string, map<char, int>>> map_kgrams(string input, int k) {
    map<string, int> kgram_counts;           // Track k-gram frequencies
    map<string, map<char, int>> transitions;  // Track character transitions
    
    // Loop through the input text
    // Stop at input.length() - k because we need k characters for a k-gram
    for (int i = 0; i <= input.length() - k; i++) {
        // Extract the k-gram at position i
        string kgram = input.substr(i, k);
        
        // Always count the k-gram occurrence
        kgram_counts[kgram]++;
        
        // Check if there's a next character
        if (i + k < input.length()) {
            char next_char = input[i + k];
            
            // Increment the count for this k-gram -> character transition
            transitions[kgram][next_char]++;
            
            cout << "Position " << i << ": k-gram '" << kgram 
                 << "' -> next char '" << next_char << "'" << endl;
        } else {
            cout << "Position " << i << ": k-gram '" << kgram 
                 << "' -> no next char (end of text)" << endl;
        }
    }
    
    return make_pair(kgram_counts, transitions);
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

    auto result = map_kgrams(input, k);
    auto kgram_counts = result.first;
    auto transitions = result.second;
    
    // Print k-gram frequencies
    cout << "\n=== K-GRAM FREQUENCIES ===" << endl;
    for (auto& count_pair : kgram_counts) {
        cout << "K-gram '" << count_pair.first << "': " << count_pair.second << endl;
    }
    
    // Print transition probabilities
    cout << "\n=== CHARACTER TRANSITIONS ===" << endl;
    for (auto& trans_pair : transitions) {
        cout << "K-gram '" << trans_pair.first << "':" << endl;

        for (auto& char_pair : trans_pair.second) {
            cout << "  -> '" << char_pair.first << "': " << char_pair.second << endl;
        }

        if (trans_pair.second.empty()) {
            cout << "  (no transitions - end of text)" << endl;
        }
    }

}