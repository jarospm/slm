#ifndef TEXTGEN_HPP
#define TEXTGEN_HPP

#include <string>
#include <random>
#include "model.hpp"

// Text generator with stateful sampling
class Generator {
private:
    const Model& model_;
    std::mt19937 gen_;
    
public:
    // Constructor: initialize generator with trained model
    Generator(const Model& model);
    
    // Generate text of specified length
    std::string generate(int length);
};

#endif

