#include <iostream>
#include <filesystem>
#include "bitio.cc"


main(int argc, char* argv[]){ // code copies from a tour of c++
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        return 1;
    }
    std::filesystem::path p {argv[1]};
}