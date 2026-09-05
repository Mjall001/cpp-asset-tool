#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

namespace fs = std::filesystem;

struct Asset{

    std::string name;
    std::string extension;
    std::uintmax_t size;

};

int AssetScanner();