#include "AssetScanner.h"
#include <iostream>
#include <unordered_map>
#include <vector>

int AssetScanner(){
    std::cout << "Program started...\n";

    fs::path filePath = "tests/TestAssets";
    
    
    std::cout << "Current working directory: " << fs::current_path() << std::endl;

    if (!fs::exists(filePath) || !fs::is_directory(filePath)){
        std:: cout << filePath <<"File Path is not a valid directory\n"<< std::endl;
    }
    std:: cout <<"\nFile Path does Exist: "<< filePath << std::endl;

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;

    for(const auto& item: dirIter){
        std:: string currentName = item.path().filename().string();
        std:: string currentExt = item.path().extension().string();
        std:: uintmax_t currentSize = item.file_size();
        //std::cout << currentName << currentExt <<" File size: " << currentSize <<std::endl;

        //save file information in a vector 
        assets.emplace_back(currentName, currentExt,   currentSize);
        //std::cout << assets.back().name << "\n";

        //place into map using assets value as key and extentions as value   
        
    }
    
    //
    std::cout << "\n" << " Summary: "  <<std::endl; 
    //print out a summary of file types, counts and duplicate filenames. 

    std::unordered_map<std::string, std::size_t> extensionSum;

    for (const auto& asset : assets) {
        extensionSum[asset.extension]++;
    }


    for (const auto& [ext, count] : extensionSum) {
    std::cout << "Extension: " << ext << " | Count: " << count << "\n";
    }
    return 0;
  
    //print total number of things in folder
    //List the file types and number of them
    //Try to include concepts like unordered_map
}

