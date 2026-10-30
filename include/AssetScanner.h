#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

namespace fs = std::filesystem;

struct Asset
{

    std::string name;      // name of file
    std::string extension; // extension
    std::uintmax_t size;   // size of file
};
struct FailedEntry
{
    fs::path path;         // which file or folder failed
    std::error_code error; // why it failed (the reason)
    std::string operation; // what you were trying to do when it failed
};

int AssetScanner(fs::path filePath);