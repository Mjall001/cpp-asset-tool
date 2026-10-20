#pragma once
#include <array>
#include <string>
#include <filesystem>
#include <cstdint>
#include <cstdio>
#include <vector>
#include "AssetScanner.h"
#include "DuplicateDetector.h"
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> DuplicateDetector()
{
    std::cout << "working" << ": " << std::endl;

    fs::path filePath = "tests/TestAssets"; // path not found
    std::cout << std::filesystem::absolute(filePath) << '\n';
    // fs::path testFile = "tests/TestAssets/Skin_Texture_Graph_Base_Colour.png";
    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;

    std::unordered_map<std::string, std::string> hashed_files;                  // filename,hash
    std::unordered_map<std::string, std::vector<std::string>> file_hash_groups; // hash,filename
    std::unordered_map<std::string, std::vector<std::string>> duplicate_files;

    for (const auto &asset : dirIter)
    {
        std::string currentName = asset.path().filename().stem().string();
        std::string currentHash = hashFile(asset.path());
        // std::cout << currentName << std::endl;
        // std::cout << currentHash << std::endl;
        hashed_files.emplace(currentName, currentHash);
    }
    for (auto i : hashed_files)
    {
        // add everything to unique_set by hash: file_name
        // if it's already there remove both and place in duplicate files
        if (!file_hash_groups.contains(i.second))
        {
            file_hash_groups[i.second];
            file_hash_groups[i.second].push_back(i.first);
        }
        else
        {
            file_hash_groups[i.second].push_back(i.first);
        }
    }
    for (const auto &i : file_hash_groups)
    {
        if (i.second.size() > 1)
        {
            duplicate_files.emplace(i);
        }
    }

    return duplicate_files;
}

// refactor to place hashing function here
// e.g hashFile(file)

std::string hashFile(fs::path file)
{
    std::ifstream fileStream(file, std::ios::binary);
    std::array<char, 8192> buffer;
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    md = EVP_sha224();
    // std::string hashString;
    std::ostringstream hashStream;

    if (!fileStream.is_open())
    {
        return "unopened file";
    }

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL)
    {
        return "no new context";
    }

    EVP_DigestInit_ex2(mdctx, md, NULL);

    while (fileStream.read(buffer.data(), buffer.size()) || fileStream.gcount() > 0)
    {
        // std::cout << "Bytes read: " << file.gcount() << std::endl; testing buffer implementation
        EVP_DigestUpdate(mdctx, buffer.data(),
                         static_cast<std::size_t>(fileStream.gcount()));
    }

    unsigned char md_value[EVP_MAX_MD_SIZE]; // hash value after digesting
    unsigned int md_len;
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    for (unsigned int i = 0; i < md_len; i++)
    {
        // printf("%02x", md_value[i]); test
        hashStream << std::hex << std::setw(2) << std::setfill('0')
                   << static_cast<int>(md_value[i]);
    }
    std::string hashString = hashStream.str();
    // std::cout << hashString << " " << hashString.size() << '\n';
    EVP_MD_CTX_free(mdctx);
    return hashString;
}