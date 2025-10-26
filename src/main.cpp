#include <iostream>
#include <string>
#include <fstream>
#include "model.hpp"
#include "textgen.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Usage: ./slm <k> <input_file> <generation_length>
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <k> <input_file> <generation_length>" << endl;
        return 1;
    }

    // Validate k (must be >= 1)
    int k;
    try {
        k = stoi(argv[1]);
    } catch (const invalid_argument& e) {
        cerr << "Error: k must be a valid integer" << endl;
        return 1;
    }
    
    if (k < 1) {
        cerr << "Error: k must be >= 1" << endl;
        return 1;
    }

    // Validate generation_length (must be >= 0)
    int gen_length;
    try {
        gen_length = stoi(argv[3]);
    } catch (const invalid_argument& e) {
        cerr << "Error: generation_length must be a valid integer" << endl;
        return 1;
    }
    
    if (gen_length < 0) {
        cerr << "Error: generation_length must be >= 0" << endl;
        return 1;
    }
    
    // Validate k <= gen_length (generation starts with k-gram, then adds more characters)
    if (k > gen_length) {
        cerr << "Error: k cannot exceed generation_length" << endl;
        return 1;
    }

    // Validate file can be opened
    ifstream file;
    file.open(argv[2]);
    
    if (!file.is_open()) {
        cerr << "Error: could not open file '" << argv[2] << "'" << endl;
        return 1;
    }

    string line;
    string input;

    while (getline(file, line)) {
        input += line;
    }

    file.close();

    // Validate input has enough characters for k-grams
    if (input.length() <= k) {
        cerr << "Error: input text must have more than k characters (input length: " 
            << input.length() << ", k: " << k << ")" << endl;
        return 1;
    }

    // Train model
    Model model(k, input);

    // Generate text
    Generator generator(model);
    string generated_text = generator.generate(gen_length);
    cout << generated_text << endl;

}

