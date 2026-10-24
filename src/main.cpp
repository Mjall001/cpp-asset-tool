#include "AssetScanner.h"
#include "Validator.h"
#include "DuplicateDetector.h"
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
    if (std::string(argv[1]) == "validate")
    {
        Validator(std::string(argv[2])); // works
    }

    if (std::string(argv[1]) == "scan")
    {
        AssetScanner(std::string(argv[2]));
    }
    if (std::string(argv[1]) == "find_duplicates")
    {
        DuplicateDetector(std::string(argv[2]));
    }

    for (int i = 0; i < argc; i++)
    {
        std::cout << "argc[" << i << "] = ";
        std::cout << argv[i] << std::endl;
    }

    // AssetScanner();
    // Validator();
    // DuplicateDetector();
    /*    auto duplicates = DuplicateDetector();
       for (const auto &group : duplicates)
       {
           std::cout << "Number of copies: " << group.second.size() << '\n';

           for (const auto &filename : group.second)
           {
               std::cout << filename << '\n';
           }
       } */
    return 0;
}

// save outputs using Asset struct

// seperate AssetScanner out of Main

// if it's an odd number of characters make sure it's even
//