#include "textgen.hpp"

using namespace std;

Generator::Generator(const Model& model) 
    : model_(model) {
    // Set up random number generator
    random_device rd;
    gen_.seed(rd());
}

string Generator::generate(int length) {
    // Step 1: Choose starting k-gram according to k-gram frequencies
    string current_kgram = model_.sample_random_kgram(gen_);
    
    // Output starts with the initial k-gram
    string output = current_kgram;
    
    // Generate remaining characters
    while (output.length() < length) {
        // Step 2: Sample next character from current k-gram's distribution
        char next_char = model_.sample_next_char(current_kgram, gen_);
        
        // Step 3: Output character
        output += next_char;
        
        // Step 4: Update k-gram (remove first char, add sampled char)
        current_kgram = current_kgram.substr(1) + next_char;
        
        // If new k-gram doesn't exist in model...
        if (!model_.has_kgram(current_kgram)) {
            // pick a new random kgram
            current_kgram = model_.sample_random_kgram(gen_);
            
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

