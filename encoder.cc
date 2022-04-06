#include <iostream>
#include <filesystem>
#include "bitio.hh"
#include <fstream>


main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path file_path {argv[1]}; 

    std::ifstream is (path, std::ifstream::binary);
    


}
