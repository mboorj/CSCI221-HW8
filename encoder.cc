#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

#include "bitio.hh"
#include "huffman.hh"


int main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path file_path {argv[1]};

    std::ifstream is (file_path, std::ifstream::binary);
    file_path+=".comp"; // new file will be *.txt.comp
    std::ofstream os (file_path, std::ofstream::binary);
    BitOutput out = BitOutput(os);

    std::vector<char> char_vector;

    Huffman huff_tree = Huffman();

    while (!is.eof()){ // if there's still stuff in the istream
      auto v = huff_tree.encode(is.get()); // get and encode the next char
      for (auto bit : v){
        out.output_bit(bit); // output the encoding bit by bit into the new file
      }
    }
    is.close();
}
