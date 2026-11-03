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

std::unordered_map<std::string, std::vector<std::string>> DuplicateDetector(fs::path filePath)
{
    std::cout << "working" << ": " << std::endl;
    auto file_counter = 0;

    std::cout << std::filesystem::absolute(filePath) << '\n';

    fs::directory_iterator dirIter(filePath);
    std::vector<Asset> assets;
    std::unordered_map<std::uintmax_t, std::vector<fs::path>> same_size_assets; // filesize and
    std::unordered_map<std::string, std::string> hashed_files;                  // filename,hash
    std::unordered_map<std::string, std::vector<std::string>> file_hash_groups; // hash,filename
    std::unordered_map<std::string, std::vector<std::string>> duplicate_files;

    for (const auto &asset : dirIter)
    {
        if (!fs::is_regular_file(asset.path()))
        {
            continue;
        }
        auto size = fs::file_size(asset.path());
        same_size_assets[size].push_back(asset.path());
    }

    for (const auto &[size, paths] : same_size_assets)
    {
        if (paths.size() < 2)
        {
            continue;
        }
        for (const auto &path : paths)
        {
            std::string currentName = path.string();
            std::string currentHash = hashFile(path);
            // std::cout << currentName << std::endl;
            // std::cout << currentHash << std::endl;
            hashed_files.emplace(currentName, currentHash);
            file_counter += 1;
        }
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
    for (const auto &[hash, names] : duplicate_files)
    {
        std::cout << "Duplicates group (" << names.size() << " files):\n";
        for (const auto &n : names)
            std::cout << " " << n << "\n";
    }
    if (duplicate_files.size() == 0)
    {
        std::cout << "No Duplicates Present" << std::endl;
    }
    std::cout << "All hash_files: " << hashed_files.size() << std::endl;
    return duplicate_files;
}

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