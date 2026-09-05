#include "AssetScanner.h"
#include <iostream>

int AssetScanner(){
    std::cout << "Program started...\n";

    fs::path filePath = "tests/TestAssets";
    
    
    std::cout << "Current working directory: " << fs::current_path() << std::endl;

    if (!fs::exists(filePath) || !fs::is_directory(filePath)){
        std:: cout << filePath <<"File Path is not a valid directory\n"<< std::endl;
    }
    std:: cout <<"File Path does Exist: "<< filePath << std::endl;

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;

    for(const auto& item: dirIter){
        std:: string currentName = item.path().filename().string();
        std:: string currentExt = item.path().extension().string();
        std:: string currentSize = std::to_string(item.file_size());

        std::cout << currentName << currentExt <<" File size: " << currentSize <<std::endl;
    }
    //std::cout << "Hello World" << std::endl;
    return 0;
}