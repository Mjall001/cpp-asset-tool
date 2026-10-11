#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>
#include "AssetScanner.h"
#include <openssl/sha.h>
#include <iomanip>
#include <fstream>
#include <iostream>

int DuplicateDetector(){
    //std:: ifstream istrm(filename, std::ios::binary);
    //esentially same thing as validator add assets to vector/unordered map and then initiate the hashing logic

    fs::path filePath = "tests/TestAssets";
    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;
    
    std::vector<auto> hashed_files;
    
    
    unsigned char hash[SHA224_DIGEST_LENGTH];

    for (const auto& asset : dirIter) {

        std:: string currentName = asset.path().filename().stem().string();
        std:: string currentExt = asset.path().extension().stem().string();
        std:: uintmax_t currentSize = asset.file_size();

        assets.emplace_back(currentName, currentExt,   currentSize);
        SHA224(reinterpret_cast<const unsigned char*>(&currentSize),sizeof(currentSize), hash);
        std:: cout <<"\nsize: "<< currentSize<<" bytes"<<std::endl;
        
        std::ofstream(currentSize, std::ios::binary);

         std::ifstream istrm(filename, std::ios::binary);
        if (!istrm.is_open())
            std::cout << "failed to open " << filename << '\n';
        else
        

        //hashed_files.emplace_back((int)hash[0]);
        std::cout << "Hash success! First byte: " << (int)hash[0] << "\n";
    }

    return 0;
}