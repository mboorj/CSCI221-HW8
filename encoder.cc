#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include "bitio.cc"
#include "bitio.hh"


main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path file_path {argv[1]}; 

    std::ifstream is (path, std::ifstream::binary);

    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        std::vector<char> char_vector;

        for (int i; i < length; i++) {
            char_vector.push_back(is.get());
        }

        is.close();

        for (int i : char_vector) {
            std::cout << char_vector[i];
        }
    }
}
