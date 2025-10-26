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

Model::Model(int k, const string& input) {
    // Train: Extract k-gram character transition statistics from input text
    for (size_t i = 0; i < input.length() - k; i++) {
        // Extract the k-gram at position i
        string kgram = input.substr(i, k);
        char next_char = input[i + k];
        
        // Track this k-gram -> character transition
        kgrams[kgram][next_char]++;
    }
    
    // Pre-compute k-gram list and weights (two synchronized vectors)
    for (const auto& kgram_pair : kgrams) {
        kgram_list_.push_back(kgram_pair.first);
        
        // K-gram frequency is sum of all character transition counts
        int total = 0;
        for (const auto& char_pair : kgram_pair.second) {
            total += char_pair.second;
        }
        kgram_weights_.push_back(total);
    }
}

const vector<string>& Model::get_kgram_list() const {
    return kgram_list_;
}

const vector<int>& Model::get_kgram_weights() const {
    return kgram_weights_;
}

string Model::sample_random_kgram(mt19937& gen) const {
    discrete_distribution<int> dist(kgram_weights_.begin(), kgram_weights_.end());
    return kgram_list_[dist(gen)];
}

char Model::sample_next_char(const string& kgram, mt19937& gen) const {
    const auto& char_dist = kgrams.at(kgram);
    
    vector<char> chars;
    vector<int> counts;
    
    // Two parallel vectors for (1) chars and (2) respective counts
    for (const auto& char_pair : char_dist) {
        chars.push_back(char_pair.first);
        counts.push_back(char_pair.second);
    }
    
    discrete_distribution<int> dist(counts.begin(), counts.end());
    return chars[dist(gen)];
}

bool Model::has_kgram(const string& kgram) const {
    return kgrams.find(kgram) != kgrams.end();
}

const map<string, map<char, int>>& Model::get_kgrams() const {
    return kgrams;
}

