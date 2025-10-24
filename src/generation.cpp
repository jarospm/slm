#include "generation.hpp"
#include <random>
#include <vector>

using namespace std;

string generate_text(const map<string, map<char, int>>& kgrams, int length) {
    // Set up random number generator
    random_device rd;       // Get one "truly random" number from hardware
    mt19937 gen(rd());  // Use it to seed the fast generator
    
    // Step 1: Choose starting k-gram according to k-gram frequencies
    vector<string> kgram_list;
    vector<int> kgram_weights;
    
    // Build two synchronized vectors for (1) k-gram strings and (2) total frequencies
    for (const auto& kgram_pair : kgrams) {
        kgram_list.push_back(kgram_pair.first);
        // K-gram frequency is sum of all character transition counts
        int total = 0;
        for (const auto& char_pair : kgram_pair.second) {
            total += char_pair.second;
        }
        kgram_weights.push_back(total);
    }
    
    // Sample initial k-gram based on frequencies
    discrete_distribution<int> kgram_dist(kgram_weights.begin(), kgram_weights.end());
    string current_kgram = kgram_list[kgram_dist(gen)];
    
    // Output starts with the initial k-gram
    string output = current_kgram;
    
    // Generate remaining characters
    while (output.length() < length) {
        // Step 2: Look up character distribution for current k-gram
        const auto& char_dist = kgrams.at(current_kgram);
        
        vector<char> chars;
        vector<int> counts;

        // Build two parallel vectors for (1) chars and (2) respective counts
        for (const auto& char_pair : char_dist) {
            chars.push_back(char_pair.first);
            counts.push_back(char_pair.second);
        }
        
        // Sample next character
        discrete_distribution<int> char_distribution(counts.begin(), counts.end());
        char next_char = chars[char_distribution(gen)];
        
        // Step 3: Output character
        output += next_char;
        
        // Step 4: Update k-gram (remove first char, add sampled char)
        current_kgram = current_kgram.substr(1) + next_char;
        
        // If new k-gram doesn't exist in model...
        if (kgrams.find(current_kgram) == kgrams.end()) {
            // add space and pick a new random kgram
            output += " ";
            current_kgram = kgram_list[kgram_dist(gen)];
            
            // Check how many characters we can still add
            int remaining = length - output.length();
            
            // Truncate the k-gram if it would exceed the length
            if (remaining < (int)current_kgram.length()) {
                output += current_kgram.substr(0, remaining);
            } else {
                // Otherwise add space + full k-gram
                output += current_kgram;
            }
        }
    }
    
    return output;
}

