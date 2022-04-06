#include <iostream>
#include <filesystem>
#include <sstream>
#include "bitio.hh"
#include "huffman.hh"

int main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }

    std::filesystem::path p {argv[1]};
    std::ifstream is (p, std::ifstream::binary);
    p += ".plaintext"; // new file will be *.txt.comp.plaintext
    std::ofstream os (p, std::ofstream::binary);

    BitInput in = BitInput(is);
    BitOutput out = BitOutput(os);
    Huffman huff_tree = Huffman();

    while (!is.eof()){ // if there's stuff in the file
      auto sym = huff_tree.decode(in.input_bit()); // input_bit will automatically move to the next bit after grabbing
      if (sym >= 0){ // if we've decoded a symbol, put it in the file
        os.put(sym);
      }
    }
    is.close();
}
