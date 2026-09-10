#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

namespace fs = std::filesystem;

struct bad_assets{
    std::string format;
    std::string file_name;
    std::uintmax_t size_bytes;
    bool is_meta = false; //for unity assets
};
int Validator();