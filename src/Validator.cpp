#include "Validator.h"
#include "AssetScanner.h"
#include <iostream>
#include <vector>
#include<string>

int Validator(){

    fs::path filePath = "tests/TestAssets";

    std::cout <<"\n--- Validation Report ---"<<std::endl;
    std::cout <<"\nFile Path:  " << filePath<< std::endl;

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;

    for (const auto& asset : dirIter) {

        std:: string currentName = asset.path().filename().string();
        std:: string currentExt = asset.path().extension().string();
        std:: uintmax_t currentSize = asset.file_size();

        assets.emplace_back(currentName, currentExt,   currentSize);
    }
    std::cout << assets.size() << std::endl;
    //Target Directory, 
    //Print failed assets name, reason it failed and file path
    //summary of passed, failed and errors
    //in the end RESULT: Validation FAILED (Exit Code 1)
    
    //tomorrow: fix summary and continue validation
    

    
    return 0;
}