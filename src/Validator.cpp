#include "Validator.h"
#include "AssetScanner.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <array>

bool isValidFilenameRegex(const std::string &filename)
{
    static const std::regex pattern("^[a-zA-Z0-9_]+$");
    return std::regex_match(filename, pattern);
}
constexpr std::uintmax_t MAX_ASSET_SIZE_BYTES = 16 * 1024 * 1024; // 16 MB

// const auto &meta_files = {"json", "meta"};

int Validator(fs::path filePath)
{

    // fs::path filePath = "tests/TestAssets";

    std::cout << "\n--- Validation Report ---" << std::endl;
    std::cout << "\nFile Path:  " << filePath << std::endl;

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;
    std::vector<validated_assets> bad_assets;
    std::array<std::string, 4> valid_formats{{".txt", ".fbx", ".png", ".jpeg"}};
    auto valid_count = 0;

    for (const auto &asset : dirIter)
    {
        if (!fs::is_regular_file(asset.path()))
        {
            continue;
        }

        std::string currentName = asset.path().filename().stem().string();
        std::string currentExt = asset.path().extension().stem().string();
        std::uintmax_t currentSize = asset.file_size();

        assets.emplace_back(currentName, currentExt, currentSize);
    } // populate assets vector for all assets

    for (const auto &a : assets)
    {

        std::string format = a.extension;
        // std:: cout <<"\nformat: "<< format <<std::endl;

        std::string file_name = a.name;
        // std:: cout <<"\nname: "<< file_name <<std::endl;

        std::uintmax_t size_bytes = a.size;
        // std:: cout <<"\nsize: "<< size_bytes <<" bytes"<<std::endl;

        bad_assets.emplace_back(format, file_name, size_bytes);

    }; // populate bad_assets Vector

    // std::cout << "\nvalidator is running " << std::endl;
    for (auto &a : bad_assets)
    {

        if (!isValidFilenameRegex(a.file_name))
        {
            // std::cout << a.file_name << std::endl;
            const std::string status_w = "WARNING";
            a.status = status_w;
            a.reason = "| THIS FILE NAME IS INVALID |";
        }
        if (std::find(valid_formats.begin(), valid_formats.end(), a.format) == valid_formats.end())
        {

            const std::string status_w = "WARNING";
            a.status = status_w;
            a.reason = "| THIS FILE IS AN INVALID FORMAT |";
        }
        // missing metadata
        if (a.size_bytes > MAX_ASSET_SIZE_BYTES)
        {
            const std::string status_w = "WARNING2";
            a.status = status_w;
            a.reason = "| THIS FILE IS OVERSIZED |";
        }
        /*  if (std:: find(meta_files.begin(), meta_files.end(), a.file_name + ".meta") == meta_files.end()){

             const std:: string status_w = "WARNING";
             a.status = status_w;
             a.reason = "| THERE IS NO MATCHING META FILE |";
             errors.emplace_back(a.reason);
         } */
        if (a.reason == "Valid file")
        {
            a.status = "VALIDATED";
            valid_count += 1;
        }
        // std::cout << "\nname " << a.file_name << std::endl;
        // std::cout << "\nstatus " << a.status << std::endl;
        // std::cout << "\nsize: " << a.size_bytes << " bytes" << std::endl;
        // std::cout << "\nformat: " << a.format << std::endl;
        //  std:: cout <<"\nReason: "<< a.reason <<std::endl;
    }
    std::cout << "Summary of assets: " << assets.size() << "\n";
    std::cout << "Validated assets: " << valid_count << "\n";
    std::cout << "Invalid assets: " << assets.size() - valid_count << "\n";
    for (auto &a : bad_assets)
    {
        if (a.status == "VALIDATED")
        {
            continue;
        }

        std::cout << "Name: " << a.file_name << a.format << ": " << a.reason << "\n";
    }

    return 0;
}
