#include "model.hpp"

using namespace std;

// NOTE: We only track k-grams that have at least one following character.
// K-grams at the end of text are ignored because:
//   1. They cannot generate text (no next character to sample)
//   2. They aren't natural starting points for generation
//
// When reading from files, spaces are added after each line (in main.cpp),
// which means line-ending k-grams transition to spaces rather than being dropped.
//
// K-gram frequency n(w) is computed by summing its character transition counts

Model::Model(int k) : k(k) {
    // Initialize empty k-grams map
}

void Model::train(const string& input) {
    // Loop through the input text, stopping before the last k characters
    for (int i = 0; i < input.length() - k; i++) {
        // Extract the k-gram at position i
        string kgram = input.substr(i, k);
        char next_char = input[i + k];
        
        // Track this k-gram -> character transition
        kgrams[kgram][next_char]++;
    }
}

const map<string, map<char, int>>& Model::get_kgrams() const {
    return kgrams;
}

int Model::get_k() const {
    return k;
}

