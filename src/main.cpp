#include <iostream>
#include <string>
#include <fstream>
#include "training.hpp"
#include "generation.hpp"

using namespace std;

// Print k-gram frequencies (computed by summing transition counts)
void print_kgram_frequencies(const map<string, map<char, int>>& kgrams) {
    cout << "\n=== K-GRAM FREQUENCIES ===" << endl;
    for (auto& kgram_pair : kgrams) {
        int total = 0;
        for (auto& char_pair : kgram_pair.second) {
            total += char_pair.second;
        }
        cout << "K-gram '" << kgram_pair.first << "': " << total << endl;
    }
}

// Print character transitions for each k-gram
void print_character_transitions(const map<string, map<char, int>>& kgrams) {
    cout << "\n=== CHARACTER TRANSITIONS ===" << endl;
    for (auto& kgram_pair : kgrams) {
        cout << "K-gram '" << kgram_pair.first << "':" << endl;

        for (auto& char_pair : kgram_pair.second) {
            cout << "  -> '" << char_pair.first << "': " << char_pair.second << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // Usage: ./slm <k> <input_file> <generation_length>
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <k> <input_file> <generation_length>" << endl;
        return 1;
    }

    int k = stoi(argv[1]);
    int gen_length = stoi(argv[3]);
    
    ifstream file;
    file.open(argv[2]);

    string line;
    string input;

    while (getline(file, line)) {
        input += line + " ";
    }

    file.close();

    // Training phase
    auto kgrams = map_kgrams(input, k);
    
    // print_kgram_frequencies(kgrams);
    // print_character_transitions(kgrams);
    // cout << "\n=== GENERATED TEXT ===" << endl;

    // Generation phase
    string generated = generate_text(kgrams, gen_length);
    cout << generated << endl;

}

