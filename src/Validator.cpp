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
    std::vector<defective_assets> ill_assets;

    for (const auto& asset : dirIter) {

        std:: string currentName = asset.path().filename().string();
        std:: string currentExt = asset.path().extension().string();
        std:: uintmax_t currentSize = asset.file_size();

        assets.emplace_back(currentName, currentExt,   currentSize);
    }//populate assets vector for all assets

    
    for (const auto& ill_assets : assets) {
        std:: string format = ill_assets.extension;
        std:: cout <<"\nformat: "<< format <<std::endl;

        std::string file_name = ill_assets.name;
        std:: cout <<"\nname: "<< file_name <<std::endl;

        std::uintmax_t size_bytes = ill_assets.size;
        std:: cout <<"\nsize: "<< size_bytes <<" bytes"<<std::endl;
        //bad_assets.emplace_back(currentName, currentExt,   currentSize);
    } // populate bad_assets Vector
    std::cout << assets.size() << std::endl;
    //Target Directory, 
    //Print failed assets name, reason it failed and file path
    //summary of passed, failed and errors
    //in the end RESULT: Validation FAILED (Exit Code 1)

    //now: Make a conditional loop and also append status and Reasons to each assets that meets the commitments 
    
    //

    
    return 0;
}