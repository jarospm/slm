#ifndef GENERATION_HPP
#define GENERATION_HPP

#include <string>
#include <map>

// Generate text using the trained k-gram model
// Parameters:
//   - kgrams: trained model (k-gram -> character -> count)
//   - length: number of characters to generate
// Returns: generated text string
std::string generate_text(const std::map<std::string, std::map<char, int>>& kgrams, int length);

#endif

