#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <map>

// Model class encapsulates k-gram statistics and training
class Model {
private:
    // K-grams representation: map<string, map<char, int>> 
    //   - Outer map: k-gram -> character distribution
    //   - Inner map: character -> count of how many times it follows the k-gram
    std::map<std::string, std::map<char, int>> kgrams;
    int k;

public:
    // Constructor: initialize model with k-gram size
    Model(int k);
    
    // Training: Extract k-gram character transition statistics from input text
    void train(const std::string& input);
    
    // Getters for model data
    const std::map<std::string, std::map<char, int>>& get_kgrams() const;
    int get_k() const;
};

#endif

