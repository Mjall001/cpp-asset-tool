#include "Validator.h"
#include "AssetScanner.h"
#include <iostream>
#include <vector>
#include<string>
#include<regex>
#include <array>
#include <openssl/sha.h> 

bool isValidFilenameRegex(const std::string& filename){
    static const std::regex pattern("^[a-zA-Z0-9_]+$");
    return std::regex_match(filename, pattern);
}
const auto& MAX_ASSET_SIZE_BYTES = 16 * 1024 * 1024; // 16 MB

const auto& meta_files = {"json", "meta"};



int Validator(){
   // std:: string sha_test = "Testing this string";
    //std:: string hashed_sha_test = SHA224(sha_test) ;
    

    fs::path filePath = "tests/TestAssets";

    std::cout <<"\n--- Validation Report ---"<<std::endl;
    std::cout <<"\nFile Path:  " << filePath<< std::endl;

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;
    std::vector<defective_assets> ill_assets;
    std::array<std:: string, 1> valid_formats{{".png"}};
    
    std::vector<std::string> errors;
    
    for (const auto& asset : dirIter) {

        std:: string currentName = asset.path().filename().stem().string();
        std:: string currentExt = asset.path().extension().stem().string();
        std:: uintmax_t currentSize = asset.file_size();

        assets.emplace_back(currentName, currentExt,   currentSize);
    }//populate assets vector for all assets

    
    for (const auto& a: assets) {
        
        std:: string format = a.extension;
        //std:: cout <<"\nformat: "<< format <<std::endl;

        std::string file_name = a.name;
        //std:: cout <<"\nname: "<< file_name <<std::endl;

        std::uintmax_t size_bytes = a.size;
        //std:: cout <<"\nsize: "<< size_bytes <<" bytes"<<std::endl;

        ill_assets.emplace_back(format, file_name, size_bytes);


    }; // populate bad_assets Vector

    std:: cout <<"\nvalidator is running "<<std::endl;
    for (auto& a: ill_assets) {
        
        if (!isValidFilenameRegex(a.file_name)){
            std:: cout << a.file_name << std::endl;
            const std:: string status_w = "WARNING";
            a.status = status_w ;
            a.reason ="| THIS FILE NAME IS INVALID |";
            errors.emplace_back(a.reason);
        }
        if (std:: find(valid_formats.begin(), valid_formats.end(),a.format ) == valid_formats.end()){

            const std:: string status_w = "WARNING";
            a.status = status_w;
            a.reason = "| THIS FILE IS AN INVALID FORMAT |";
            errors.emplace_back(a.reason);
        }
        //missing metadata
        if (a.size_bytes > MAX_ASSET_SIZE_BYTES){
            const std:: string status_w = "WARNING2";
            a.status = status_w;
            a.reason = "| THIS FILE IS OVERSIZED |";
            errors.emplace_back(a.reason);
        }
       /*  if (std:: find(meta_files.begin(), meta_files.end(), a.file_name + ".meta") == meta_files.end()){

            const std:: string status_w = "WARNING";
            a.status = status_w;
            a.reason = "| THERE IS NO MATCHING META FILE |";
            errors.emplace_back(a.reason);
        } */
       if(a.reason == "Valid file"){
        a.status = "VALIDATED";
       }
        std:: cout <<"\nname "<< a.file_name <<std::endl;
        std:: cout <<"\nstatus "<< a.status <<std::endl;
        std:: cout <<"\nsize: "<< a.size_bytes <<" bytes"<<std::endl;
        std:: cout <<"\nformat: "<< a.format <<std::endl;
        //std:: cout <<"\nReason: "<< a.reason <<std::endl;
        for (const auto& err : errors) {
            std::cout << "\nReason: " << err << std::endl;
        }
        
        errors.clear(); 
    }   
 
    //std::cout << ill_assets.size() << std::endl;

    

    
    //std::cout << ill_assets.size() << std::endl;
    


    //Target Directory, 
    //Print failed assets name, reason it failed and file path
    //summary of passed, failed and errors
    //in the end RESULT: Validation FAILED (Exit Code 1)

    //now: Make a conditional loop and also append status and Reasons to each assets that meets the commitments 
    
    //


return 0;

}
