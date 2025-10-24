#include "kgram.hpp"

using namespace std;

// NOTE: We only track k-grams that have at least one following character.
// K-grams at the end of text are ignored because:
//   1. They cannot generate text (no next character to sample)
//   2. They aren't natural starting points for generation
//
// K-gram frequency n(w) is computed by summing its character transition counts

map<string, map<char, int>> map_kgrams(string input, int k) {
    map<string, map<char, int>> kgrams;
    
    // Loop through the input text, stopping before the last k characters
    for (int i = 0; i < input.length() - k; i++) {
        // Extract the k-gram at position i
        string kgram = input.substr(i, k);
        char next_char = input[i + k];
        
        // Track this k-gram -> character transition
        kgrams[kgram][next_char]++;
    }
    
    return kgrams;
}
