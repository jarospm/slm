#ifndef KGRAM_HPP
#define KGRAM_HPP

#include <string>
#include <map>

// Training phase: Extract k-gram character transition statistics from input text
// Returns: map<string, map<char, int>> 
//   - Outer map: k-gram -> character distribution
//   - Inner map: character -> count of how many times it follows the k-gram
std::map<std::string, std::map<char, int>> map_kgrams(std::string input, int k);

#endif

