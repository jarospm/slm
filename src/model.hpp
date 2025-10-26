#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <map>
#include <vector>
#include <random>

// Model class encapsulates k-gram statistics and training
class Model {
private:
    // K-grams representation: map<string, map<char, int>> 
    //   - Outer map: k-gram -> character distribution
    //   - Inner map: character -> count of how many times it follows the k-gram
    std::map<std::string, std::map<char, int>> kgrams;
    
    // Derived sampling data (computed after training)
    std::vector<std::string> kgram_list_;
    std::vector<int> kgram_weights_;

public:
    // Constructor: initialize and train model with k-gram size and input text
    Model(int k, const std::string& input);
    
    // Sampling interface
    const std::vector<std::string>& get_kgram_list() const;
    const std::vector<int>& get_kgram_weights() const;
    std::string sample_random_kgram(std::mt19937& gen) const;
    char sample_next_char(const std::string& kgram, std::mt19937& gen) const;
    bool has_kgram(const std::string& kgram) const;
    
    // Debug utilities
    const std::map<std::string, std::map<char, int>>& get_kgrams() const;
    void print_kgram_frequencies() const;
    void print_character_transitions() const;
};

#endif

