#include <iostream>
#include <filesystem>
#include "bitio.hh"


main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    std::filesystem::path p {argv[1]};
}
