#include <iostream>
#include <filesystem>
#include "bitio.hh"
#include "huffman.hh"

int main(int argc, char* argv[]){ // code copies from a tour of c++
std::cout<<"this works :)";
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path file_path {argv[1]};
    std::ifstream is (file_path, std::ifstream::binary);
    file_path+=".plaintext";
    std::vector<bool> bool_vector;
    std::ofstream outfile (file_path, std::ifstream::binary);

    Huffman huff;
    BitInput istream(is);

    is.close();

    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
        for (int i = 0 ; i < length; i++) {
            bool_vector.push_back(istream.input_bit());
        }
        is.close();
    }

    while(true){
        auto symbol = -1;
        while (symbol < 0){
            for (auto b : bool_vector){
                symbol = huff.decode(b);
            }
        }
        if (symbol == Huffman::HEOF){break;}
        else {outfile<<symbol;}
        symbol = -1;
    }
    outfile.close();
}
