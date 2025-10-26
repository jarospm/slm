# SLM - Small Language Model

A simple text generator that learns patterns from input text and generates new text in a similar style.

## Overview

This program implements a character-level statistical language model using k-grams. It analyzes transition frequencies between k-character sequences and their following characters, then uses these statistics to generate new text that mimics the style of the input data.

## How It Works

1. **Training**: The model scans the input text and builds a frequency table of k-grams (sequences of k characters) and the characters that follow them
2. **Initialization**: Text generation begins by selecting a random k-gram weighted by its frequency in the training data
3. **Generation**: For each step:
   - Sample the next character from the current k-gram's learned distribution
   - Update the k-gram by removing its first character and appending the new one
   - If the new k-gram doesn't exist in the model, restart with a fresh random k-gram

## Building

To produce the `slm` executable:

```bash
make
```

To clean build artifacts:

```bash
make clean
```

## Usage

```bash
./slm <k> <input_file> <generation_length>
```

**Arguments:**
- `k`: K-gram size (must be ≥ 1)
- `input_file`: Path to training text file
- `generation_length`: Number of characters to generate (must be ≥ k)

**Example:**
```bash
./slm 3 moby.txt 500
```

This trains a 3-gram model on `moby.txt` and generates 500 characters.

## Project Structure

- `src/model.hpp/cpp`: K-gram model training and sampling
- `src/textgen.hpp/cpp`: Text generation algorithm
- `src/main.cpp`: CLI interface and validation

## Requirements

- C++17 compatible compiler (g++, clang++)
- Standard library with `<random>`, `<map>`, `<vector>` support

