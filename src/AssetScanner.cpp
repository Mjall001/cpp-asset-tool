#include "AssetScanner.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <thread>
#include <chrono>

int AssetScanner(fs::path filePath)
{
    std::cout << "Scanning started...\n";

    std::cout << "Current working directory: " << fs::current_path() << std::endl;
    std::error_code ec;
    fs::directory_iterator end;

    std::vector<FailedEntry> failures;
    std::vector<Asset> assets;

    if (!fs::exists(filePath) || !fs::is_directory(filePath))
    {
        std::cout << filePath << "File Path is not a valid directory\n"
                  << std::endl;
        return 1;
    }
    // std:: cout <<"\nFile Path does Exist: "<< filePath << std::endl;
    fs::directory_iterator dirIter(filePath, ec);

    if (ec)
    {
        std::cout << "Failed to open directory: " << ec.message() << "\n";
        return 1;
    }
    for (; dirIter != end; dirIter.increment(ec))
    {
        if (ec)
        {
            failures.push_back({filePath, ec, "reading next entry"});
            break;
        }
        const auto &item = *dirIter;
        std::error_code entryEc;

        bool isFile = fs::is_regular_file(item.path(), entryEc);

        if (entryEc)
        {
            failures.push_back({item.path(), entryEc, "checking file type"});
            continue;
        }
        if (!isFile)
        {
            continue;
        }
        std::string currentName = item.path().filename().string();
        std::string currentExt = item.path().extension().string();
        std::uintmax_t currentSize = fs::file_size(item.path(), entryEc);
        if (entryEc)
        {
            failures.push_back({item.path(), entryEc, "reading file size"});
            continue;
        }
        // std::cout << currentName << currentExt <<" File size: " << currentSize <<std::endl;

        assets.emplace_back(currentName, currentExt, currentSize);
        // std::cout << assets.back().name << "\n";
    }
    for (const auto &f : failures)
    {
        std::cerr << f.path << " | " << f.operation << " | " << f.error.message() << "\n";
    }

    //
    std::cout << "\n"
              << "Summary: " << std::endl;
    // print out a summary of file types, counts and duplicate filenames.

    std::unordered_map<std::string, std::size_t> extensionSum;

    for (const auto &asset : assets)
    {
        extensionSum[asset.extension]++;
    }

    std::cout << "Total Assets: " << assets.size() << "\n";
    for (const auto &[ext, count] : extensionSum)
    {
        std::cout << "Extension: " << ext << " | Count: " << count << "\n";
    }

    return 0;
}
