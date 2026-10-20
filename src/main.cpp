#include "AssetScanner.h"
#include "Validator.h"
#include "DuplicateDetector.h"
#include <iostream>

int main()
{

    // AssetScanner();
    // Validator();
    DuplicateDetector();
    /*    auto duplicates = DuplicateDetector();
       for (const auto &group : duplicates)
       {
           std::cout << "Number of copies: " << group.second.size() << '\n';

           for (const auto &filename : group.second)
           {
               std::cout << filename << '\n';
           }
       } */
}

// save outputs using Asset struct

// seperate AssetScanner out of Main

// if it's an odd number of characters make sure it's even
//