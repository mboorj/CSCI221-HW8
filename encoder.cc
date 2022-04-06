#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include "bitio.hh"
#include "huffman.hh"


int main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path file_path {argv[1]}; 

    std::ifstream is (file_path, std::ifstream::binary);

    std::vector<char> char_vector;

    Huffman huff_tree = Huffman();

    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        for (int i = 0 ; i < length; i++) {
            char_vector.push_back(is.get());
        }

        is.close();
    }

    for(auto it=char_vector.begin(); it != char_vector.end(); it++) {
        huff_tree.Huffman::encode(*it);
    }
}
